
#include <iostream>
#include <string>
#include <vector>

struct Groupe {
    std::string police;
    long long nombre;
    long long largeur;
    long long hauteur;
};

struct Position {
    long long x1;
    long long y1;
    long long x2;
    long long y2;
};

int main() {
    long long P, L;

    if (!(std::cin >> P >> L)) {
        return 0;
    }

    int G;
    std::cin >> G;

    // Aucun groupe : aucun calcul de texture n'est nécessaire.
    if (G == 0) {
        std::cout << "AUCUN\n";
        return 0;
    }

    std::vector<Groupe> groupes;

    long long besoin = 0;
    long long occupe = 0;

    // Lecture des groupes et calcul des surfaces.
    for (int i = 0; i < G; ++i) {
        Groupe groupe;

        std::cin >> groupe.police
                 >> groupe.nombre
                 >> groupe.largeur
                 >> groupe.hauteur;

        groupes.push_back(groupe);

        // Besoin pour le choix automatique de la largeur.
        besoin += groupe.nombre
                * (groupe.largeur + P)
                * (groupe.hauteur + P);

        // Surface réelle des glyphes, sans les marges.
        occupe += groupe.nombre
                * groupe.largeur
                * groupe.hauteur;
    }

    long long W = L;

    // Choix automatique de la largeur.
    if (W == 0) {
        W = 512;

        while (W * W < 2 * besoin && W < 4096) {
            W *= 2;
        }
    }

    long long H = W;

    bool reussi = false;
    int essaisReussis = 0;

    std::vector<Position> positions(groupes.size());

    // Huit essais au maximum.
    for (int essai = 1; essai <= 8; ++essai) {
        long long x = P;
        long long y = P;
        long long e = 0;

        bool tient = true;

        // On recommence le rangement de tous les groupes.
        std::vector<Position> tentative(groupes.size());

        for (std::size_t i = 0;
             i < groupes.size() && tient;
             ++i) {

            const Groupe& groupe = groupes[i];

            long long rw = groupe.largeur + P;
            long long rh = groupe.hauteur + P;

            // Placement de tous les glyphes du groupe.
            for (long long j = 0;
                 j < groupe.nombre;
                 ++j) {

                // Le glyphe ne tient pas sur l'étagère courante.
                if (x + rw > W - P) {
                    x = P;
                    y = y + e + P;
                    e = 0;

                    // Même sur une étagère neuve,
                    // le glyphe ne tient pas en largeur.
                    if (x + rw > W - P) {
                        tient = false;
                        break;
                    }
                }

                // Le glyphe dépasse la hauteur de la texture.
                if (y + rh > H - P) {
                    tient = false;
                    break;
                }

                // Mémorisation du premier glyphe du groupe.
                if (j == 0) {
                    tentative[i].x1 = x;
                    tentative[i].y1 = y;
                }

                // Mise à jour de la position du dernier glyphe.
                tentative[i].x2 = x;
                tentative[i].y2 = y;

                // Avance horizontale.
                x += rw;

                // La hauteur de l'étagère est le maximum
                // des hauteurs de rangement de ses glyphes.
                if (rh > e) {
                    e = rh;
                }
            }
        }

        if (tient) {
            // Toutes les positions sont valides.
            positions = tentative;
            essaisReussis = essai;
            reussi = true;
            break;
        }

        // Agrandissement selon la règle de l'énoncé.
        if (W == H) {
            W *= 2;
        } else {
            H = W;
        }
    }

    // Aucun rangement réussi après huit essais.
    if (!reussi) {
        std::cout << "ESSAIS 8\n";
        std::cout << "ECHEC\n";
        return 0;
    }

    // Informations sur le premier essai réussi.
    std::cout << "ESSAIS " << essaisReussis << '\n';
    std::cout << "TEXTURE " << W << ' ' << H << '\n';

    for (std::size_t i = 0;
         i < groupes.size();
         ++i) {

        std::cout << groupes[i].police << ' '
                  << positions[i].x1 << ' '
                  << positions[i].y1 << ' '
                  << positions[i].x2 << ' '
                  << positions[i].y2 << '\n';
    }

    // Surface de la texture et pourcentage de perte.
    long long surfaceTexture = W * H;

    long long perdu =
        (surfaceTexture - occupe) * 100 / surfaceTexture;

    std::cout << "OCCUPE " << occupe << '\n';
    std::cout << "PERDU " << perdu << '\n';

    return 0;
}
