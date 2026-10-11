
#include <iostream>
#include <string>

int main() {
    long long seuil;
    int N;

    // Lecture du seuil et du nombre de sons.
    if (!(std::cin >> seuil >> N)) {
        return 0;
    }

    long long memoire = 0;
    int flux = 0;
    int refuses = 0;

    for (int i = 0; i < N; ++i) {
        std::string nom;

        long long frequence;
        long long canaux;
        long long bits;
        long long duree;
        long long fichier;

        // Lecture des informations du son.
        std::cin >> nom
                 >> frequence
                 >> canaux
                 >> bits
                 >> duree
                 >> fichier;

        // Vérification de la profondeur acceptée.
        if (bits != 8 &&
            bits != 16 &&
            bits != 24 &&
            bits != 32) {

            std::cout << nom << " REFUSE\n";
            ++refuses;
            continue;
        }

        // Calcul de la taille brute.
        // Toutes les multiplications précèdent la division.
        const long long brut =
            frequence * canaux * (bits / 8) * duree / 1000;

        // Pourcentage du brut occupé par le fichier.
        const long long pourcent =
            fichier * 100 / brut;

        // Choix du mode de lecture.
        if (brut > seuil) {
            std::cout << nom << ' '
                      << brut << ' '
                      << pourcent << " FLUX\n";

            ++flux;
        } else {
            std::cout << nom << ' '
                      << brut << ' '
                      << pourcent << " MEMOIRE\n";

            memoire += brut;
        }
    }

    // Bilans finaux.
    std::cout << "MEMOIRE " << memoire << '\n';
    std::cout << "FLUX " << flux << '\n';
    std::cout << "REFUSES " << refuses << '\n';

    return 0;
}
