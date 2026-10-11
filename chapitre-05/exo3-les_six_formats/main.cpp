
#include <iostream>
#include <string>

struct FormatPixel {
    const char* nom;
    long long octetsParPixel;
    bool couleur;
    bool transparence;
    bool flottants;
};

// Les six formats autorisés par l'énoncé.
const FormatPixel FORMATS[] = {
    {"GRAY8",     1,  false, false, false},
    {"GRAY_A16",  2,  false, true,  false},
    {"RGB24",     3,  true,  false, false},
    {"RGBA32",    4,  true,  true,  false},
    {"RGB96F",    12, true,  false, true},
    {"RGBA128F",  16, true,  true,  true}
};

const int NOMBRE_FORMATS =
    sizeof(FORMATS) / sizeof(FORMATS[0]);

// Renvoie l'adresse du format s'il est connu, sinon nullptr.
const FormatPixel* trouverFormat(const std::string& nom) {
    for (int i = 0; i < NOMBRE_FORMATS; ++i) {
        if (nom == FORMATS[i].nom) {
            return &FORMATS[i];
        }
    }

    return nullptr;
}

// Construit les pertes dans l'ordre exigé par l'énoncé.
std::string calculerPertes(
    const FormatPixel& source,
    const FormatPixel& cible
) {
    std::string pertes;

    if (source.transparence && !cible.transparence) {
        pertes = "TRANSPARENCE";
    }

    if (source.couleur && !cible.couleur) {
        if (!pertes.empty()) {
            pertes += '+';
        }

        pertes += "COULEUR";
    }

    if (source.flottants && !cible.flottants) {
        if (!pertes.empty()) {
            pertes += '+';
        }

        pertes += "ETENDUE";
    }

    if (pertes.empty()) {
        return "AUCUNE";
    }

    return pertes;
}

int main() {
    long long w, h;
    int N;

    // Lecture des dimensions et du nombre de conversions.
    if (!(std::cin >> w >> h >> N)) {
        return 0;
    }

    const long long nombrePixels = w * h;

    long long total = 0;
    int sansPerte = 0;
    int refuses = 0;

    for (int i = 0; i < N; ++i) {
        std::string nomSource;
        std::string nomCible;

        std::cin >> nomSource >> nomCible;

        const FormatPixel* source =
            trouverFormat(nomSource);

        const FormatPixel* cible =
            trouverFormat(nomCible);

        // Une conversion est refusée si au moins un format
        // n'appartient pas à la table autorisée.
        if (source == nullptr || cible == nullptr) {
            std::cout << nomSource << ' '
                      << nomCible << " REFUSE\n";

            ++refuses;
            continue;
        }

        // Calcul des mémoires en octets.
        const long long octetsSource =
            nombrePixels * source->octetsParPixel;

        const long long octetsCible =
            nombrePixels * cible->octetsParPixel;

        const std::string pertes =
            calculerPertes(*source, *cible);

        // Affichage de la conversion.
        std::cout << nomSource << ' '
                  << nomCible << ' '
                  << octetsSource << ' '
                  << octetsCible << ' '
                  << pertes << '\n';

        // Seule la mémoire cible acceptée entre dans le total.
        total += octetsCible;

        if (pertes == "AUCUNE") {
            ++sansPerte;
        }
    }

    // Les trois lignes de bilan, même lorsque N vaut zéro.
    std::cout << "TOTAL " << total << '\n';
    std::cout << "SANS_PERTE " << sansPerte << '\n';
    std::cout << "REFUSES " << refuses << '\n';

    return 0;
}
