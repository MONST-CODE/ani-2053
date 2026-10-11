
#include <iostream>
#include <string>
#include <vector>

struct Glyphe {
    char caractere;
    long long avance;
    long long x0;
    long long y0;
    long long x1;
    long long y1;
};

struct Crenage {
    char gauche;
    char droite;
    long long correction;
};

// Recherche un glyphe dans la table.
// Retourne nullptr si le caractère n'existe pas.
const Glyphe* trouverGlyphe(
    const std::vector<Glyphe>& glyphes,
    char caractere
) {
    for (const Glyphe& glyphe : glyphes) {
        if (glyphe.caractere == caractere) {
            return &glyphe;
        }
    }

    return nullptr;
}

// Recherche la correction applicable à un couple.
// Une absence de couple équivaut à une correction nulle.
long long trouverCrenage(
    const std::vector<Crenage>& crenages,
    char gauche,
    char droite
) {
    for (const Crenage& crenage : crenages) {
        if (crenage.gauche == gauche &&
            crenage.droite == droite) {
            return crenage.correction;
        }
    }

    return 0;
}

int main() {
    int G;

    if (!(std::cin >> G)) {
        return 0;
    }

    // Lecture de la table des glyphes.
    std::vector<Glyphe> glyphes;

    for (int i = 0; i < G; ++i) {
        Glyphe glyphe;

        std::cin >> glyphe.caractere
                 >> glyphe.avance
                 >> glyphe.x0
                 >> glyphe.y0
                 >> glyphe.x1
                 >> glyphe.y1;

        glyphes.push_back(glyphe);
    }

    int K;
    std::cin >> K;

    // Lecture de la table des couples de crénage.
    std::vector<Crenage> crenages;

    for (int i = 0; i < K; ++i) {
        std::string couple;
        long long correction;

        std::cin >> couple >> correction;

        crenages.push_back({
            couple[0],
            couple[1],
            correction
        });
    }

    // Lecture du texte et de sa ligne de base.
    std::string texte;
    long long ox, oy;

    std::cin >> texte >> ox >> oy;

    long long curseur = ox;
    int absents = 0;

    // État de la boîte englobante.
    bool aDessine = false;

    long long minX = 0;
    long long minY = 0;
    long long maxX = 0;
    long long maxY = 0;

    // Traitement des caractères dans l'ordre du texte.
    for (std::size_t i = 0; i < texte.size(); ++i) {
        char caractere = texte[i];

        const Glyphe* glyphe =
            trouverGlyphe(glyphes, caractere);

        // Un glyphe absent ne fait avancer
        // ni le curseur ni le calcul du crénage.
        if (glyphe == nullptr) {
            std::cout << caractere << " ABSENT\n";
            ++absents;
            continue;
        }

        // Affichage de la position de départ du glyphe.
        std::cout << caractere << ' '
                  << curseur << '\n';

        // Seuls les rectangles de largeur et hauteur
        // strictement positives sont dessinés.
        if (glyphe->x1 > glyphe->x0 &&
            glyphe->y1 > glyphe->y0) {

            long long gauche = curseur + glyphe->x0;
            long long droite = curseur + glyphe->x1;

            long long haut = oy + glyphe->y0;
            long long bas = oy + glyphe->y1;

            if (!aDessine) {
                // Le premier rectangle initialise la boîte.
                minX = gauche;
                minY = haut;
                maxX = droite;
                maxY = bas;

                aDessine = true;
            } else {
                // Les rectangles suivants agrandissent
                // éventuellement la boîte englobante.
                if (gauche < minX) {
                    minX = gauche;
                }

                if (haut < minY) {
                    minY = haut;
                }

                if (droite > maxX) {
                    maxX = droite;
                }

                if (bas > maxY) {
                    maxY = bas;
                }
            }
        }

        // Étape 1 : appliquer l'avance du glyphe.
        curseur += glyphe->avance;

        // Étape 2 : appliquer le crénage avec
        // le caractère suivant, s'il existe.
        if (i + 1 < texte.size()) {
            curseur += trouverCrenage(
                crenages,
                caractere,
                texte[i + 1]
            );
        }
    }

    // Affichage du curseur final.
    std::cout << "CURSEUR " << curseur << '\n';

    if (!aDessine) {
        // Aucun rectangle exploitable n'a été dessiné.
        std::cout << "BOITE AUCUNE\n";
        std::cout << "MONTE 0\n";
        std::cout << "DESCEND 0\n";
        std::cout << "ECRAN RIEN\n";
    } else {
        std::cout << "BOITE "
                  << minX << ' '
                  << minY << ' '
                  << maxX << ' '
                  << maxY << '\n';

        // Distance entre la ligne de base
        // et le bord supérieur de la boîte.
        long long monte = 0;

        if (minY < oy) {
            monte = oy - minY;
        }

        // Distance entre la ligne de base
        // et le bord inférieur de la boîte.
        long long descend = 0;

        if (maxY > oy) {
            descend = maxY - oy;
        }

        std::cout << "MONTE " << monte << '\n';
        std::cout << "DESCEND " << descend << '\n';

        // Détermination du statut de l'écran.
        if (maxY <= 0) {
            std::cout << "ECRAN HORS\n";
        } else if (minY < 0) {
            std::cout << "ECRAN COUPE\n";
        } else {
            std::cout << "ECRAN VISIBLE\n";
        }
    }

    std::cout << "ABSENTS " << absents << '\n';

    return 0;
}
