#include "NKWindow/NKWindow.h"
#include "NKWindow/NKMain.h"
using namespace nkentseu;

int nkmain(const NkEntryState &state)
{
    
    NkWindowConfig config3;
    config3.title = "TAILLE MINIMALE";
    config3.width = 800;
    config3.height = 600;
    config3.resizable = true;
    config3.minWidth = 400;
    config3.minHeight = 300;

    // Creation de la fenetre

    nkentseu::NkWindow FentreExo3(config3);

    math::NkVec2T S = FentreExo3.GetSize();

    std::cout<<"LA LONGEUR APRES INITIALISATION EST "<<S.width<<" de Large et "<<S.height<<" de Haut"<<std::endl;

    if(!FentreExo3.IsOpen()) 
    {
        logger.Error("Echec Lors de l'initialisationd la fenetre");
    }

    // Boolen et Boucle
    bool IsRunning = true ;

    while(FentreExo3.IsOpen())
    {
        nkentseu::NkEvent* evenement = nullptr;
        while ((evenement = nkentseu::NkEvents().PollEvent()) != nullptr)
        {
            if(evenement->Is<nkentseu::NkWindowCloseEvent>())
            {
                IsRunning = false;
            }
            if(auto taile = evenement->As<NkWindowResizeEvent>())
            {
                math::NkVec2T S = FentreExo3.GetSize();
                std::cout<<"La Largeur actuel de la fenetre "<<S.width<<"La Hauteur "<<S.height<<std::endl;
            }
        }
        
    }
    return 0;
}