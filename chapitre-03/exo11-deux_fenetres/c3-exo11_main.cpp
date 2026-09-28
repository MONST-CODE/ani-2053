#include "NKWindow/NKWindow.h"
#include "NKWindow/NKMain.h"
using namespace nkentseu ;

int nkmain(const NkEntryState &state) {

    //On cree "config1" ET "config2" nos variables de types NkWindowConfig 

    NkWindowConfig config1,config2;

    //On leur Passe des Parametre telque le titre de notre pages et les dimensions de la fenetre
    //config1
    config1.title = "Ma Fentre Nkentseu";
    config1.width = 800;
    config1.height = 600;
    //config2
    config2.title = "MA Deuxiemme Fenetre Nkentseu";
    config2.width = 1280;
    config2.height = 720;
    //Creation de la fenetre et Verification de la bonne Creation de celle ci
    
    nkentseu::NkWindow window(config1);
    nkentseu::NkWindow window1(config2);
    if(!window.IsOpen()){
        logger.Error("Echec de l'initialisation de la fenetre");
    }

    //Creation et gestion de la boucle des Evenements

    if(!window1.IsOpen()){
        logger.Error("Ca cuit la 2eme fenetre a refuser de s'ouvrir");
    }

    //Boucle D'evenement
    while(window.IsOpen() && window1.IsOpen())
    {
        nkentseu::NkEvent* event = nullptr;

        while ((event = nkentseu::NkEvents().PollEvent()) != nullptr)
        {
            //Gestion de l'evenemt de clic sur la croix rouge de la Fenetre 1

            if(event->Is<nkentseu::NkWindowCloseEvent>())

            {
                window.Close();
            }
            //Gestion de l'evenemt de clic sur la croix rouge de la Fenetre 2

            if(event->Is<nkentseu::NkWindowCloseEvent>())

            {
                window1.Close();
            }

           if(window.IsClickThrough())
           {
              int a = 0;
              std::cout<<"Je Suis La Premiere Fenetre J'ai deja Recus "<<a++<<" clicks"<<std::endl;
           }

            // code ,Serie D'evenemnt
        
           

            if(window1.IsClickThrough())

            {
                int b = 0;
                std::cout<<"Je Suis la Deuxieme Fenetre j'ai recus "<<b++<<" clicks"<<std::endl;
            }
            // code ,Serie D'evenemnt
        }
    }
    return 0;
}