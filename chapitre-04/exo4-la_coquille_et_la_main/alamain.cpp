#include "NKWindow/NKWindow.h"
#include "NKWindow/NKMain.h"
#include "NKEvent/NkEvent.h"
#include "NKCanvas/Core/NkContextDesc.h"
#include "NKCanvas/Core/NkGraphicsApi.h"
#include "NKCanvas/App/NkCanvasApp.h"
#include "NKCanvas/Renderer/Core/NkRenderer2D.h"
using namespace nkentseu;

int nkmain()
{
    //config 
    NkWindowConfig ConfigAlamain;

    ConfigAlamain.title = "A LA MAIN";
    ConfigAlamain.width = 800;
    ConfigAlamain.height = 600;
    //creation fentre
    NkWindow Alamain;
    //creation carre
    math::NkRect2f carre(20,20,20,20);
    //notre nkevents pour gerer la boucle d'evenements
    nkentseu::NkEvent* EventAlamain = nullptr;
    //pour le deplacement
    float32 dt=100.0f;
    //boucle d'evenement
    while (Alamain.IsOpen())
    {
        while((EventAlamain = NkEvents().PollEvent()) != nullptr)
        {
            if(EventAlamain->Is<NkWindowCloseEvent>() )
            {
                Alamain.Close();
            }
            switch(EventAlamain->GetType())
            {
            case nkentseu::NkEventType::NK_KEY_PRESSED:
            auto keypressed = EventAlamain->As<nkentseu::NkKeyPressEvent>();
            break;
            }

        }
    }
    

}