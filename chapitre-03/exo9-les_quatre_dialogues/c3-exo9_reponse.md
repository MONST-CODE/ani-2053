# LES 04 DIALOGUES

## LES MOTS DU TERMINAL
```bash
jenga build        

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

Build Order (8 projects):
  1. LaFenetreNue [WINDOWED_APP] → 
  2. exo2 [WINDOWED_APP] → 
  3. LesBorneS [WINDOWED_APP] → 
  4. L'Asterice [WINDOWED_APP] → 
  5. 2fenetres [WINDOWED_APP] → 
  6. EXO4 [WINDOWED_APP] → 
  7. EXO9 [WINDOWED_APP] → 
  8. EXO10 [WINDOWED_APP]


╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║  Project: LaFenetreNue                                                   Kind: WINDOWED_APP  ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

ℹ Found 1 source file(s)
✓   [1/1] Compiled: c3-exo1_main.cpp
ℹ Linking...
✓ Built: Build\Bin\Debug-Windows\LaFenetreNue\LaFenetreNue.exe

┌──────────────────────────────────────────────────────────────────────────────────────────────┐
│  ✓ Build Successful                                                             Time: 2.54s  │
└──────────────────────────────────────────────────────────────────────────────────────────────┘

╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║  Project: exo2                                                           Kind: WINDOWED_APP  ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

ℹ Found 1 source file(s)
✓   [1/1] Compiled: c3-exo2_main.cpp
ℹ Linking...
✓ Built: Build\Bin\Debug-Windows\exo2\exo2.exe

┌──────────────────────────────────────────────────────────────────────────────────────────────┐
│  ✓ Build Successful                                                             Time: 2.64s  │
└──────────────────────────────────────────────────────────────────────────────────────────────┘

╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║  Project: LesBorneS                                                      Kind: WINDOWED_APP  ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

ℹ Found 1 source file(s)
✓   [1/1] Compiled: c3-exo3_main.cpp
ℹ Linking...
✓ Built: Build\Bin\Debug-Windows\LesBorneS\LesBorneS.exe

┌──────────────────────────────────────────────────────────────────────────────────────────────┐
│  ✓ Build Successful                                                             Time: 2.45s  │
└──────────────────────────────────────────────────────────────────────────────────────────────┘

╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║  Project: L'Asterice                                                     Kind: WINDOWED_APP  ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

ℹ Found 1 source file(s)
✓   [1/1] Compiled with warnings: c3-exo5_main.cpp
╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║                                  Warning: c3-exo5_main.cpp                                   ║
╠══════════════════════════════════════════════════════════════════════════════════════════════╣
║ C:\Users\CEO BRUNO                                                                           ║
║ ZAMBA\Desktop\ani-2053\chapitre-03\exo5-le_titre_qui_informe\c3-exo5_main.cpp:1:10: warning: ║
║ non-portable path to file '"NKWindow/NKWindow.h"'; specified path differs in case from file  ║
║ name on disk [-Wnonportable-include-path]                                                    ║
║     1 | #include "NkWindow/NKWindow.h"                                                       ║
║       |          ^~~~~~~~~~~~~~~~~~~~~                                                       ║
║       |          "NKWindow/NKWindow.h"                                                       ║
║ C:\Users\CEO BRUNO                                                                           ║
║ ZAMBA\Desktop\ani-2053\chapitre-03\exo5-le_titre_qui_informe\c3-exo5_main.cpp:2:10: warning: ║
║ non-portable path to file '"NKWindow/NKMain.h"'; specified path differs in case from file    ║
║ name on disk [-Wnonportable-include-path]                                                    ║
║     2 | #include "NkWindow/NKMain.h"                                                         ║
║       |          ^~~~~~~~~~~~~~~~~~~                                                         ║
║       |          "NKWindow/NKMain.h"                                                         ║
║ 2 warnings generated.                                                                        ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝
ℹ Linking...
✓ Built: Build\Bin\Debug-Windows\L'Asterice\L'Asterice.exe

┌──────────────────────────────────────────────────────────────────────────────────────────────┐
│  ✓ Build Successful                                                             Time: 2.28s  │
│ Warnings: 2                                                                                  │
└──────────────────────────────────────────────────────────────────────────────────────────────┘

╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║  Project: 2fenetres                                                      Kind: WINDOWED_APP  ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

ℹ Found 1 source file(s)
✓   [1/1] Compiled: c3-exo11_main.cpp
ℹ Linking...
✓ Built: Build\Bin\Debug-Windows\2fenetres\2fenetres.exe

┌──────────────────────────────────────────────────────────────────────────────────────────────┐
│  ✓ Build Successful                                                             Time: 2.42s  │
└──────────────────────────────────────────────────────────────────────────────────────────────┘

╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║  Project: EXO4                                                           Kind: WINDOWED_APP  ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

ℹ Found 1 source file(s)
✓   [1/1] Compiled: c3-exo4_main.cpp
ℹ Linking...
✓ Built: Build\Bin\Debug-Windows\EXO4\EXO4.exe

┌──────────────────────────────────────────────────────────────────────────────────────────────┐
│  ✓ Build Successful                                                             Time: 2.40s  │
└──────────────────────────────────────────────────────────────────────────────────────────────┘

╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║  Project: EXO9                                                           Kind: WINDOWED_APP  ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

ℹ Found 1 source file(s)
✓   [1/1] Compiled: c3-exo9_main.cpp
ℹ Linking...
✓ Built: Build\Bin\Debug-Windows\EXO9\EXO9.exe

┌──────────────────────────────────────────────────────────────────────────────────────────────┐
│  ✓ Build Successful                                                             Time: 2.40s  │
└──────────────────────────────────────────────────────────────────────────────────────────────┘

╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║  Project: EXO10                                                          Kind: WINDOWED_APP  ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

ℹ Found 1 source file(s)

╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║                             Compilation Error: c3-exo10_main.cpp                             ║
╠══════════════════════════════════════════════════════════════════════════════════════════════╣
║ C:\Users\CEO BRUNO                                                                           ║
║ ZAMBA\Desktop\ani-2053\chapitre-03\exo10-la_fenetre_sans_bordure\c3-exo10_main.cpp:13:5:     ║
║ error: no member named 'NkWindow' in 'nkentseu::NkWindowConfig'                              ║
║    11 |     config1.                                                                         ║
║       |     ~~~~~~~                                                                          ║
║    12 |                                                                                      ║
║    13 |     NkWindow fenetre(config1);                                                       ║
║       |     ^                                                                                ║
║ C:\Users\CEO BRUNO                                                                           ║
║ ZAMBA\Desktop\ani-2053\chapitre-03\exo10-la_fenetre_sans_bordure\c3-exo10_main.cpp:13:13:    ║
║ error: expected ';' after expression                                                         ║
║    13 |     NkWindow fenetre(config1);                                                       ║
║       |             ^                                                                        ║
║       |             ;                                                                        ║
║ C:\Users\CEO BRUNO                                                                           ║
║ ZAMBA\Desktop\ani-2053\chapitre-03\exo10-la_fenetre_sans_bordure\c3-exo10_main.cpp:13:14:    ║
║ error: use of undeclared identifier 'fenetre'                                                ║
║    13 |     NkWindow fenetre(config1);                                                       ║
║       |              ^~~~~~~                                                                 ║
║ C:\Users\CEO BRUNO                                                                           ║
║ ZAMBA\Desktop\ani-2053\chapitre-03\exo10-la_fenetre_sans_bordure\c3-exo10_main.cpp:15:12:    ║
║ error: use of undeclared identifier 'fenetre'                                                ║
║    15 |     while (fenetre.IsOpen())                                                         ║
║       |            ^~~~~~~                                                                   ║
║ 4 errors generated.                                                                          ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

✗ ✗ Compilation failed: C:\Users\............\Desktop\ani-2053\chapitre-03\exo10-la_fenetre_sans_bordure\c3-exo10_main.cpp

┌──────────────────────────────────────────────────────────────────────────────────────────────┐
│  ✗ Build Failed                                                                 Time: 1.89s  │
│ Errors: 4  | Failed files: 1                                                                 │
└──────────────────────────────────────────────────────────────────────────────────────────────┘

════════════════════════════════════════════════════════════════════════════════
                                  BUILD FAILED                                  
════════════════════════════════════════════════════════════════════════════════
Projects Built:  7/8
Failed:         1
Errors:         4
Warnings:       2
Time:           19.02s
Status:         ✗ FAILURE
════════════════════════════════════════════════════════════════════════════════

Echecs (1) — a corriger :
  ✗ EXO10

PS C:\Users\............\Desktop\ani-2053\chapitre-03> jenga run EXO9     

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
  ▶  EXECUTION  —  EXO9.exe
     C:\Users\............\Desktop\ani-2053\chapitre-03\Build\Bin\Debug-Windows\EXO9\EXO9.exe
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━


━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
  ◀  FIN D'EXECUTION  —  termine normalement  (13.93s)
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
```
## Interpretation 
Le build  ces bien passer sauf le dernier projet qui  a son soucis adansles logs ilne nous gene pas pour l'instant 
 
 Apres Execution ON A:
 * Une fenetres fonctionnel  qui s'ouvre 
 * Une Boites de Dialogue Qui s'ouvre quand on appuie sur (W ou Z)
 * possibiliter de sauvegarde avec la touche S quiouvre notre explorateurs nus permetant de choisir l'emplacement de sauvegarde 
  le code source est :
  ```cpp
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
```