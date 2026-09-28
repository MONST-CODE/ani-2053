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