#include <iostream>
#include <cmath>

int main()
{
    // -----------------------------------------------------------------
    // Valeur exacte de pi demandée par l'énoncé.
    // -----------------------------------------------------------------
    const double PI = 3.141592653589793;

    // -----------------------------------------------------------------
    // Le premier nombre indique combien de cercles nous devons traiter.
    // -----------------------------------------------------------------
    int N;
    std::cin >> N;

    // -----------------------------------------------------------------
    // Compteurs du bilan final.
    // -----------------------------------------------------------------
    long long nombreVisibles = 0;
    long long nombreRefuses = 0;

    // -----------------------------------------------------------------
    // On traite chaque cercle.
    // -----------------------------------------------------------------
    for (int i = 0; i < N; ++i)
    {
        // -------------------------------------------------------------
        // r = rayon du cercle
        // n = nombre de segments
        // -------------------------------------------------------------
        long long r;
        long long n;

        std::cin >> r >> n;

        // -------------------------------------------------------------
        // RÈGLE 1
        //
        // Un cercle polygonal doit avoir au moins 3 segments.
        // -------------------------------------------------------------
        if (n < 3)
        {
            ++nombreRefuses;

            std::cout
                << r << ' '
                << n << " REFUSE\n";

            // On passe directement au cercle suivant.
            continue;
        }

        // -------------------------------------------------------------
        // RÈGLE 2
        //
        // Calcul de l'écart entre le vrai cercle et le polygone.
        //
        // La fonction cos() travaille en radians.
        // PI / n est justement exprimé en radians.
        // -------------------------------------------------------------
        double angle = PI / static_cast<double>(n);

        double g =
            static_cast<double>(r)
            * (1.0 - std::cos(angle));

        // -------------------------------------------------------------
        // RÈGLE 3
        //
        // L'énoncé demande l'écart en millièmes de pixel,
        // arrondi vers le bas.
        //
        // Exemple :
        // 7.6128 pixels
        // devient 7612 millièmes.
        // -------------------------------------------------------------
        long long ecart =
            static_cast<long long>(std::floor(g * 1000.0));

        // -------------------------------------------------------------
        // RÈGLE 4
        //
        // Si l'écart est nul, aucun zoom ne permettra de voir
        // les segments.
        //
        // On ne doit surtout pas faire 100 / g lorsque g == 0.
        // -------------------------------------------------------------
        if (g == 0.0)
        {
            std::cout
                << r << ' '
                << n << ' '
                << ecart << " JAMAIS\n";

            continue;
        }

        // -------------------------------------------------------------
        // RÈGLE 5
        //
        // On cherche le plus petit pourcentage d'agrandissement
        // permettant d'atteindre un écart d'au moins 1 pixel.
        //
        // L'énoncé impose un arrondi vers le haut.
        // -------------------------------------------------------------
        long long zoom =
            static_cast<long long>(
                std::ceil(100.0 / g)
            );

        // -------------------------------------------------------------
        // RÈGLE 6
        //
        // Si le zoom nécessaire est <= 100 %,
        // les segments sont déjà visibles à taille normale.
        // -------------------------------------------------------------
        if (zoom <= 100)
        {
            ++nombreVisibles;

            std::cout
                << r << ' '
                << n << ' '
                << ecart << ' '
                << zoom << " VISIBLE\n";
        }
        else
        {
            std::cout
                << r << ' '
                << n << ' '
                << ecart << ' '
                << zoom << " INVISIBLE\n";
        }
    }

    // -----------------------------------------------------------------
    // Bilan final.
    // -----------------------------------------------------------------
    std::cout
        << "VISIBLES "
        << nombreVisibles
        << '\n';

    std::cout
        << "REFUSES "
        << nombreRefuses
        << '\n';

    return 0;
}