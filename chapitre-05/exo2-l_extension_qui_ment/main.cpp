#include <iostream>
#include <string>
#include <vector>
#include <cctype>

int valeurHex(char c)
{
    // Transformer un caractère hexadécimal en nombre.
    
    if(c >= '0' && c <= '9')
    {
        return c - '0';
    }
    if(c >= 'A' && c <= 'F')
    {
        return c - 'A'+10;
    }
    if(c >= 'a' && c <= 'f')
    {
        return c - 'a'+10;
    }
    return -1; 
}

std::vector<int> decoderHex(const std::string& texte)
{
    std::vector<int> octets;
    if( texte == "-")
    {
       return octets;
    } 
    for (std::size_t i = 0; i+1<texte.size(); i+= 2){
    
     int haut = valeurHex(texte[i]);
     int bas = valeurHex(texte[i+1]) ;
     int ReelValeur = (haut * 16) + bas;
     octets.push_back(ReelValeur);
    }
    return octets;
}

std::string reconnaitreFormat(
    long long taille,
    const std::vector<int>& octets)
{
    // Tester les formats dans l'ordre EXACT de l'énoncé.
    
    // 1. taille < 4 -> aucun format
    if(taille<4)
    {
        std::cout<<"Taille n respectant la taille d'aucun format"<<std::endl;
        return "";
    }
    //
    // 2. PNG
    if(taille >= 8 && octets.size()>=4 && octets[0] == 0x89 && octets[1] == 0x50 && octets[2] == 0x4E && octets[3] == 0x47)
    {
        return "PNG";
    }
    //
    // 3. JPEG
    if(octets.size()>=3 && octets[0] == 0xFF && octets[1] == 0xD8 && octets[2] == 0xFF)
    {
        return "JPEG";
    }
    //
    // 4. BMP
    if(octets.size()>=2 && octets[0] == 0x42 && octets[1] == 0x4D)
    {
        return "BMP";
    }
    
    // 5. QOI : 71 6F 69 66
    if (octets.size() >= 4 &&
        octets[0] == 0x71 &&
        octets[1] == 0x6F &&
        octets[2] == 0x69 &&
        octets[3] == 0x66)
    {
        return "QOI";
    }

    // 6. GIF : 47 49 46 38
    if (octets.size() >= 4 &&
        octets[0] == 0x47 &&
        octets[1] == 0x49 &&
        octets[2] == 0x46 &&
        octets[3] == 0x38)
    {
        return "GIF";
    }

    // 7. ICO : 00 00 01 00 ou 00 00 02 00
    if (octets.size() >= 4 &&
        octets[0] == 0x00 &&
        octets[1] == 0x00 &&
        (octets[2] == 0x01 || octets[2] == 0x02) &&
        octets[3] == 0x00)
    {
        return "ICO";
    }

    // 8. HDR : taille >= 10 et signature 23 3F
    if (taille >= 10 &&
        octets.size() >= 2 &&
        octets[0] == 0x23 &&
        octets[1] == 0x3F)
    {
        return "HDR";
    }

    // 9. EXR : 76 2F 31 01
    if (octets.size() >= 4 &&
        octets[0] == 0x76 &&
        octets[1] == 0x2F &&
        octets[2] == 0x31 &&
        octets[3] == 0x01)
    {
        return "EXR";
    }

    // 10. PBM, PGM ou PPM : le premier octet vaut 50 ("P").
    if (octets.size() >= 2 &&
        octets[0] == 0x50 &&
        octets[1] >= 0x31 &&
        octets[1] <= 0x36)
    {
        if (octets[1] == 0x31 || octets[1] == 0x34)
        {
            return "PBM";
        }

        if (octets[1] == 0x32 || octets[1] == 0x35)
        {
            return "PGM";
        }

        if (octets[1] == 0x33 || octets[1] == 0x36)
        {
            return "PPM";
        }
    }

    // 11. TGA : ce format est supposé à partir du troisième octet.
    // Attention : ICO a déjà été testé avant TGA.
    if (taille >= 18 && octets.size() >= 3)
    {
        int typeImage = octets[2];

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

    // 12. SVG : ignorer éventuellement le BOM UTF-8.
    //Apres recherches je mesuis rendu compte qu'il yaplusieurs types de SVG
    std::size_t position = 0;

    if (octets.size() >= 3 &&
        octets[0] == 0xEF &&
        octets[1] == 0xBB &&
        octets[2] == 0xBF)
    {
        position = 3;
    }

    // Ignorer les espaces, tabulations et retours à la ligne autorisés.
    while (position < octets.size())
    {
        int b = octets[position];

        if (b != 0x20 && b != 0x09 &&
            b != 0x0A && b != 0x0D)
        {
            break;
        }

        ++position;
    }

    // SVG commençant par "<?xml".
    if (position + 5 <= octets.size() &&
        octets[position]     == 0x3C &&
        octets[position + 1] == 0x3F &&
        octets[position + 2] == 0x78 &&
        octets[position + 3] == 0x6D &&
        octets[position + 4] == 0x6C)
    {
        return "SVG";
    }

    // SVG commençant directement par "<svg".
    if (position + 4 <= octets.size() &&
        octets[position]     == 0x3C &&
        octets[position + 1] == 0x73 &&
        octets[position + 2] == 0x76 &&
        octets[position + 3] == 0x67)
    {
        return "SVG";
    }
    return ""; // aucun format reconnu
}

std::string extensionDe(const std::string& nom)
{
    // Chercher le dernier point dans le nom.
    std::size_t position = nom.find_last_of('.');

    // Aucun point = aucune extension.
    if (position == std::string::npos)
    {
        return "";
    }

    // Récupérer tout ce qui vient après le dernier point.
    std::string extension = nom.substr(position + 1);

    // Mettre l'extension en minuscules.
    for (char& c : extension)
    {
        c = static_cast<char>(
            std::tolower(static_cast<unsigned char>(c))
        );
    }

    return extension;
}

// Vérifie si l'extension correspond au format reconnu.
bool extensionCorrecte(
    const std::string& format,
    const std::string& extension)
{
    if (format == "PNG")
        return extension == "png";

    if (format == "JPEG")
        return extension == "jpg" || extension == "jpeg";

    if (format == "BMP")
        return extension == "bmp";

    if (format == "QOI")
        return extension == "qoi";

    if (format == "GIF")
        return extension == "gif";

    if (format == "ICO")
        return extension == "ico" || extension == "cur";

    if (format == "HDR")
        return extension == "hdr";

    if (format == "EXR")
        return extension == "exr";

    if (format == "PBM")
        return extension == "pbm";

    if (format == "PGM")
        return extension == "pgm";

    if (format == "PPM")
        return extension == "ppm";

    if (format == "TGA")
        return extension == "tga";

    if (format == "SVG")
        return extension == "svg";

    return false;
}

int main()
{
    int n = 0;
    std::cin >> n;

    long long lus = 0;
    long long mensonges = 0;
    long long refuses = 0;

    for (int i = 0; i < n; ++i)
    {
        std::string nom;
        long long taille = 0;
        std::string texteHex;

        // Lire le nom, la taille totale et les premiers octets.
        std::cin >> nom >> taille >> texteHex;

        // Convertir la chaîne hexadécimale en nombres.
        std::vector<int> octets = decoderHex(texteHex);

        // Déterminer le véritable format du fichier.
        std::string format = reconnaitreFormat(taille, octets);

        // Aucun format reconnu.
        if (format.empty())
        {
            std::cout << nom << " REFUSE\n";
            ++refuses;
            continue;
        }

        // Le format est reconnu, même si l'extension ment.
        ++lus;

        std::string extension = extensionDe(nom);

        if (extensionCorrecte(format, extension))
        {
            std::cout << nom << ' ' << format << " OK\n";
        }
        else
        {
            std::cout << nom << ' ' << format << " MENT\n";
            ++mensonges;
        }
    }

    // Bilan final
    std::cout << "LUS " << lus << '\n';
    std::cout << "MENSONGES " << mensonges << '\n';
    std::cout << "REFUSES " << refuses << '\n';

    return 0;
}