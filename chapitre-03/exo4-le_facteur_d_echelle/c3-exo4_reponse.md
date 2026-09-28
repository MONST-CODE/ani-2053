# Facteur- D'Echelle
## LesmOTS DU TERMINAL 
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
│  ✓ Build Successful                                                             Time: 5.42s  │
└──────────────────────────────────────────────────────────────────────────────────────────────┘

╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║  Project: exo2                                                           Kind: WINDOWED_APP  ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

ℹ Found 1 source file(s)
✓   [1/1] Compiled: c3-exo2_main.cpp
ℹ Linking...
✓ Built: Build\Bin\Debug-Windows\exo2\exo2.exe

┌──────────────────────────────────────────────────────────────────────────────────────────────┐
│  ✓ Build Successful                                                             Time: 2.58s  │
└──────────────────────────────────────────────────────────────────────────────────────────────┘

╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║  Project: LesBorneS                                                      Kind: WINDOWED_APP  ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

ℹ Found 1 source file(s)
✓   [1/1] Compiled: c3-exo3_main.cpp
ℹ Linking...
✓ Built: Build\Bin\Debug-Windows\LesBorneS\LesBorneS.exe

┌──────────────────────────────────────────────────────────────────────────────────────────────┐
│  ✓ Build Successful                                                             Time: 2.67s  │
└──────────────────────────────────────────────────────────────────────────────────────────────┘

╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║  Project: L'Asterice                                                     Kind: WINDOWED_APP  ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

ℹ Found 1 source file(s)
✓   [1/1] Compiled with warnings: c3-exo5_main.cpp
╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║                                  Warning: c3-exo5_main.cpp                                   ║
╠══════════════════════════════════════════════════════════════════════════════════════════════╣
║ C:\....\CEO BRUNO                                                                           ║
║ ZAMBA\Desktop\ani-2053\chapitre-03\exo5-le_titre_qui_informe\c3-exo5_main.cpp:1:10: warning: ║
║ non-portable path to file '"NKWindow/NKWindow.h"'; specified path differs in case from file  ║
║ name on disk [-Wnonportable-include-path]                                                    ║
║     1 | #include "NkWindow/NKWindow.h"                                                       ║
║       |          ^~~~~~~~~~~~~~~~~~~~~                                                       ║
║       |          "NKWindow/NKWindow.h"                                                       ║
║ C:\....\CEO BRUNO                                                                           ║
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
│  ✓ Build Successful                                                             Time: 2.67s  │
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
│  ✓ Build Successful                                                             Time: 2.68s  │
└──────────────────────────────────────────────────────────────────────────────────────────────┘

╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║  Project: EXO4                                                           Kind: WINDOWED_APP  ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

ℹ Found 1 source file(s)
✓   [1/1] Compiled: c3-exo4_main.cpp
ℹ Linking...
✓ Built: Build\Bin\Debug-Windows\EXO4\EXO4.exe

┌──────────────────────────────────────────────────────────────────────────────────────────────┐
│  ✓ Build Successful                                                             Time: 2.66s  │
└──────────────────────────────────────────────────────────────────────────────────────────────┘

╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║  Project: EXO9                                                           Kind: WINDOWED_APP  ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

ℹ Found 1 source file(s)
✓   [1/1] Compiled: c3-exo9_main.cpp
ℹ Linking...
✓ Built: Build\Bin\Debug-Windows\EXO9\EXO9.exe

┌──────────────────────────────────────────────────────────────────────────────────────────────┐
│  ✓ Build Successful                                                             Time: 2.44s  │
└──────────────────────────────────────────────────────────────────────────────────────────────┘

╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║  Project: EXO10                                                          Kind: WINDOWED_APP  ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

ℹ Found 1 source file(s)

╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║                             Compilation Error: c3-exo10_main.cpp                             ║
╠══════════════════════════════════════════════════════════════════════════════════════════════╣
║ C:\....\CEO BRUNO                                                                           ║
║ ZAMBA\Desktop\ani-2053\chapitre-03\exo10-la_fenetre_sans_bordure\c3-exo10_main.cpp:13:5:     ║
║ error: no member named 'NkWindow' in 'nkentseu::NkWindowConfig'                              ║
║    11 |     config1.                                                                         ║
║       |     ~~~~~~~                                                                          ║
║    12 |                                                                                      ║
║    13 |     NkWindow fenetre(config1);                                                       ║
║       |     ^                                                                                ║
║ C:\....\CEO BRUNO                                                                           ║
║ ZAMBA\Desktop\ani-2053\chapitre-03\exo10-la_fenetre_sans_bordure\c3-exo10_main.cpp:13:13:    ║
║ error: expected ';' after expression                                                         ║
║    13 |     NkWindow fenetre(config1);                                                       ║
║       |             ^                                                                        ║
║       |             ;                                                                        ║
║ C:\....\CEO BRUNO                                                                           ║
║ ZAMBA\Desktop\ani-2053\chapitre-03\exo10-la_fenetre_sans_bordure\c3-exo10_main.cpp:13:14:    ║
║ error: use of undeclared identifier 'fenetre'                                                ║
║    13 |     NkWindow fenetre(config1);                                                       ║
║       |              ^~~~~~~                                                                 ║
║ C:\....\CEO BRUNO                                                                           ║
║ ZAMBA\Desktop\ani-2053\chapitre-03\exo10-la_fenetre_sans_bordure\c3-exo10_main.cpp:15:12:    ║
║ error: use of undeclared identifier 'fenetre'                                                ║
║    15 |     while (fenetre.IsOpen())                                                         ║
║       |            ^~~~~~~                                                                   ║
║ 4 errors generated.                                                                          ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

✗ ✗ Compilation failed: C:\....\....\Desktop\ani-2053\chapitre-03\exo10-la_fenetre_sans_bordure\c3-exo10_main.cpp

┌──────────────────────────────────────────────────────────────────────────────────────────────┐
│  ✗ Build Failed                                                                 Time: 2.01s  │
│ Errors: 4  | Failed files: 1                                                                 │
└──────────────────────────────────────────────────────────────────────────────────────────────┘

════════════════════════════════════════════════════════════════════════════════
                                  BUILD FAILED                                  
════════════════════════════════════════════════════════════════════════════════
Projects Built:  7/8
Failed:         1
Errors:         4
Warnings:       2
Time:           23.13s
Status:         ✗ FAILURE
════════════════════════════════════════════════════════════════════════════════

Echecs (1) — a corriger :
  ✗ EXO10

PS C:\....\....\Desktop\ani-2053\chapitre-03> jenga run EXO4     

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
  ▶  EXECUTION  —  EXO4.exe
     C:\....\....\Desktop\ani-2053\chapitre-03\Build\Bin\Debug-Windows\EXO4\EXO4.exe
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

la taille de la fenetre est [600,800]la Taille de l'ecran est [1920 , 1080]
le Scale est [800 , 600]
la taille de la fenetre est [1009,1920]la Taille de l'ecran est [1920 , 1080]
le Scale est [1920 , 1009]
la taille de la fenetre est [600,800]la Taille de l'ecran est [1920 , 1080]
le Scale est [800 , 600]
la taille de la fenetre est [507,669]la Taille de l'ecran est [1920 , 1080]
le Scale est [669 , 507]
la taille de la fenetre est [507,669]la Taille de l'ecran est [1920 , 1080]
le Scale est [669 , 507]
la taille de la fenetre est [507,669]la Taille de l'ecran est [1920 , 1080]
le Scale est [669 , 507]

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
  ◀  FIN D'EXECUTION  —  termine normalement  (371.08s)
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
PS C:\....\....\Desktop\ani-2053\chapitre-03> 
```
## Interpretation et rendue 
cette fois ci la console es propre soyex en sur elle n'es pas fabriquer elle a ete copier telquel 
*La fenetre s'ouvre
* Getsize , GetDisplay(), etcc...fonctionne donc car on des infos palpables a la sortie 
* la fenetre se ferme correctement .