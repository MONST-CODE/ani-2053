#include "NKWindow/NKWindow.h"
#include "NKWindow/NKMain.h"
using namespace nkentseu ;

int nkmain(const nkentseu::NkEntryState& state)
{
    NkWindowConfig config3;
    config3.title = "EXO 4";
    config3.width = 800;
    config3.height = 600;
    NkWindow fenetre(config3);

    while ((fenetre.IsOpen()))
    {
        nkentseu::NkEvent* event = nullptr ;
        while((event = nkentseu::NkEvents().PollEvent()) != nullptr)
        {
            //Fermeture sur la croix 
            if (event->Is<nkentseu::NkWindowCloseEvent>())
            {
                fenetre.Close();
            }
            //T
            
            if(auto taille = event->As<NkWindowResizeEvent>())
            {

             auto size = fenetre.GetSize();
             auto displaySize = fenetre.GetDisplaySize();
             float32 scale = fenetre.GetDpiScale();
             std::cout<<"la taille de la fenetre est ["<<size.height<<","<<size.width<<"]"<<"la Taille de l'ecran est "<<"["<<displaySize.width<<" , "<<displaySize.height<<"]"<<std::endl;
             std::cout<<"le Scale est "<<"["<<size.width*scale<<" , "<<size.height*scale<<"]"<<std::endl;

            }
            


        }
    }
    return 0;
}