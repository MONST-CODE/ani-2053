
#include <iostream>
#include <string>
#include <vector>

// Informations d'une piste média.
struct Piste {
    std::string type;
    std::string code;
};

// Transforme une chaîne hexadécimale en octets.
// Le caractère '-' représente un fichier sans octet fourni.
std::vector<unsigned char> decoderHex(
    const std::string& hexadecimal
) {
    std::vector<unsigned char> octets;

    if (hexadecimal == "-") {
        return octets;
    }

    for (std::size_t i = 0;
         i + 1 < hexadecimal.size();
         i += 2) {

        unsigned int valeur = std::stoul(
            hexadecimal.substr(i, 2),
            nullptr,
            16
        );

        octets.push_back(
            static_cast<unsigned char>(valeur)
        );
    }

    return octets;
}

// Reconnaît le conteneur à partir des premiers octets.
// L'extension du fichier n'intervient jamais.
std::string reconnaitreConteneur(
    const std::vector<unsigned char>& b
) {
    const std::size_t n = b.size();

    // MP4 : les octets 4 à 7 contiennent "ftyp".
    if (n >= 12 &&
        b[4] == 0x66 &&
        b[5] == 0x74 &&
        b[6] == 0x79 &&
        b[7] == 0x70) {

        return "MP4";
    }

    // WEBM : signature EBML.
    if (n >= 4 &&
        b[0] == 0x1A &&
        b[1] == 0x45 &&
        b[2] == 0xDF &&
        b[3] == 0xA3) {

        return "WEBM";
    }

    // WAV : "RIFF" aux octets 0 à 3,
    // puis "WAVE" aux octets 8 à 11.
    if (n >= 12 &&
        b[0] == 0x52 &&
        b[1] == 0x49 &&
        b[2] == 0x46 &&
        b[3] == 0x46 &&
        b[8] == 0x57 &&
        b[9] == 0x41 &&
        b[10] == 0x56 &&
        b[11] == 0x45) {

        return "WAV";
    }

    // OGG : "OggS".
    if (n >= 4 &&
        b[0] == 0x4F &&
        b[1] == 0x67 &&
        b[2] == 0x67 &&
        b[3] == 0x53) {

        return "OGG";
    }

    // FLAC : "fLaC".
    if (n >= 4 &&
        b[0] == 0x66 &&
        b[1] == 0x4C &&
        b[2] == 0x61 &&
        b[3] == 0x43) {

        return "FLAC";
    }

    // MP3 : signature ID3.
    if (n >= 3 &&
        b[0] == 0x49 &&
        b[1] == 0x44 &&
        b[2] == 0x33) {

        return "MP3";
    }

    // MP3 : signature de synchronisation.
    if (n >= 2 &&
        b[0] == 0xFF &&
        b[1] >= 0xE0) {

        return "MP3";
    }

    return "INCONNU";
}

// Donne le nom du codec correspondant au code fourni.
// Un code non répertorié conserve son orthographe originale.
std::string nomCodec(const std::string& code) {
    if (code == "mp4a") {
        return "aac";
    }

    if (code == "Opus" || code == "opus") {
        return "opus";
    }

    if (code == "avc1" || code == "avc3") {
        return "h264";
    }

    if (code == "hvc1" || code == "hev1") {
        return "h265";
    }

    if (code == "vp08") {
        return "vp8";
    }

    if (code == "vp09") {
        return "vp9";
    }

    if (code == "mp4v") {
        return "mpeg4";
    }

    if (code == ".mp3") {
        return "mp3";
    }

    if (code == "twos" ||
        code == "sowt" ||
        code == "lpcm") {

        return "pcm";
    }

    return code;
}

// Détermine si le lecteur sait décoder la première piste vidéo
// en fonction de son code original, et non de son nom normalisé.
bool lecteurConnait(const std::string& code) {
    return code == "mjpa" ||
           code == "jpeg" ||
           code == "MJPG" ||
           code == "avc1" ||
           code == "avc3" ||
           code == "hvc1" ||
           code == "hev1" ||
           code == "av01";
}

int main() {
    int N;

    if (!(std::cin >> N)) {
        return 0;
    }

    int nombreMP4 = 0;
    int nombreLisibles = 0;
    int nombreInconnus = 0;

    for (int i = 0; i < N; ++i) {
        std::string nom;
        std::string hexadecimal;
        int P;

        std::cin >> nom >> hexadecimal >> P;

        // Toutes les pistes sont lues, même si le fichier
        // n'est pas un MP4.
        std::vector<Piste> pistes;

        for (int j = 0; j < P; ++j) {
            Piste piste;

            std::cin >> piste.type >> piste.code;

            pistes.push_back(piste);
        }

        // Reconnaissance du conteneur.
        const std::vector<unsigned char> octets =
            decoderHex(hexadecimal);

        const std::string conteneur =
            reconnaitreConteneur(octets);

        std::cout << nom << ' '
                  << conteneur << '\n';

        if (conteneur == "INCONNU") {
            ++nombreInconnus;
        }

        // Les pistes ne sont détaillées que pour les MP4.
        if (conteneur != "MP4") {
            continue;
        }

        ++nombreMP4;

        bool premiereVideoTrouvee = false;
        std::string verdict = "SANS_IMAGE";

        // Affichage des pistes et recherche de la première vidéo.
        for (std::size_t j = 0; j < pistes.size(); ++j) {
            const Piste& piste = pistes[j];

            const std::string typeAffiche =
                piste.type == "vide" ? "VIDEO" : "AUDIO";

            std::cout << nom << " PISTE "
                      << j + 1 << ' '
                      << typeAffiche << ' '
                      << nomCodec(piste.code) << '\n';

            // Seule la première piste vidéo détermine
            // le verdict du lecteur.
            if (!premiereVideoTrouvee &&
                piste.type == "vide") {

                premiereVideoTrouvee = true;

                if (lecteurConnait(piste.code)) {
                    verdict = "LISIBLE";
                } else {
                    verdict = "ECHEC";
                }
            }
        }

        std::cout << nom << " LECTEUR "
                  << verdict << '\n';

        if (verdict == "LISIBLE") {
            ++nombreLisibles;
        }
    }

    // Bilans finaux.
    std::cout << "MP4 " << nombreMP4 << '\n';
    std::cout << "LISIBLES " << nombreLisibles << '\n';
    std::cout << "INCONNUS " << nombreInconnus << '\n';

    return 0;
}
