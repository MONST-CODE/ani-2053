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
    //Creation de la fenetre et Verification de la bonne Creation de celle ci
    
    nkentseu::NkWindow window(config);
    if(!window.IsOpen()){
        logger.Error("Echec de l'initialisation de la fenetre");
    }
    NkDialogs boites;
    NkString Message;

    //Boucle D'evenement
    while(window.IsOpen())
    {

        nkentseu::NkEvent* event = nullptr;

        while ((event = nkentseu::NkEvents().PollEvent()) != nullptr)
        {
            //Gestion de l'evenemt de clic sur la croix rouge de la Fenetre

            if(event->Is<nkentseu::NkWindowCloseEvent>())
            {
                window.Close();
            }
            if(auto* key = event->As<NkKeyPressEvent>())
            {
                switch (key->GetKey())
                {
                case NkKey::NK_F :
                    boites.OpenFileDialog();
                    break;
                case NkKey::NK_D :
                    boites.OpenFolderDialog();
                    break;
                case NkKey::NK_W :
                    boites.OpenMessageBox("Entrer votre message",Message,1);
                    break;
                case NkKey::NK_S :
                    boites.SaveFileDialog();
                    break;
                
                default:
                    break;
                }
            }
            // code ,Serie D'evenement
        }
        
    }
    return 0;
}