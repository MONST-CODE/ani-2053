#include <iostream>
#include <string>

int main()
{
    // -------------------------------------------------------------------------
    // 1. Les compteurs globaux
    // -------------------------------------------------------------------------
    long long totalPoints = 0;
    long long totalSegments = 0;
    long long totalTriangles = 0;
    long long totalRefuses = 0;

    // -------------------------------------------------------------------------
    // 2. Le premier nombre indique combien de listes nous devons traiter
    //
    // Exemple :
    // 5
    // TRIANGLES 7
    // LINE_STRIP 5
    // ...
    //
    // Ici, N vaut 5 : nous devons donc traiter 5 lignes.
    // -------------------------------------------------------------------------
    int N;
    std::cin >> N;

    // -------------------------------------------------------------------------
    // 3. On traite les N lignes une par une
    // -------------------------------------------------------------------------
    for (int i = 0; i < N; ++i)
    {
        // -------------------------------------------------------------
        // Variables relatives à UNE seule entrée
        // -------------------------------------------------------------
        std::string typeSaisi;
        long long s;

        long long nombreFormes = 0;
        long long restants = 0;

        // On lit :
        // - le type
        // - le nombre de sommets
        //
        // Exemple :
        // TRIANGLES 7
        //
        // typeSaisi = "TRIANGLES"
        // s = 7
        std::cin >> typeSaisi >> s;

        // -------------------------------------------------------------
        // CAS 1 : POINTS
        //
        // Chaque sommet devient directement un point.
        //
        // Exemple :
        // POINTS 5
        //
        // => 5 points
        // => 0 sommet restant
        // -------------------------------------------------------------
        if (typeSaisi == "POINTS")
        {
            nombreFormes = s;
            restants = 0;

            totalPoints += nombreFormes;

            std::cout << "POINTS "
                      << s << " "
                      << nombreFormes
                      << " POINTS "
                      << restants
                      << "\n";
        }

        // -------------------------------------------------------------
        // CAS 2 : LINES
        //
        // Il faut 2 sommets pour former 1 segment.
        //
        // Exemple :
        // LINES 5
        //
        // 5 / 2 = 2 segments
        // 5 % 2 = 1 sommet restant
        // -------------------------------------------------------------
        else if (typeSaisi == "LINES")
        {
            nombreFormes = s / 2;
            restants = s % 2;

            totalSegments += nombreFormes;

            std::cout << "LINES "
                      << s << " "
                      << nombreFormes
                      << " SEGMENTS "
                      << restants
                      << "\n";
        }

        // -------------------------------------------------------------
        // CAS 3 : LINE_STRIP
        //
        // Une ligne brisée de s sommets forme :
        //
        // s - 1 segments, si s >= 2
        //
        // Sinon :
        // 0 segment
        // s sommet(s) restant(s)
        //
        // Exemple :
        // LINE_STRIP 5
        // => 4 segments
        //
        // LINE_STRIP 1
        // => 0 segment, 1 restant
        // -------------------------------------------------------------
        else if (typeSaisi == "LINE_STRIP")
        {
            if (s >= 2)
            {
                nombreFormes = s - 1;
                restants = 0;
            }
            else
            {
                nombreFormes = 0;
                restants = s;
            }

            totalSegments += nombreFormes;

            std::cout << "LINE_STRIP "
                      << s << " "
                      << nombreFormes
                      << " SEGMENTS "
                      << restants
                      << "\n";
        }

        // -------------------------------------------------------------
        // CAS 4 : TRIANGLES
        //
        // Il faut 3 sommets pour former 1 triangle.
        //
        // Exemple :
        // TRIANGLES 7
        //
        // 7 / 3 = 2 triangles
        // 7 % 3 = 1 sommet restant
        // -------------------------------------------------------------
        else if (typeSaisi == "TRIANGLES")
        {
            nombreFormes = s / 3;
            restants = s % 3;

            totalTriangles += nombreFormes;

            std::cout << "TRIANGLES "
                      << s << " "
                      << nombreFormes
                      << " TRIANGLES "
                      << restants
                      << "\n";
        }

        // -------------------------------------------------------------
        // CAS 5 : TRIANGLE_STRIP
        //
        // À partir de 3 sommets :
        //
        // nombre de triangles = s - 2
        //
        // Si s < 3 :
        // 0 triangle
        // s sommets restants
        // -------------------------------------------------------------
        else if (typeSaisi == "TRIANGLE_STRIP")
        {
            if (s >= 3)
            {
                nombreFormes = s - 2;
                restants = 0;
            }
            else
            {
                nombreFormes = 0;
                restants = s;
            }

            totalTriangles += nombreFormes;

            std::cout << "TRIANGLE_STRIP "
                      << s << " "
                      << nombreFormes
                      << " TRIANGLES "
                      << restants
                      << "\n";
        }

        // -------------------------------------------------------------
        // CAS 6 : TRIANGLE_FAN
        //
        // Même règle que TRIANGLE_STRIP :
        //
        // si s >= 3 :
        //     s - 2 triangles
        //
        // sinon :
        //     0 triangle
        //     s sommets restants
        // -------------------------------------------------------------
        else if (typeSaisi == "TRIANGLE_FAN")
        {
            if (s >= 3)
            {
                nombreFormes = s - 2;
                restants = 0;
            }
            else
            {
                nombreFormes = 0;
                restants = s;
            }

            totalTriangles += nombreFormes;

            std::cout << "TRIANGLE_FAN "
                      << s << " "
                      << nombreFormes
                      << " TRIANGLES "
                      << restants
                      << "\n";
        }

        // -------------------------------------------------------------
        // CAS 7 : TYPE REFUSÉ
        //
        // QUADS est refusé.
        //
        // Tout autre mot inconnu est également refusé.
        //
        // Exemple :
        // QUADS 8
        //
        // => QUADS 8 REFUSE
        //
        // Important :
        // "quads" est aussi refusé.
        // -------------------------------------------------------------
        else
        {
            ++totalRefuses;

            std::cout << typeSaisi
                      << " "
                      << s
                      << " REFUSE\n";
        }
    }

    // -------------------------------------------------------------------------
    // 4. Bilan global
    //
    // Ces quatre lignes doivent obligatoirement être dans cet ordre.
    // -------------------------------------------------------------------------
    std::cout << "POINTS " << totalPoints << "\n";
    std::cout << "SEGMENTS " << totalSegments << "\n";
    std::cout << "TRIANGLES " << totalTriangles << "\n";
    std::cout << "REFUSES " << totalRefuses << "\n";

    return 0;
}