// chapitre-06/exo8-le_message_qui_compte_ses_octets/octets.cpp
// Compare deux encodages du même état joueur avec le bitstream de Nkentseu.
// Lancement : octets serveur
//            octets client 127.0.0.1

#include "NKWindow/NKMain.h"
#include "NKNetwork/NKNetwork.h"
#include "NKTime/NkChrono.h"
#include "NKCore/NkAtomic.h"

#include <iostream>

using namespace nkentseu;

NKENTSEU_DEFINE_APP_DATA(([]() {
    NkAppData donnees{};
    donnees.appName = "Le message qui compte ses octets";
    donnees.appVersion = "1.0.0";
    return donnees;
})());

namespace {

constexpr uint16 PORT_SERVEUR = 7777;
constexpr uint32 BUFFER_CAPACITE = 64;
constexpr uint8 ACCUSE_RECEPTION = 0xAC;

struct EtatJoueur {
    bool vivant{};
    uint8 numero{};
    float32 x{};
    float32 y{};
    float32 angle{};
    int32 sante{};
};

// Un seul état est utilisé pour les deux paquets : seule l'écriture change.
const EtatJoueur JOUEUR_TEST{true, 42, 123.456f, -78.914f, 123.27f, 73};

float32 ecart(float32 envoye, float32 relu) {
    const float32 difference = envoye - relu;
    return difference < 0.0f ? -difference : difference;
}

void afficherEcart(const char* champ, float32 difference, const char* unite) {
    std::cout << "  Écart " << champ << " : " << difference << ' ' << unite << '\n';
}

// Version de référence : les six champs gardent leur type complet.
bool ecrireComplet(uint8* buffer, uint32& octets, uint32& bits) {
    NkBitWriter writer(buffer, BUFFER_CAPACITE);
    writer.WriteU8(JOUEUR_TEST.vivant ? 1 : 0);
    writer.WriteU8(JOUEUR_TEST.numero);
    writer.WriteF32(JOUEUR_TEST.x);
    writer.WriteF32(JOUEUR_TEST.y);
    writer.WriteF32(JOUEUR_TEST.angle);
    writer.WriteI32(JOUEUR_TEST.sante);

    octets = writer.BytesWritten();
    bits = writer.BitsWritten();
    return !writer.IsOverflowed();
}

// Version compacte : on envoie uniquement la précision utile au jeu.
bool ecrireQuantifie(uint8* buffer, uint32& octets, uint32& bits) {
    NkBitWriter writer(buffer, BUFFER_CAPACITE);
    writer.WriteBool(JOUEUR_TEST.vivant);
    writer.WriteU8(JOUEUR_TEST.numero);
    writer.WriteF32Q(JOUEUR_TEST.x, -500.0f, 500.0f, 0.01f); // position au cm
    writer.WriteF32Q(JOUEUR_TEST.y, -500.0f, 500.0f, 0.01f);
    writer.WriteF32Q(JOUEUR_TEST.angle, 0.0f, 360.0f, 0.5f);  // angle au demi-degré
    writer.WriteInt(JOUEUR_TEST.sante, 0, 100);               // santé entre 0 et 100

    octets = writer.BytesWritten();
    bits = writer.BitsWritten();
    return !writer.IsOverflowed();
}

bool lireComplet(const NkReceiveMsg& message, EtatJoueur& joueur) {
    NkBitReader reader(message.data, message.size);
    joueur.vivant = reader.ReadU8() != 0;
    joueur.numero = reader.ReadU8();
    joueur.x = reader.ReadF32();
    joueur.y = reader.ReadF32();
    joueur.angle = reader.ReadF32();
    joueur.sante = reader.ReadI32();
    return !reader.IsOverflowed();
}

bool lireQuantifie(const NkReceiveMsg& message, EtatJoueur& joueur) {
    NkBitReader reader(message.data, message.size);
    joueur.vivant = reader.ReadBool();
    joueur.numero = reader.ReadU8();
    joueur.x = reader.ReadF32Q(-500.0f, 500.0f, 0.01f);
    joueur.y = reader.ReadF32Q(-500.0f, 500.0f, 0.01f);
    joueur.angle = reader.ReadF32Q(0.0f, 360.0f, 0.5f);
    joueur.sante = reader.ReadInt(0, 100);
    return !reader.IsOverflowed();
}

void afficherComparaison(const char* mode, const EtatJoueur& relu, uint32 taille) {
    std::cout << "[Serveur] État relu en " << mode << " (" << taille << " octets)\n"
              << "  Vivant : " << (relu.vivant ? "oui" : "non") << '\n'
              << "  Numéro : " << static_cast<uint32>(relu.numero) << '\n'
              << "  Position : x=" << relu.x << " m, y=" << relu.y << " m\n"
              << "  Angle : " << relu.angle << " degrés\n"
              << "  Santé : " << relu.sante << "/100\n"
              << "  Écarts par rapport à l'état envoyé :\n";

    afficherEcart("vivant", relu.vivant == JOUEUR_TEST.vivant ? 0.0f : 1.0f, "état");
    afficherEcart("numéro", ecart(static_cast<float32>(JOUEUR_TEST.numero), static_cast<float32>(relu.numero)), "unité");
    afficherEcart("position x", ecart(JOUEUR_TEST.x, relu.x), "m");
    afficherEcart("position y", ecart(JOUEUR_TEST.y, relu.y), "m");
    afficherEcart("angle", ecart(JOUEUR_TEST.angle, relu.angle), "degré");
    afficherEcart("santé", ecart(static_cast<float32>(JOUEUR_TEST.sante), static_cast<float32>(relu.sante)), "point");
}

int lancerServeur() {
    NkConnectionManager serveur;
    const NkNetResult resultat = serveur.StartServer(PORT_SERVEUR, 1);
    if (resultat != NkNetResult::NK_NET_OK) {
        std::cout << "[Serveur] Démarrage impossible : "
                  << net::NkNetResultStr(resultat) << '\n';
        return 1;
    }

    std::cout << "[Serveur] En écoute sur le port " << PORT_SERVEUR
              << ". Lance le client dans une autre console.\n";

    uint32 paquetsRecus = 0;
    uint32 toursAttente = 0;

    // DrainAll vide la file des messages reçus par le fil réseau de Nkentseu.
    while (serveur.IsRunning() && paquetsRecus < 2 && toursAttente < 3000) {
        NkVector<NkReceiveMsg> messages;
        serveur.DrainAll(messages);

        for (const NkReceiveMsg& message : messages) {
            EtatJoueur relu{};
            bool paquetValide = false;

            // Pour ces six champs, le paquet complet fait 18 octets et le quantifié 8.
            // On n'ajoute pas de champ de type : la mesure porte sur les données demandées.
            if (message.size == 18) {
                paquetValide = lireComplet(message, relu);
                if (paquetValide) afficherComparaison("types complets", relu, message.size);
            } else if (message.size == 8) {
                paquetValide = lireQuantifie(message, relu);
                if (paquetValide) afficherComparaison("quantifié", relu, message.size);
            } else {
                std::cout << "[Serveur] Taille inattendue : " << message.size
                          << " octets. Message ignoré.\n";
            }

            if (paquetValide) ++paquetsRecus;
            else if (message.size == 18 || message.size == 8)
                std::cout << "[Serveur] Le paquet est incomplet ou invalide.\n";

            if (paquetsRecus == 2) {
                // L'accusé permet au client d'attendre la réception avant de fermer.
                const NkNetResult accuse = serveur.SendTo(message.from, &ACCUSE_RECEPTION, 1);
                if (accuse == NkNetResult::NK_NET_OK)
                    std::cout << "[Serveur] Les deux paquets ont été reçus.\n";
                else
                    std::cout << "[Serveur] L'accusé de réception n'a pas pu être envoyé.\n";
                NkChrono::SleepMilliseconds(100); // laisser partir l'accusé sur le réseau
                break;
            }
        }

        if (paquetsRecus < 2) {
            NkChrono::SleepMilliseconds(10);
            ++toursAttente;
        }
    }

    const bool termine = paquetsRecus == 2;
    if (!termine)
        std::cout << "[Serveur] Délai dépassé : " << paquetsRecus << " paquet(s) sur 2.\n";

    serveur.Shutdown();
    return termine ? 0 : 1;
}

int lancerClient(const char* adresseServeur) {
    // Les deux buffers restent en vie jusqu'à la fin de l'envoi.
    uint8 bufferComplet[BUFFER_CAPACITE] = {};
    uint8 bufferQuantifie[BUFFER_CAPACITE] = {};
    uint32 octetsComplets = 0, bitsComplets = 0;
    uint32 octetsQuantifies = 0, bitsQuantifies = 0;

    if (!ecrireComplet(bufferComplet, octetsComplets, bitsComplets) ||
        !ecrireQuantifie(bufferQuantifie, octetsQuantifies, bitsQuantifies)) {
        std::cout << "[Client] Un buffer est trop petit : écriture interrompue.\n";
        return 1;
    }

    std::cout << "[Client] Types complets : " << octetsComplets << " octets, "
              << bitsComplets << " bits.\n"
              << "[Client] Quantifié : " << octetsQuantifies << " octets, "
              << bitsQuantifies << " bits.\n";

    NkConnectionManager client;
    NkAtomic<bool> envoiTermine{false};
    NkAtomic<bool> envoisReussis{false};

    // Ce callback vient du fil réseau : les paquets partent seulement après connexion.
    client.onPeerConnected = [&](NkPeerId pair) {
        const NkNetResult complet = client.SendTo(pair, bufferComplet, octetsComplets);
        const NkNetResult quantifie = client.SendTo(pair, bufferQuantifie, octetsQuantifies);
        envoisReussis.Store(complet == NkNetResult::NK_NET_OK &&
                            quantifie == NkNetResult::NK_NET_OK);
        envoiTermine.Store(true);
    };

    const NkNetResult connexion = client.Connect(NkAddress(adresseServeur, PORT_SERVEUR));
    if (connexion != NkNetResult::NK_NET_OK) {
        std::cout << "[Client] Connexion impossible : "
                  << net::NkNetResultStr(connexion) << '\n';
        return 1;
    }

    std::cout << "[Client] Connexion demandée à " << adresseServeur
              << ':' << PORT_SERVEUR << ".\n";

    // Connect démarre un handshake asynchrone : on attend son callback sans bloquer en boucle serrée.
    uint32 toursAttente = 0;
    while (!envoiTermine.Load() && toursAttente < 1500) {
        NkChrono::SleepMilliseconds(10);
        ++toursAttente;
    }

    if (!envoiTermine.Load() || !envoisReussis.Load()) {
        std::cout << "[Client] Délai dépassé ou envoi incomplet. Vérifie le serveur et le pare-feu.\n";
        client.Shutdown();
        return 1;
    }

    std::cout << "[Client] Envoi des deux paquets accepté. Attente de confirmation...\n";

    bool accuseRecu = false;
    toursAttente = 0;
    while (!accuseRecu && toursAttente < 3000) {
        NkVector<NkReceiveMsg> messages;
        client.DrainAll(messages);
        for (const NkReceiveMsg& message : messages) {
            if (message.size == 1 && message.data[0] == ACCUSE_RECEPTION) {
                accuseRecu = true;
                std::cout << "[Client] Le serveur confirme la réception des deux paquets.\n";
                break;
            }
        }
        if (!accuseRecu) {
            NkChrono::SleepMilliseconds(10);
            ++toursAttente;
        }
    }

    if (!accuseRecu)
        std::cout << "[Client] Aucun accusé reçu avant le délai limite.\n";

    client.Shutdown();
    return accuseRecu ? 0 : 1;
}

} // namespace

int nkmain(const NkEntryState& state) {
    const NkNetResult initialisation = NkSocket::PlatformInit();
    if (initialisation != NkNetResult::NK_NET_OK) {
        std::cout << "Initialisation de NKNetwork impossible : "
                  << net::NkNetResultStr(initialisation) << '\n';
        return 1;
    }

    std::cout.setf(std::ios::fixed);
    std::cout.precision(3);

    int codeRetour = 0;
    if (state.args.Size() < 2) {
        std::cout << "Utilisation :\n"
                  << "  octets serveur\n"
                  << "  octets client 127.0.0.1\n"
                  << "Sur deux machines, remplace 127.0.0.1 par l'IP locale du serveur.\n";
        codeRetour = 1;
    } else if (state.args[1] == "serveur") {
        codeRetour = lancerServeur();
    } else if (state.args[1] == "client") {
        const char* adresse = state.args.Size() >= 3
            ? state.args[2].CStr()
            : "127.0.0.1";
        codeRetour = lancerClient(adresse);
    } else {
        std::cout << "Rôle inconnu : utilise 'serveur' ou 'client'.\n";
        codeRetour = 1;
    }

    NkSocket::PlatformShutdown();
    return codeRetour;
}
