# LE TITRE QUI INFORME
## LES MOTS DE LA CONSOLE

## Ce Que Nous avons Compris Ce que nous interpretons
## A-1-LE CODE
```cpp
#include "NkWindow/NKWindow.h"
#include "NkWindow/NKMain.h"

#include <iostream>
#include <cstdio>

using namespace nkentseu;

int nkmain(const nkentseu::NkEntryState& state)

{
    NkWindowConfig config3;

    config3.title = "TAILLE MINIMALE";
    config3.width = 800;
    config3.height = 600;
    config3.resizable = true;
    config3.minWidth = 400;
    config3.minHeight = 300;

    // Création de la fenêtre
    NkWindow FentreExo3(config3);

    // Obtenir la taille après initialisation
    math::NkVec2u S = FentreExo3.GetSize();

    std::cout
        << "LA LONGUEUR APRES INITIALISATION EST "
        << S.width
        << " de Large et "
        << S.height
        << " de Haut"
        << std::endl;

    if (!FentreExo3.IsOpen())
    {
        logger.Error("Echec lors de l'initialisation de la fenetre");
        return 1;
    }

    int i = 0;
    // Boucle d'evenement
    while (FentreExo3.IsOpen())
    {
        nkentseu::NkEvent* evenement = nullptr;

        while ((evenement = nkentseu::NkEvents().PollEvent()) != nullptr)
        {
            // Fermeture
            if (evenement->Is<nkentseu::NkWindowCloseEvent>())
            {
                FentreExo3.Close();
                break;
            }

            // Redimensionnement
            if (auto taille = evenement->As<NkWindowResizeEvent>())
            {
                S = FentreExo3.GetSize();

                ++i;

                std::cout<< "TAILLE MAXIMALE  "<< i<< " Modif ["<< S.width<< " "<< S.height<< "]"<< std::endl;

                char titre[128];

                std::snprintf(titre,sizeof(titre),"TAILLE MAXIMALE * %d Modif [%u %u]",i,S.width,S.height);

                FentreExo3.SetTitle(NkString(titre));
            }
        }
    }

    return 0;
}
```
## A-2-Ce Qui etais attendu Ce Qui etais livrer
### A-2-A Ce Qui etait ATTENDU

- Une Fentre fonctionnelle
- un Titre dynamique qui se remplace automatiquement apres chaque resize effectuer
- une fenetre qui se ferme proprement  
### A-2-B Ce Qui A ETE EFFECTUER

- Une Fentre fonctionnelle
- un Titre dynamique (informatifs) qui se remplace automatiquement apres chaque resize effectuer
- une fenetre qui se ferme proprement  