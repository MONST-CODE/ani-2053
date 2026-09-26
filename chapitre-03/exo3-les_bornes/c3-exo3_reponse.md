# LES BORNES
## Cas sans configurtions des minimales 
### 1-1-Etatdu code
```cpp
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
```
## 1-2-Console pour la configurtion(les repetitions on ete supprimer car iletait trop nombreux car present dans la boucle)
```bash
PS C:\.....\.....\Desktop\ani-2053\chapitre-03> jenga build 

╔══════════════════════════════════════════════════════════════════╗
║                                                                  ║
║                ██╗███████╗███╗   ██╗ ██████╗  █████╗             ║
║                ██║██╔════╝████╗  ██║██╔════╝ ██╔══██╗            ║
║                ██║█████╗  ██╔██╗ ██║██║  ███╗███████║            ║
║           ██   ██║██╔══╝  ██║╚██╗██║██║   ██║██╔══██║            ║
║           ╚█████╔╝███████╗██║ ╚████║╚██████╔╝██║  ██║            ║
║            ╚════╝ ╚══════╝╚═╝  ╚═══╝ ╚═════╝ ╚═╝  ╚═╝            ║
║                                                                  ║
║             Multi-platform C/C++ Build System v2.8.0             ║
║                                                                  ║
╚══════════════════════════════════════════════════════════════════╝

Loading workspace...

Configuration: Debug
Target:        Windows x86_64
Toolchain:     clang-mingw

Build Order (3 projects):
  1. LaFenetreNue [WINDOWED_APP] → 
  2. exo2 [WINDOWED_APP] → 
  3. LesBorneS [WINDOWED_APP]


╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║  Project: LaFenetreNue                                                   Kind: WINDOWED_APP  ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

ℹ Found 1 source file(s)
✓   [1/1] Compiled: c3-exo1_main.cpp
ℹ Linking...
✓ Built: Build\Bin\Debug-Windows\LaFenetreNue\LaFenetreNue.exe

┌──────────────────────────────────────────────────────────────────────────────────────────────┐
│  ✓ Build Successful                                                             Time: 2.42s  │
└──────────────────────────────────────────────────────────────────────────────────────────────┘

╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║  Project: exo2                                                           Kind: WINDOWED_APP  ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

ℹ Found 1 source file(s)
✓   [1/1] Compiled: c3-exo2_main.cpp
ℹ Linking...
✓ Built: Build\Bin\Debug-Windows\exo2\exo2.exe

┌──────────────────────────────────────────────────────────────────────────────────────────────┐
│  ✓ Build Successful                                                             Time: 2.30s  │
└──────────────────────────────────────────────────────────────────────────────────────────────┘

╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║  Project: LesBorneS                                                      Kind: WINDOWED_APP  ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

ℹ Found 1 source file(s)
✓   [1/1] Compiled: c3-exo3_main.cpp
ℹ Linking...
✓ Built: Build\Bin\Debug-Windows\LesBorneS\LesBorneS.exe

┌──────────────────────────────────────────────────────────────────────────────────────────────┐
│  ✓ Build Successful                                                             Time: 2.16s  │
└──────────────────────────────────────────────────────────────────────────────────────────────┘

════════════════════════════════════════════════════════════════════════════════
                                BUILD COMPLETED                                 
════════════════════════════════════════════════════════════════════════════════
Projects Built:  3/3
Time:           6.89s
Status:         ✓ SUCCESS
════════════════════════════════════════════════════════════════════════════════

PS C:\.....\.....\Desktop\ani-2053\chapitre-03> jenga run exo3                       

╔══════════════════════════════════════════════════════════════════╗
║                                                                  ║
║                ██╗███████╗███╗   ██╗ ██████╗  █████╗             ║
║                ██║██╔════╝████╗  ██║██╔════╝ ██╔══██╗            ║
║                ██║█████╗  ██╔██╗ ██║██║  ███╗███████║            ║
║           ██   ██║██╔══╝  ██║╚██╗██║██║   ██║██╔══██║            ║
║           ╚█████╔╝███████╗██║ ╚████║╚██████╔╝██║  ██║            ║
║            ╚════╝ ╚══════╝╚═╝  ╚═══╝ ╚═════╝ ╚═╝  ╚═╝            ║
║                                                                  ║
║             Multi-platform C/C++ Build System v2.8.0             ║
║                                                                  ║
╚══════════════════════════════════════════════════════════════════╝

Project 'exo3' not found.
PS C:\.....\.....\Desktop\ani-2053\chapitre-03> jenga run LesBorneS

╔══════════════════════════════════════════════════════════════════╗
║                                                                  ║
║                ██╗███████╗███╗   ██╗ ██████╗  █████╗             ║
║                ██║██╔════╝████╗  ██║██╔════╝ ██╔══██╗            ║
║                ██║█████╗  ██╔██╗ ██║██║  ███╗███████║            ║
║           ██   ██║██╔══╝  ██║╚██╗██║██║   ██║██╔══██║            ║
║           ╚█████╔╝███████╗██║ ╚████║╚██████╔╝██║  ██║            ║
║            ╚════╝ ╚══════╝╚═╝  ╚═══╝ ╚═════╝ ╚═╝  ╚═╝            ║
║                                                                  ║
║             Multi-platform C/C++ Build System v2.8.0             ║
║                                                                  ║
╚══════════════════════════════════════════════════════════════════╝


━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
  ▶  EXECUTION  —  LesBorneS.exe
     C:\.....\.....\Desktop\ani-2053\chapitre-03\Build\Bin\Debug-Windows\LesBorneS\LesBorneS.exe
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

LA LONGEUR APRES INITIALISATION EST 800 de Large et 600 de Haut
La Largeur actuel de la fenetre 800La Hauteur 600
La Largeur actuel de la fenetre 434La Hauteur 261
La Largeur actuel de la fenetre 434La Hauteur 261
La Largeur actuel de la fenetre 384La Hauteur 261
La Largeur actuel de la fenetre 384La Hauteur 261
La Largeur actuel de la fenetre 384La Hauteur 261
La Largeur actuel de la fenetre 384La Hauteur 261
La Largeur actuel de la fenetre 384La Hauteur 261
La Largeur actuel de la fenetre 384La Hauteur 261
La Largeur actuel de la fenetre 384La Hauteur 261

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
  ◀  FIN D'EXECUTION  —  termine avec le code 1  (148.47s)
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
```
## 1-3-CONCLUSION
d'apres les log on peut direqued'une maniere ou du autre la taille minimales es respecter
- width = 384~400
- heigth = 261~300
## Cas sans configurtions des minimales 
### 1-1-Etatdu code
```cpp
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
```
## 1-2-Console pour la configurtion(les repetitions on ete supprimer car iletait trop nombreux car present dans la boucle)
```bash
PS C:\.....\.....\Desktop\ani-2053\chapitre-03>jenga build        

╔══════════════════════════════════════════════════════════════════╗
║                                                                  ║
║                ██╗███████╗███╗   ██╗ ██████╗  █████╗             ║
║                ██║██╔════╝████╗  ██║██╔════╝ ██╔══██╗            ║
║                ██║█████╗  ██╔██╗ ██║██║  ███╗███████║            ║
║           ██   ██║██╔══╝  ██║╚██╗██║██║   ██║██╔══██║            ║
║           ╚█████╔╝███████╗██║ ╚████║╚██████╔╝██║  ██║            ║
║            ╚════╝ ╚══════╝╚═╝  ╚═══╝ ╚═════╝ ╚═╝  ╚═╝            ║
║                                                                  ║
║             Multi-platform C/C++ Build System v2.8.0             ║
║                                                                  ║
╚══════════════════════════════════════════════════════════════════╝

Loading workspace...

Configuration: Debug
Target:        Windows x86_64
Toolchain:     clang-mingw

Build Order (3 projects):
  1. LaFenetreNue [WINDOWED_APP] → 
  2. exo2 [WINDOWED_APP] → 
  3. LesBorneS [WINDOWED_APP]


╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║  Project: LaFenetreNue                                                   Kind: WINDOWED_APP  ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

ℹ Found 1 source file(s)
✓   [1/1] Compiled: c3-exo1_main.cpp
ℹ Linking...
✓ Built: Build\Bin\Debug-Windows\LaFenetreNue\LaFenetreNue.exe

┌──────────────────────────────────────────────────────────────────────────────────────────────┐
│  ✓ Build Successful                                                             Time: 2.50s  │
└──────────────────────────────────────────────────────────────────────────────────────────────┘

╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║  Project: exo2                                                           Kind: WINDOWED_APP  ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

ℹ Found 1 source file(s)
✓   [1/1] Compiled: c3-exo2_main.cpp
ℹ Linking...
✓ Built: Build\Bin\Debug-Windows\exo2\exo2.exe

┌──────────────────────────────────────────────────────────────────────────────────────────────┐
│  ✓ Build Successful                                                             Time: 2.37s  │
└──────────────────────────────────────────────────────────────────────────────────────────────┘

╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║  Project: LesBorneS                                                      Kind: WINDOWED_APP  ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

ℹ Found 1 source file(s)
✓   [1/1] Compiled: c3-exo3_main.cpp
ℹ Linking...
✓ Built: Build\Bin\Debug-Windows\LesBorneS\LesBorneS.exe

┌──────────────────────────────────────────────────────────────────────────────────────────────┐
│  ✓ Build Successful                                                             Time: 2.23s  │
└──────────────────────────────────────────────────────────────────────────────────────────────┘

════════════════════════════════════════════════════════════════════════════════
                                BUILD COMPLETED                                 
════════════════════════════════════════════════════════════════════════════════
Projects Built:  3/3
Time:           7.10s
Status:         ✓ SUCCESS
════════════════════════════════════════════════════════════════════════════════

PS C:\.....\.....\Desktop\ani-2053\chapitre-03> jenga run LesBorneS

╔══════════════════════════════════════════════════════════════════╗
║                                                                  ║
║                ██╗███████╗███╗   ██╗ ██████╗  █████╗             ║
║                ██║██╔════╝████╗  ██║██╔════╝ ██╔══██╗            ║
║                ██║█████╗  ██╔██╗ ██║██║  ███╗███████║            ║
║           ██   ██║██╔══╝  ██║╚██╗██║██║   ██║██╔══██║            ║
║           ╚█████╔╝███████╗██║ ╚████║╚██████╔╝██║  ██║            ║
║            ╚════╝ ╚══════╝╚═╝  ╚═══╝ ╚═════╝ ╚═╝  ╚═╝            ║
║                                                                  ║
║             Multi-platform C/C++ Build System v2.8.0             ║
║                                                                  ║
╚══════════════════════════════════════════════════════════════════╝


━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
  ▶  EXECUTION  —  LesBorneS.exe
     C:\.....\.....\Desktop\ani-2053\chapitre-03\Build\Bin\Debug-Windows\LesBorneS\LesBorneS.exe
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

LA LONGEUR APRES INITIALISATION EST 800 de Large et 600 de Haut
La Largeur actuel de la fenetre 800La Hauteur 600
La Largeur actuel de la fenetre 144La Hauteur 51
La Largeur actuel de la fenetre 144La Hauteur 51
La Largeur actuel de la fenetre 144La Hauteur 51
La Largeur actuel de la fenetre 144La Hauteur 51
La Largeur actuel de la fenetre 144La Hauteur 51
La Largeur actuel de la fenetre 144La Hauteur 51
La Largeur actuel de la fenetre 144La Hauteur 51
La Largeur actuel de la fenetre 144La Hauteur 51
La Largeur actuel de la fenetre 144La Hauteur 51
La Largeur actuel de la fenetre 144La Hauteur 51
La Largeur actuel de la fenetre 144La Hauteur 51
La Largeur actuel de la fenetre 144La Hauteur 51

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
  ◀  FIN D'EXECUTION  —  termine avec le code 1  (52.14s)
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
PS C:\.....\.....\Desktop\ani-2053\chapitre-03> 
```
* La Taille MINIMALE Predefinis par le systeme est 
- width = 144~150 ou 160 
- heigth = 51~60