
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    long long D, C;

    if (!(std::cin >> D >> C)) {
        return 0;
    }

    int N;
    std::cin >> N;

    // Lecture des instants de lecture, dans l'ordre donné.
    std::vector<long long> instants(N);

    for (int i = 0; i < N; ++i) {
        std::cin >> instants[i];
    }

    // Résultats des trois simulations.
    std::vector<long long> voix(N);
    std::vector<long long> retards(N);
    std::vector<std::string> etats(N);

    long long voixMax = 0;
    long long retardMax = 0;
    int coupes = 0;

    // ---------------------------------------------------------
    // 1. Simulation avec une voix distincte par lecture.
    // ---------------------------------------------------------

    int premiereActive = 0;

    for (int i = 0; i < N; ++i) {
        // Les lectures finies à cet instant ne sont plus actives.
        while (premiereActive <= i &&
               instants[premiereActive] + D <= instants[i]) {
            ++premiereActive;
        }

        // Les instants étant triés, les lectures actives
        // forment un bloc allant de premiereActive à i.
        voix[i] = i - premiereActive + 1;

        if (voix[i] > voixMax) {
            voixMax = voix[i];
        }
    }

    // ---------------------------------------------------------
    // 2. Simulation du chargement successif des fichiers.
    // ---------------------------------------------------------

    long long finPrecedent = 0;

    for (int i = 0; i < N; ++i) {
        long long debutChargement;

        if (i == 0) {
            // Le premier chargement n'attend personne.
            debutChargement = instants[i];
        } else {
            // On attend soit la demande, soit la fin précédente.
            debutChargement = std::max(
                instants[i],
                finPrecedent
            );
        }

        long long finChargement = debutChargement + C;

        retards[i] = finChargement - instants[i];

        finPrecedent = finChargement;

        if (retards[i] > retardMax) {
            retardMax = retards[i];
        }
    }

    // ---------------------------------------------------------
    // 3. Simulation d'une seule voix rejouée.
    // ---------------------------------------------------------

    for (int i = 0; i < N; ++i) {
        // Une lecture est coupée si la suivante commence
        // strictement avant sa fin théorique.
        if (i + 1 < N &&
            instants[i + 1] < instants[i] + D) {

            etats[i] = "COUPE";
            ++coupes;
        } else {
            etats[i] = "ENTIER";
        }
    }

    // ---------------------------------------------------------
    // Affichage des résultats, sans texte supplémentaire.
    // ---------------------------------------------------------

    for (int i = 0; i < N; ++i) {
        std::cout << instants[i] << ' '
                  << voix[i] << ' '
                  << retards[i] << ' '
                  << etats[i] << '\n';
    }

    std::cout << "VOIX_MAX " << voixMax << '\n';
    std::cout << "RETARD_MAX " << retardMax << '\n';
    std::cout << "COUPES " << coupes << '\n';

    return 0;
}
