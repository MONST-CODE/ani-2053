#include "NKWindow/NKWindow.h"
#include "NKWindow/NKMain.h"
using namespace nkentseu ;

int nkmain(const NkEntryState &state) {

    //On cree "config" notre variables de types NkWindowConfig 

    NkWindowConfig config;

    //On lui Passe des Parametre telque le titre de notre pages et les dimensions de la fenetre

    config.title = "Ma Fentre Nkentseu";
    config.width = 800;
    config.height = 600;
    nkentseu::NkWindow window(config);

    //Creation de la fenetre et Verification de la bonne Creation de celle ci

    if(!window.Create(config)) {
        logger.Error(" Echec de la Creation de la fenetre");
        return -1;
    }

    //Creation d'un Boolen pour la gestion de la boucle des Evenements

    bool IsRunning = true;

    //Boucle D'evenement

    while (IsRunning){
        
        nkentseu::NkEvent* event = nullptr;

        while ((event = nkentseu::NkEvents().PollEvent()) != nullptr)
        {
            //Gestion de l'evenemt de clic sur la croix rouge de la Fenetre

            if(event->Is<nkentseu::NkWindowCloseEvent>()){
                IsRunning = false;
            }

            // code ,Serie D'evenemnt
        }
        
    }
    return 0;
}