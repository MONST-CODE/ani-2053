// Exercice 5 - Le futur qui ne bloque pas
// Le chargement de l'image s'effectue dans un worker du NkThreadPool.
// Le fil principal reste le seul responsable des evenements et du dessin.

#include <cstdint>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

#include "NKCanvas/Core/NkContextDesc.h"
#include "NKCanvas/Core/NkGraphicsApi.h"
#include "NKCanvas/Renderer/Core/NkRenderer2D.h"
#include "NKCanvas/Renderer/Targets/NkRenderWindow.h"
#include "NKCore/NkTraits.h"
#include "NKEvent/NkWindowEvent.h"
#include "NKImage/Core/NkImage.h"
#include "NKMath/NkColor.h"
#include "NKThreading/NkPromise.h"
#include "NKThreading/NkThreadPool.h"
#include "NKTime/NkChrono.h"
#include "NKWindow/Core/NkWindowConfig.h"
#include "NKWindow/NKMain.h"
#include "NKWindow/NKWindow.h"

using namespace nkentseu;
using namespace nkentseu::renderer;

namespace {
    // true  : version non bloquante, qui interroge futur.IsReady() a chaque trame.
    // false : version bloquante, qui appelle futur.Get() immediatement apres le lancement.
    constexpr bool UTILISER_ISREADY = true;

    // Placez une grande image a cote du repertoire de lancement, ou adaptez ce chemin.
    constexpr const char* CHEMIN_IMAGE = "grande-photo.png";

    // Le programme est normalement lance depuis la racine du depot. Le second
    // chemin permet aussi une execution depuis le dossier de cet exercice.
    constexpr const char* CHEMIN_RAPPORT_DEPOT =
        "chapitre-06/exo5-le_futur_qui_ne_bloque_pas/cadence.txt";
    constexpr const char* CHEMIN_RAPPORT_LOCAL = "cadence.txt";

    constexpr std::uint64_t NOMBRE_TRAMES_AVANT_CHARGEMENT = 60;
    constexpr float32 TAILLE_CARRE = 32.0f;

    // Renvoie la taille du fichier sur disque, sans le charger dans le fil principal.
    std::uint64_t tailleFichierEnOctets(const char* chemin) {
        std::ifstream fichier(chemin, std::ios::binary | std::ios::ate);
        if (!fichier.is_open()) {
            return 0;
        }

        const std::streamoff taille = fichier.tellg();
        if (taille < 0) {
            return 0;
        }

        return static_cast<std::uint64_t>(taille);
    }

    // Ne copie jamais NkImage : on ne conserve que ses metadonnees.
    void releverImage(const NkImage& image,
                      bool& imageValide,
                      uint32& largeur,
                      uint32& hauteur) {
        largeur = image.Width();
        hauteur = image.Height();
        imageValide = largeur > 0 && hauteur > 0 && image.Pixels() != nullptr;
    }

    struct MesureCadence {
        bool disponible = false;
        float64 trameMaximaleMs = 0.0;
        std::uint64_t tramesPendantChargement = 0;
    };

    // Recupere les valeurs numeriques d'une ligne deja mesuree. Une ligne contenant
    // encore "A MESURER" est volontairement ignoree.
    bool extraireMesure(const std::string& ligne, MesureCadence& mesure) {
        const std::size_t positionTrame = ligne.find("trame la plus longue");
        if (positionTrame == std::string::npos) {
            return false;
        }

        const std::size_t egalDuree = ligne.find('=', positionTrame);
        const std::size_t debutCompteur = ligne.find("trames ", egalDuree);
        if (egalDuree == std::string::npos || debutCompteur == std::string::npos) {
            return false;
        }
        const std::size_t egalCompteur = ligne.find('=', debutCompteur);
        if (egalCompteur == std::string::npos) {
            return false;
        }

        std::istringstream lectureDuree(ligne.substr(egalDuree + 1));
        std::istringstream lectureCompteur(ligne.substr(egalCompteur + 1));
        float64 duree = 0.0;
        std::uint64_t nombreTrames = 0;
        if (!(lectureDuree >> duree) || !(lectureCompteur >> nombreTrames)) {
            return false;
        }

        mesure.disponible = true;
        mesure.trameMaximaleMs = duree;
        mesure.tramesPendantChargement = nombreTrames;
        return true;
    }

    // Lit le rapport precedent pour conserver la mesure de l'autre mode entre
    // deux executions successives (true, puis false pour la constante).
    void lireMesuresExistantes(const std::string& chemin,
                               MesureCadence& mesureGet,
                               MesureCadence& mesureIsReady) {
        std::ifstream rapport(chemin);
        if (!rapport.is_open()) {
            return;
        }

        std::string ligne;
        while (std::getline(rapport, ligne)) {
            if (ligne.rfind("Get :", 0) == 0) {
                (void)extraireMesure(ligne, mesureGet);
            } else if (ligne.rfind("IsReady :", 0) == 0) {
                (void)extraireMesure(ligne, mesureIsReady);
            }
        }
    }

    void ecrireLigneMesure(std::ofstream& rapport,
                           const char* etiquette,
                           const MesureCadence& mesure) {
        rapport << etiquette;
        if (!mesure.disponible) {
            rapport << " trame la plus longue = A MESURER ms ; "
                       "trames dessinees pendant le chargement = A MESURER.\n\n";
            return;
        }

        rapport << " trame la plus longue = " << std::fixed << std::setprecision(3)
                << mesure.trameMaximaleMs << " ms ; "
                << "trames dessinees pendant le chargement = "
                << mesure.tramesPendantChargement << ".\n\n";
    }

    // Le rapport reste constitue des quatre paragraphes demandes. La premiere
    // execution remplit un mode ; la deuxieme conserve ce resultat et remplit l'autre.
    void ecrireRapport(const std::string& chemin,
                       std::uint64_t tailleFichier,
                       bool imageValide,
                       uint32 largeur,
                       uint32 hauteur,
                       float64 tempsChargementMs,
                       const MesureCadence& mesureGet,
                       const MesureCadence& mesureIsReady) {
        std::ofstream rapport(chemin, std::ios::out | std::ios::trunc);
        if (!rapport.is_open()) {
            std::cout << "Attention : impossible d'ecrire le rapport dans " << chemin << ".\n";
            return;
        }

        rapport << "Image : fichier = " << CHEMIN_IMAGE
                << " ; taille sur disque = " << std::fixed << std::setprecision(3)
                << (static_cast<float64>(tailleFichier) / (1024.0 * 1024.0))
                << " Mo (" << tailleFichier << " octets)";
        if (imageValide) {
            const std::uint64_t taillePixelsRGBA =
                static_cast<std::uint64_t>(largeur) * static_cast<std::uint64_t>(hauteur) * 4u;
            rapport << " ; dimensions = " << largeur << " x " << hauteur << " pixels"
                    << " ; pixels RGBA = "
                    << (static_cast<float64>(taillePixelsRGBA) / (1024.0 * 1024.0)) << " Mo";
        } else {
            rapport << " ; dimensions = indisponibles (chargement invalide)";
        }
        rapport << " ; temps de chargement = " << tempsChargementMs << " ms.\n\n";

        ecrireLigneMesure(rapport, "Get :", mesureGet);
        ecrireLigneMesure(rapport, "IsReady :", mesureIsReady);
        rapport << "Ce qu'on voit : avec Get, le fil principal attend la fin du chargement et le "
                    "carre semble se figer pendant cette attente ; avec IsReady, la boucle "
                    "verifie futur.IsReady() sans bloquer et le carre continue d'avancer "
                    "pendant le chargement. Les mesures montrent l'effet du blocage sur la cadence.\n";
    }

    std::string trouverCheminRapport() {
        std::ifstream rapportDepot(CHEMIN_RAPPORT_DEPOT);
        if (rapportDepot.is_open()) {
            return CHEMIN_RAPPORT_DEPOT;
        }
        return CHEMIN_RAPPORT_LOCAL;
    }
}

NKENTSEU_DEFINE_APP_DATA(([]() {
    NkAppData donnees{};
    donnees.appName = "Le futur qui ne bloque pas";
    donnees.appVersion = "1.0.0";
    return donnees;
})());

int nkmain(const NkEntryState& state) {
    (void)state;

    const std::uint64_t tailleFichier = tailleFichierEnOctets(CHEMIN_IMAGE);
    const std::string cheminRapport = trouverCheminRapport();
    MesureCadence mesureGet;
    MesureCadence mesureIsReady;
    lireMesuresExistantes(cheminRapport, mesureGet, mesureIsReady);

    // 1. Fenetre native.
    NkWindowConfig configurationFenetre;
    configurationFenetre.title = "Nkentseu - Le futur qui ne bloque pas";
    configurationFenetre.width = 960;
    configurationFenetre.height = 600;
    configurationFenetre.centered = true;
    configurationFenetre.resizable = true;

    NkWindow fenetre;
    if (!fenetre.Create(configurationFenetre)) {
        std::cout << "Erreur : impossible de creer la fenetre.\n";
        return -1;
    }

    // 2. Cible de rendu NkCanvas. Sous Windows, on choisit Direct3D 11.
    NkContextDesc descriptionGraphique;
#if defined(NKENTSEU_PLATFORM_WINDOWS)
    descriptionGraphique.api = NkGraphicsApi::NK_GFX_API_DX11;
#else
    descriptionGraphique.api = NkGraphicsApi::NK_GFX_API_OPENGL;
#endif

    NkRenderWindow cible(fenetre, descriptionGraphique);
    if (!cible.IsValid()) {
        std::cout << "Erreur : impossible d'initialiser NkCanvas.\n";
        fenetre.Close();
        return -2;
    }

    // 3. Etat du programme et gestion de la fermeture.
    auto& evenements = NkEvents();
    bool applicationActive = true;
    evenements.AddEventCallback<NkWindowCloseEvent>(
        [&](NkWindowCloseEvent*) { applicationActive = false; });

    // Le promise et le future vivent plus longtemps que la tache qu'ils coordonnent.
    // Le pool est declare apres eux et rejoint explicitement avant la fin de nkmain.
    NkPromise<NkImage> promesse;
    NkFuture<NkImage> futur = promesse.GetFuture();
    threading::NkThreadPool pool(1);

    bool chargementLance = false;
    bool resultatRecupere = false;
    bool imageValide = false;

    uint32 largeurImage = 0;
    uint32 hauteurImage = 0;
    float64 tempsChargementImageMs = 0.0;
    float64 trameLaPlusLongueMs = 0.0;
    std::uint64_t tramesDessinees = 0;
    std::uint64_t tramesPendantChargement = 0;

    float32 positionX = 20.0f;
    float32 positionY = 100.0f;
    uint32 derniereLargeur = 0;
    uint32 derniereHauteur = 0;
    NkChrono chronometreTrame;

    std::cout << "Mode choisi : "
              << (UTILISER_ISREADY ? "IsReady (non bloquant)" : "Get (bloquant)")
              << "\nImage : " << CHEMIN_IMAGE << "\n";
    if (tailleFichier == 0) {
        std::cout << "Attention : fichier introuvable ou vide depuis le repertoire courant.\n";
    }
    std::cout << "La fenetre commence a dessiner. Le chargement demarre apres 60 trames.\n";

    // 4. Boucle principale : evenements, futur, dessin, mesure de trame.
    while (applicationActive && fenetre.IsOpen()) {
        // Le chrono repart au debut de chaque trame. En mode Get, le temps d'attente
        // bloquant fera donc partie de la trame exceptionnellement longue.
        (void)chronometreTrame.Reset();

        while (NkEvent* evenement = evenements.PollEvent()) {
            (void)evenement;
        }
        if (!applicationActive) {
            break;
        }

        // Maintient la cible de rendu a la taille de la fenetre si elle est redimensionnee.
        const math::NkVec2u tailleFenetre = fenetre.GetSize();
        if (tailleFenetre.x > 0 && tailleFenetre.y > 0 &&
            (tailleFenetre.x != derniereLargeur || tailleFenetre.y != derniereHauteur)) {
            if (derniereLargeur != 0 && derniereHauteur != 0) {
                cible.OnResize(tailleFenetre.x, tailleFenetre.y);
            }
            derniereLargeur = tailleFenetre.x;
            derniereHauteur = tailleFenetre.y;
        }

        // Le lancement se fait apres les 60 premieres trames deja dessinees.
        if (!chargementLance && tramesDessinees >= NOMBRE_TRAMES_AVANT_CHARGEMENT) {
            chargementLance = true;

            pool.Enqueue([&]() {
                NkImage image;
                NkChrono chronometreChargement;

                // desiredChannels = 4 demande une image RGBA. Le resultat reste local
                // a ce worker ; aucune fonction graphique n'est appelee ici.
                (void)image.Load(CHEMIN_IMAGE, 4);
                tempsChargementImageMs = chronometreChargement.Elapsed().milliseconds;

                // NkImage n'est pas copiable : son contenu est transfere au promise.
                promesse.SetValue(nkentseu::traits::NkMove(image));
            });

            std::cout << "Chargement lance dans le NkThreadPool apres "
                      << tramesDessinees << " trames.\n";
        }

        // Ces deux indicateurs servent a isoler les trames affectees au chargement.
        // Ils sont mis a jour avant le rendu puis comptes apres Display().
        bool cetteTrameEstPendantLeChargement = false;
        bool mesurerDureeCetteTrame = false;

        if (chargementLance && !resultatRecupere) {
            if (UTILISER_ISREADY) {
                // IsReady ne bloque pas : tant que la valeur manque, on dessine quand meme.
                if (futur.IsReady()) {
                    const NkImage& image = futur.Get();
                    releverImage(image, imageValide, largeurImage, hauteurImage);
                    resultatRecupere = true;
                } else {
                    cetteTrameEstPendantLeChargement = true;
                    mesurerDureeCetteTrame = true;
                }
            } else {
                // Get bloque jusqu'a SetValue(). La trame courante ne sera dessinee
                // qu'apres la fin du chargement : le gel est ainsi visible et mesurable.
                mesurerDureeCetteTrame = true;
                const NkImage& image = futur.Get();
                releverImage(image, imageValide, largeurImage, hauteurImage);
                resultatRecupere = true;
            }
        }

        const math::NkVec2u tailleCible = cible.GetSize();
        cible.Clear(NkColor2D{18, 22, 30, 255});

        NkRenderer2D& rendu = cible.GetRenderer2D();
        rendu.DrawFilledRect(
            NkRect2f{positionX, positionY, TAILLE_CARRE, TAILLE_CARRE},
            NkColor2D{255, 145, 55, 255});
        cible.Display();

        ++tramesDessinees;
        if (cetteTrameEstPendantLeChargement) {
            ++tramesPendantChargement;
        }

        const float64 dureeTrameMs = chronometreTrame.Elapsed().milliseconds;
        // La plus longue trame est celle observee pendant l'attente du resultat,
        // et non une pause accidentelle survenue avant le lancement ou apres la fin.
        if (mesurerDureeCetteTrame && dureeTrameMs > trameLaPlusLongueMs) {
            trameLaPlusLongueMs = dureeTrameMs;
        }

        // Le carre avance exactement d'un pixel par trame, puis revient a gauche.
        positionX += 1.0f;
        if (tailleCible.x > 0 && positionX > static_cast<float32>(tailleCible.x)) {
            positionX = -TAILLE_CARRE;
        }
    }

    // Si la fenetre est fermee alors que le chargement tourne encore, on attend le
    // resultat ici afin que la promesse reste vivante jusqu'a SetValue().
    if (chargementLance && !resultatRecupere) {
        const NkImage& image = futur.Get();
        releverImage(image, imageValide, largeurImage, hauteurImage);
        resultatRecupere = true;
    }
    pool.Join();

    // 5. Mesures lisibles dans la console pour remplir cadence.txt sans inventer
    // des valeurs : effectuer une execution pour chaque valeur de la constante.
    std::cout << std::fixed << std::setprecision(3);
    std::cout << "\n--- MESURES A REPORTER DANS cadence.txt ---\n";
    std::cout << "Image : fichier = " << CHEMIN_IMAGE
              << " ; taille sur disque = "
              << (static_cast<float64>(tailleFichier) / (1024.0 * 1024.0))
              << " Mo (" << tailleFichier << " octets)";

    if (resultatRecupere && imageValide) {
        const std::uint64_t taillePixelsRGBA =
            static_cast<std::uint64_t>(largeurImage) * static_cast<std::uint64_t>(hauteurImage) * 4u;
        std::cout << " ; dimensions = " << largeurImage << " x " << hauteurImage
                  << " pixels ; pixels RGBA = "
                  << (static_cast<float64>(taillePixelsRGBA) / (1024.0 * 1024.0))
                  << " Mo";
    } else {
        std::cout << " ; chargement invalide (verifiez le chemin de l'image)";
    }
    std::cout << " ; temps de chargement = " << tempsChargementImageMs << " ms.\n";

    std::cout << (UTILISER_ISREADY ? "IsReady" : "Get")
              << " : trame la plus longue = " << trameLaPlusLongueMs
              << " ms ; trames dessinees pendant le chargement = "
              << tramesPendantChargement << ".\n";
    std::cout << "Trames dessinees au total : " << tramesDessinees << ".\n";
    std::cout << "Ce qu'on voit : en mode Get, la fenetre et le carre se figent pendant l'attente ; "
                 "en mode IsReady, le carre continue d'avancer tant que le resultat n'est pas pret.\n";

    // Met a jour cadence.txt avec les valeurs reelles de cette execution. L'autre
    // version est conservee si elle a deja ete mesuree lors d'une execution precedente.
    if (chargementLance && resultatRecupere) {
        MesureCadence& mesureCourante = UTILISER_ISREADY ? mesureIsReady : mesureGet;
        mesureCourante.disponible = true;
        mesureCourante.trameMaximaleMs = trameLaPlusLongueMs;
        mesureCourante.tramesPendantChargement = tramesPendantChargement;

        ecrireRapport(cheminRapport, tailleFichier, imageValide,
                      largeurImage, hauteurImage, tempsChargementImageMs,
                      mesureGet, mesureIsReady);
        std::cout << "Rapport cadence.txt actualise : " << cheminRapport << "\n";
    } else {
        std::cout << "Le chargement n'a pas demarre : gardez la fenetre ouverte au moins 60 trames.\n";
    }

    return 0;
}
