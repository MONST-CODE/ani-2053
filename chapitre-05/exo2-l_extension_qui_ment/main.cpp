#include <iostream>
#include <string>
#include <vector>
#include <cctype>

// ============================================================
// 1. CONVERSION DE L'HEXADECIMAL EN OCTETS
// ============================================================

// Convertit un chiffre hexadecimal en valeur entre 0 et 15.
// Retourne -1 si le caractere n'est pas hexadecimal.
int valeurHex(char c)
{
    if (c >= '0' && c <= '9')
    {
        return c - '0';
    }

    if (c >= 'A' && c <= 'F')
    {
        return c - 'A' + 10;
    }

    if (c >= 'a' && c <= 'f')
    {
        return c - 'a' + 10;
    }

    return -1;
}

// Convertit une chaine hexadecimale en octets.
// Chaque paire de caracteres represente un octet.
// Le tiret '-' indique qu'aucun octet n'est fourni.
std::vector<unsigned char> decoderHex(const std::string& texte)
{
    std::vector<unsigned char> octets;

    if (texte == "-")
    {
        return octets;
    }

    // Une chaine hexadecimale doit contenir un nombre pair
    // de caracteres.
    if (texte.size() % 2 != 0)
    {
        return {};
    }

    for (std::size_t i = 0; i < texte.size(); i += 2)
    {
        int haut = valeurHex(texte[i]);
        int bas = valeurHex(texte[i + 1]);

        // Rejeter une chaine contenant un chiffre incorrect.
        if (haut < 0 || bas < 0)
        {
            return {};
        }

        int valeur = haut * 16 + bas;

        octets.push_back(
            static_cast<unsigned char>(valeur)
        );
    }

    return octets;
}

// ============================================================
// 2. RECONNAISSANCE DU FORMAT REEL DU FICHIER
// ============================================================

// Reconnait le format en examinant les octets fournis.
// Les regles sont appliquees dans l'ordre de l'enonce.
// Une chaine vide signifie qu'aucun format n'est reconnu.
std::string reconnaitreFormat(
    long long taille,
    const std::vector<unsigned char>& octets)
{
    const std::size_t n = octets.size();

    // Regle generale : les fichiers de moins de 4 octets
    // sont refuses immediatement.
    // Aucun message supplementaire ne doit etre affiche.
    if (taille < 4)
    {
        return "";
    }

    // --------------------------------------------------------
    // PNG
    // Signature : 89 50 4E 47
    // La taille totale doit etre d'au moins 8 octets.
    // --------------------------------------------------------
    if (taille >= 8 &&
        n >= 4 &&
        octets[0] == 0x89 &&
        octets[1] == 0x50 &&
        octets[2] == 0x4E &&
        octets[3] == 0x47)
    {
        return "PNG";
    }

    // --------------------------------------------------------
    // JPEG
    // Signature : FF D8 FF
    // --------------------------------------------------------
    if (n >= 3 &&
        octets[0] == 0xFF &&
        octets[1] == 0xD8 &&
        octets[2] == 0xFF)
    {
        return "JPEG";
    }

    // --------------------------------------------------------
    // BMP
    // Signature : BM
    // --------------------------------------------------------
    if (n >= 2 &&
        octets[0] == 0x42 &&
        octets[1] == 0x4D)
    {
        return "BMP";
    }

    // --------------------------------------------------------
    // QOI
    // Signature : qoif
    // --------------------------------------------------------
    if (n >= 4 &&
        octets[0] == 0x71 &&
        octets[1] == 0x6F &&
        octets[2] == 0x69 &&
        octets[3] == 0x66)
    {
        return "QOI";
    }

    // --------------------------------------------------------
    // GIF
    // Signature : GIF8
    // --------------------------------------------------------
    if (n >= 4 &&
        octets[0] == 0x47 &&
        octets[1] == 0x49 &&
        octets[2] == 0x46 &&
        octets[3] == 0x38)
    {
        return "GIF";
    }

    // --------------------------------------------------------
    // ICO
    // Signatures : 00 00 01 00 ou 00 00 02 00
    // --------------------------------------------------------
    if (n >= 4 &&
        octets[0] == 0x00 &&
        octets[1] == 0x00 &&
        (octets[2] == 0x01 || octets[2] == 0x02) &&
        octets[3] == 0x00)
    {
        return "ICO";
    }

    // --------------------------------------------------------
    // HDR
    // Signature : #?
    // La taille totale doit etre d'au moins 10 octets.
    // --------------------------------------------------------
    if (taille >= 10 &&
        n >= 2 &&
        octets[0] == 0x23 &&
        octets[1] == 0x3F)
    {
        return "HDR";
    }

    // --------------------------------------------------------
    // EXR
    // Signature : 76 2F 31 01
    // --------------------------------------------------------
    if (n >= 4 &&
        octets[0] == 0x76 &&
        octets[1] == 0x2F &&
        octets[2] == 0x31 &&
        octets[3] == 0x01)
    {
        return "EXR";
    }

    // --------------------------------------------------------
    // PBM, PGM et PPM
    // Premier octet : P (50)
    // Deuxieme octet : chiffre ASCII entre 1 et 6.
    // --------------------------------------------------------
    if (n >= 2 &&
        octets[0] == 0x50 &&
        octets[1] >= 0x31 &&
        octets[1] <= 0x36)
    {
        switch (octets[1])
        {
            case 0x31:
            case 0x34:
                return "PBM";

            case 0x32:
            case 0x35:
                return "PGM";

            case 0x33:
            case 0x36:
                return "PPM";
        }
    }

    // --------------------------------------------------------
    // TGA
    // Ce format est suppose a partir du troisieme octet.
    // La taille totale doit etre d'au moins 18 octets.
    // --------------------------------------------------------
    if (taille >= 18 && n >= 3)
    {
        unsigned char typeImage = octets[2];

        if (typeImage == 0x00 ||
            typeImage == 0x01 ||
            typeImage == 0x02 ||
            typeImage == 0x03 ||
            typeImage == 0x09 ||
            typeImage == 0x0A ||
            typeImage == 0x0B)
        {
            return "TGA";
        }
    }

    // --------------------------------------------------------
    // SVG
    // On ignore d'abord un eventuel BOM UTF-8.
    // On ignore ensuite les espaces autorises.
    // --------------------------------------------------------
    std::size_t position = 0;

    if (n >= 3 &&
        octets[0] == 0xEF &&
        octets[1] == 0xBB &&
        octets[2] == 0xBF)
    {
        position = 3;
    }

    // Espaces, tabulations et retours a la ligne.
    while (position < n)
    {
        unsigned char b = octets[position];

        if (b != 0x20 &&
            b != 0x09 &&
            b != 0x0A &&
            b != 0x0D)
        {
            break;
        }

        ++position;
    }

    // SVG commencant par "<?xml".
    if (position + 5 <= n &&
        octets[position]     == 0x3C &&
        octets[position + 1] == 0x3F &&
        octets[position + 2] == 0x78 &&
        octets[position + 3] == 0x6D &&
        octets[position + 4] == 0x6C)
    {
        return "SVG";
    }

    // SVG commencant directement par "<svg".
    if (position + 4 <= n &&
        octets[position]     == 0x3C &&
        octets[position + 1] == 0x73 &&
        octets[position + 2] == 0x76 &&
        octets[position + 3] == 0x67)
    {
        return "SVG";
    }

    // Aucun format reconnu.
    return "";
}

// ============================================================
// 3. EXTRACTION ET NORMALISATION DE L'EXTENSION
// ============================================================

// Extrait le texte situe apres le dernier point du nom.
// Convertit ensuite l'extension en minuscules.
std::string extensionDe(const std::string& nom)
{
    std::size_t position = nom.find_last_of('.');

    // Aucun point : aucune extension.
    if (position == std::string::npos)
    {
        return "";
    }

    std::string extension = nom.substr(position + 1);

    for (char& c : extension)
    {
        c = static_cast<char>(
            std::tolower(static_cast<unsigned char>(c))
        );
    }

    return extension;
}

// ============================================================
// 4. VERIFICATION DE LA CORRESPONDANCE FORMAT / EXTENSION
// ============================================================

// Renvoie true si l'extension est autorisee pour le format.
bool extensionCorrecte(
    const std::string& format,
    const std::string& extension)
{
    if (format == "PNG")
    {
        return extension == "png";
    }

    if (format == "JPEG")
    {
        return extension == "jpg" ||
               extension == "jpeg";
    }

    if (format == "BMP")
    {
        return extension == "bmp";
    }

    if (format == "QOI")
    {
        return extension == "qoi";
    }

    if (format == "GIF")
    {
        return extension == "gif";
    }

    if (format == "ICO")
    {
        return extension == "ico" ||
               extension == "cur";
    }

    if (format == "HDR")
    {
        return extension == "hdr";
    }

    if (format == "EXR")
    {
        return extension == "exr";
    }

    if (format == "PBM")
    {
        return extension == "pbm";
    }

    if (format == "PGM")
    {
        return extension == "pgm";
    }

    if (format == "PPM")
    {
        return extension == "ppm";
    }

    if (format == "TGA")
    {
        return extension == "tga";
    }

    if (format == "SVG")
    {
        return extension == "svg";
    }

    return false;
}

// ============================================================
// 5. PROGRAMME PRINCIPAL
// ============================================================

int main()
{
    int N;

    if (!(std::cin >> N))
    {
        return 0;
    }

    long long lus = 0;
    long long mensonges = 0;
    long long refuses = 0;

    for (int i = 0; i < N; ++i)
    {
        std::string nom;
        std::string texteHex;
        long long taille;

        // Lecture des informations du fichier.
        std::cin >> nom >> taille >> texteHex;

        // Conversion des octets.
        std::vector<unsigned char> octets =
            decoderHex(texteHex);

        // Reconnaissance du format reel.
        std::string format =
            reconnaitreFormat(taille, octets);

        // Aucun format reconnu.
        if (format.empty())
        {
            std::cout << nom << " REFUSE\n";

            ++refuses;
            continue;
        }

        // Le fichier est reconnu, meme si son extension ment.
        ++lus;

        // Extraction et verification de l'extension.
        std::string extension = extensionDe(nom);

        if (extensionCorrecte(format, extension))
        {
            std::cout << nom << ' '
                      << format << " OK\n";
        }
        else
        {
            std::cout << nom << ' '
                      << format << " MENT\n";

            ++mensonges;
        }
    }

    // Bilan final.
    std::cout << "LUS " << lus << '\n';
    std::cout << "MENSONGES " << mensonges << '\n';
    std::cout << "REFUSES " << refuses << '\n';

    return 0;
}