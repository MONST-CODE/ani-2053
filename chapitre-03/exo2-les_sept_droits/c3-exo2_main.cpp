#include "NKWindow/NKWindow.h"
#include "NKWindow/NKMain.h"
using namespace nkentseu;

int nkmain(const NkEntryState &state) 

{

    // Variables de Config

    NkWindowConfig config ;

    //configurations de notre fenetre

    config.title = "7 fois la fenetre";
    config.width = 800;
    config.height = 600;
    config.resizable = true;
    config.centered      = true;        
    config.movable       = true;
    config.closable      = true;
    config.minimizable   = true;
    config.maximizable   = true;
    config.canFullscreen = true;
    config.fullscreen    = false;

    //creation de notre fenetre apres passage des parametres necessaires a ce dernier notre premiere fenetre

    nkentseu::NkWindow fenetre(config);

    //Creation de la fenetre et gestion du cas echeant 

    if(!fenetre.IsOpen()){
        logger.Error("ECHEC DE CREATION DE LA FENTRE ");
        return -1;
    }
/*
    // Nouveau parametre pour notre 2eme Fenetre
    
    config.title = "2eme fenetre" ;
    config.fullscreen = true ;

    //creation de notre 2eme fenetre 

    nkentseu::NkWindow fenetre2(config);

    //Gestion du cas echeant 

    if(!fenetre.IsOpen()){
        logger.Error("ECHEC DE CREATION DE LA FENTRE ");
        return -1;
    }
    
    /// Nouveau parametre pour notre 3eme Fenetre
    
    config.title = "3eme fenetre" ;
    config.canFullscreen = false ;

    //creation de notre 3eme fenetre 

    nkentseu::NkWindow fenetre3(config);

    //Gestion du cas echeant 

    if(!fenetre.IsOpen()){
        logger.Error("ECHEC DE CREATION DE LA FENTRE ");
        return -1;
    }
    
    // Nouveau parametre pour notre 4eme Fenetre
    
    config.title = "4eme fenetre" ;
    config.maximizable = false ;

    //creation de notre 4eme fenetre 

    nkentseu::NkWindow fenetre4(config);

    //Gestion du cas echeant 

    if(!fenetre.IsOpen()){
        logger.Error("ECHEC DE CREATION DE LA FENTRE ");
        return -1;
    }
    // Nouveau parametre pour notre 5eme Fenetre

    config.title = "5eme fenetre" ;
    config.movable = false ;

    //creation de notre 5eme fenetre 

    nkentseu::NkWindow fenetre5(config);

    //Gestion du cas echeant 

    if(!fenetre.IsOpen()){
        logger.Error("ECHEC DE CREATION DE LA FENTRE ");
        return -1;
    }

    // Nouveau parametre pour notre 6eme Fenetre
    
    config.title = "6eme fenetre" ;
    config.centered = false ;

    //creation de notre 6eme fenetre 

    nkentseu::NkWindow fenetre6(config);

    //Gestion du cas echeant 

    

    if(!fenetre.IsOpen()){
        logger.Error("ECHEC DE CREATION DE LA FENTRE ");
        return -1;
    }

    // Nouveau parametre pour notre 7eme Fenetre
    
    config.title = "7eme fenetre" ;
    config.closable = false ;

    //creation de notre 7eme fenetre 

    nkentseu::NkWindow fenetre7(config);

    //Gestion du cas echeant 

    if(!fenetre.IsOpen()){
        logger.Error("ECHEC DE CREATION DE LA FENTRE ");
        return -1;
    }
*/
    // Booleen et Boucle
    bool IsRunning = true ;
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