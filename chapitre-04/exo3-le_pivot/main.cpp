#include <iostream>
#include <string>
#include <algorithm>

int main()
{
    // -------------------------------------------------------------------------
    // Le premier nombre indique combien de rectangles nous devons traiter.
    // -------------------------------------------------------------------------
    int N;
    std::cin >> N;

    // Compteur du nombre d'angles refusés.
    long long refuses = 0;

    // -------------------------------------------------------------------------
    // On traite les rectangles un par un.
    // -------------------------------------------------------------------------
    for (int i = 0; i < N; ++i)
    {
        // ---------------------------------------------------------------------
        // Données reçues pour un rectangle
        // ---------------------------------------------------------------------
        std::string nom;

        long long w;
        long long h;

        long long px;
        long long py;

        long long ox;
        long long oy;

        long long sx;
        long long sy;

        long long angle;

        // Lecture des 10 informations :
        //
        // nom w h px py ox oy sx sy angle
        std::cin
            >> nom
            >> w
            >> h
            >> px
            >> py
            >> ox
            >> oy
            >> sx
            >> sy
            >> angle;

        // ---------------------------------------------------------------------
        // 1. Vérifier que l'angle est un multiple de 90
        // ---------------------------------------------------------------------
        if (angle % 90 != 0)
        {
            ++refuses;

            std::cout << nom << " ANGLE REFUSE\n";

            // Ce rectangle est terminé.
            // On passe directement au suivant.
            continue;
        }

        // ---------------------------------------------------------------------
        // 2. Ramener l'angle dans [0, 359]
        //
        // Exemple :
        // -90  -> 270
        // 450  -> 90
        // -180 -> 180
        // ---------------------------------------------------------------------
        long long angleNormalise = angle % 360;

        if (angleNormalise < 0)
        {
            angleNormalise += 360;
        }

        // ---------------------------------------------------------------------
        // 3. Déterminer le cosinus et le sinus exacts pour les 4 angles
        //
        // Pas besoin de sin() ou cos() :
        // les angles autorisés sont seulement 0, 90, 180 et 270.
        // ---------------------------------------------------------------------
        long long c;
        long long s;

        if (angleNormalise == 0)
        {
            c = 1;
            s = 0;
        }
        else if (angleNormalise == 90)
        {
            c = 0;
            s = 1;
        }
        else if (angleNormalise == 180)
        {
            c = -1;
            s = 0;
        }
        else
        {
            // angleNormalise == 270
            c = 0;
            s = -1;
        }

        // ---------------------------------------------------------------------
        // 4. Les quatre coins locaux du rectangle
        //
        // Ordre obligatoire :
        //
        // 1. haut-gauche
        // 2. haut-droit
        // 3. bas-droit
        // 4. bas-gauche
        // ---------------------------------------------------------------------
        long long localX[4] = {0, w, w, 0};
        long long localY[4] = {0, 0, h, h};

        // ---------------------------------------------------------------------
        // 5. Tableau contenant les quatre coins après transformation
        // ---------------------------------------------------------------------
        long long worldX[4];
        long long worldY[4];

        // ---------------------------------------------------------------------
        // 6. Transformer chacun des quatre coins
        // ---------------------------------------------------------------------
        for (int coin = 0; coin < 4; ++coin)
        {
            // -------------------------------------------------------------
            // Étape A :
            // retirer l'origine
            // -------------------------------------------------------------
            long long ax = localX[coin] - ox;
            long long ay = localY[coin] - oy;

            // -------------------------------------------------------------
            // Étape B :
            // appliquer l'échelle
            // -------------------------------------------------------------
            ax = ax * sx;
            ay = ay * sy;

            // -------------------------------------------------------------
            // Étape C :
            // appliquer la rotation
            //
            // Formules données dans l'énoncé :
            //
            // rx = ax * c - ay * s
            // ry = ax * s + ay * c
            // -------------------------------------------------------------
            long long rx = ax * c - ay * s;
            long long ry = ax * s + ay * c;

            // -------------------------------------------------------------
            // Étape D :
            // ajouter la position dans le monde
            // -------------------------------------------------------------
            worldX[coin] = px + rx;
            worldY[coin] = py + ry;
        }

        // ---------------------------------------------------------------------
        // 7. Calculer la boîte englobante
        // ---------------------------------------------------------------------
        long long minX = worldX[0];
        long long maxX = worldX[0];

        long long minY = worldY[0];
        long long maxY = worldY[0];

        for (int coin = 1; coin < 4; ++coin)
        {
            minX = std::min(minX, worldX[coin]);
            maxX = std::max(maxX, worldX[coin]);

            minY = std::min(minY, worldY[coin]);
            maxY = std::max(maxY, worldY[coin]);
        }

        // ---------------------------------------------------------------------
        // 8. Afficher les quatre coins
        //
        // L'ordre est :
        // HG -> HD -> BD -> BG
        // ---------------------------------------------------------------------
        std::cout
            << nom
            << " COINS "
            << worldX[0] << ' ' << worldY[0] << ' '
            << worldX[1] << ' ' << worldY[1] << ' '
            << worldX[2] << ' ' << worldY[2] << ' '
            << worldX[3] << ' ' << worldY[3]
            << '\n';

        // ---------------------------------------------------------------------
        // 9. Afficher la boîte englobante
        // ---------------------------------------------------------------------
        std::cout
            << nom
            << " BOITE "
            << minX << ' '
            << minY << ' '
            << maxX << ' '
            << maxY
            << '\n';
    }

    // -------------------------------------------------------------------------
    // 10. Bilan final
    // -------------------------------------------------------------------------
    std::cout << "REFUSES " << refuses << '\n';

    return 0;
}