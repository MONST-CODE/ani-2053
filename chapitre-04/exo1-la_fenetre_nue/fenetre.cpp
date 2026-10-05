#include "NKCanvas/App/NkCanvasApp.h"
#include "NKWindow/NKMain.h"
using namespace nkentseu;
using namespace nkentseu::renderer;

class fenetre_nue : public NkCanvasApp
{
   public: fenetre_nue()
    {
        Config().title = "fenetre";
        Config().width = 800 ;
        Config().height = 600 ;
        Config().clearColor = NkColor2D(255,10,20,30);
    }
    
};

int nkmain(const NkEntryState& State)
{
    return NkCanvasApp::Run<fenetre_nue>(State);
}