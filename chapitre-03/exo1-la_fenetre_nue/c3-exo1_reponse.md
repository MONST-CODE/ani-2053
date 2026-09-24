# I-TOUTES LES ERREURS
## 1-ERREUR DU A L"ENVIRONNEMENT ET AU FICHIER DE CONFIGURATIONS .jenga
* **Lancement Sans Builder je ne m'appercois pas de cela sur le champ car mes fichier jenga ont des Erreurs**
```cpp
PS C:\...\...\Desktop\ani-2053> cd .\chapitre-03\
PS C:\...\...\Desktop\ani-2053\chapitre-03> cd .\exo1-la_fenetre_nue\

PS C:\...\....\Desktop\ani-2053\chapitre-03\exo1-la_fenetre_nue> jenga run

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

Error loading workspace: expected ':' (chapitre-03.jenga, line 11)
Failed to load workspace.
PS C:\....\...\Desktop\ani-2053\chapitre-03\exo1-la_fenetre_nue> jenga run

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

Error loading workspace: useconfig: fichier de config introuvable: C:\Users\CEO BRUNO ZAMBA\Desktop\ani-2053\chapitre-03\exo1-la_fenetre_nue\NkentseuKit\NkentseuKit.jenga
Failed to load workspace.
```
* J'ai ecrit 'configuration' au lieu de 'configurations'
```cpp
PS C:\Users\CEO BRUNO ZAMBA\Desktop\ani-2053\chapitre-03\exo1-la_fenetre_nue> jenga run

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

Error loading workspace: name 'configuration' is not defined
Failed to load workspace.
```
* 'TargetOs' correction 'TargetOS'
```cpp
PS C:\Users\CEO BRUNO ZAMBA\Desktop\ani-2053\chapitre-03\exo1-la_fenetre_nue> jenga run

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
Error loading workspace: name 'TargetOs' is not defined
Failed to load workspace.
```
* Ici 'TargetArch' es bien ecrit le souci vient du 'x86' la correction est 'X86' mais jai d'abord mis ARCH en majuscule ce qui creea l'erreur suivante 
```cpp
PS C:\Users\CEO BRUNO ZAMBA\Desktop\ani-2053\chapitre-03\exo1-la_fenetre_nue> jenga run

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

Error loading workspace: type object 'TargetArch' has no attribute 'x86_64'
Failed to load workspace.
PS C:\Users\CEO BRUNO ZAMBA\Desktop\ani-2053\chapitre-03\exo1-la_fenetre_nue> jenga run

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

Error loading workspace: name 'TargetARCH' is not defined
Failed to load workspace.
```
* Ici 'windoweapp'es mal ecrit correction 'windowedapp'
```cpp
PS C:\Users\CEO BRUNO ZAMBA\Desktop\ani-2053\chapitre-03\exo1-la_fenetre_nue> jenga run

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

Error loading workspace: name 'windoweapp' is not defined
Failed to load workspace.
```
* Enfin nous nous rendons compte que depuis nous lancons sans builder au prealable
```cpp
PS C:\..\...\Desktop\ani-2053\chapitre-03\exo1-la_fenetre_nue> jenga run

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


Executable not found: C:\Users\CEO BRUNO ZAMBA\Desktop\ani-2053\chapitre-03\Build\Bin\Debug-Windows\LaFenetreNue\LaFenetreNue.exe
```
## 2-ERREUR DU A NOTRE REEL CODE
*  Serie D'erreur courant 
      -gestion du dossier kit
      -Liaison des fichier jenga via useconfig() il es question pour nous de lier notre dossier kit afin que les fonction telque 'NkWindow.h' soit directement lier (le but es de faire un peu comme la SDL3 "la detection es presque souvent automatique hors les fichier ne sont pas notre dossier de code)

```cpp
PS C:\...\...\Desktop\ani-2053\chapitre-03\exo1-la_fenetre_nue> jenga build

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

Build Order (1 projects):
  1. LaFenetreNue [WINDOWED_APP]


╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║  Project: LaFenetreNue                                                   Kind: WINDOWED_APP  ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

ℹ Found 1 source file(s)

╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║                             Compilation Error: c3-exo1_main.cpp                              ║
╠══════════════════════════════════════════════════════════════════════════════════════════════╣
║ C:\Users\CEO BRUNO                                                                           ║
║ ZAMBA\Desktop\ani-2053\chapitre-03\exo1-la_fenetre_nue\c3-exo1_main.cpp:1:10: fatal error:   ║
║ 'NKWindow/NKWindow.h' file not found                                                         ║
║     1 | #include "NKWindow/NKWindow.h"                                                       ║
║       |          ^~~~~~~~~~~~~~~~~~~~~                                                       ║
║ 1 error generated.                                                                           ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

✗ ✗ Compilation failed: C:\...\... ZAMBA\Desktop\ani-2053\chapitre-03\exo1-la_fenetre_nue\c3-exo1_main.cpp

┌──────────────────────────────────────────────────────────────────────────────────────────────┐
│  ✗ Build Failed                                                                 Time: 0.08s  │
│ Errors: 2  | Failed files: 1                                                                 │
└──────────────────────────────────────────────────────────────────────────────────────────────┘

════════════════════════════════════════════════════════════════════════════════
                                  BUILD FAILED                                  
════════════════════════════════════════════════════════════════════════════════
Projects Built:  0/1
Failed:         1
Errors:         2
Time:           0.08s
Status:         ✗ FAILURE
════════════════════════════════════════════════════════════════════════════════

Echecs (1) — a corriger :
  ✗ LaFenetreNue

PS C:\Users\CEO BRUNO ZAMBA\Desktop\ani-2053\chapitre-03\exo1-la_fenetre_nue> jenga build

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
Error loading workspace: name 'useNkentseuKit' is not defined
Failed to load workspace.
PS C:\Users\CEO BRUNO ZAMBA\Desktop\ani-2053\chapitre-03\exo1-la_fenetre_nue> jenga build

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
Error loading workspace: (unicode error) 'unicodeescape' codec can't decode bytes in position 20-21: malformed \N character escape (chapitre-03.jenga, line 11)
Failed to load workspace.'
PS C:\Users\CEO BRUNO ZAMBA\Desktop\ani-2053\chapitre-03\exo1-la_fenetre_nue> jenga build        

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

Build Order (1 projects):
  1. LaFenetreNue [WINDOWED_APP]


╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║  Project: LaFenetreNue                                                   Kind: WINDOWED_APP  ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

ℹ Found 1 source file(s)

╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║                             Compilation Error: c3-exo1_main.cpp                              ║
╠══════════════════════════════════════════════════════════════════════════════════════════════╣
║ C:\Users\CEO BRUNO                                                                           ║
║ ZAMBA\Desktop\ani-2053\chapitre-03\exo1-la_fenetre_nue\c3-exo1_main.cpp:3:25: error:         ║
║ expected ';' after namespace name                                                            ║
║     3 | using namespace Nkentseu                                                             ║
║       |                         ^                                                            ║
║       |                         ;                                                            ║
║ C:\Users\CEO BRUNO                                                                           ║
║ ZAMBA\Desktop\ani-2053\chapitre-03\exo1-la_fenetre_nue\c3-exo1_main.cpp:3:17: error: no      ║
║ namespace named 'Nkentseu'; did you mean 'nkentseu'?                                         ║
║     3 | using namespace Nkentseu                                                             ║
║       |                 ^~~~~~~~                                                             ║
║       |                 nkentseu                                                             ║
║ C:\Users\CEO BRUNO                                                                           ║
║ ZAMBA\Desktop\ani-2053\chapitre-03\BRUNO\include/NKWindow/EntryPoints/NkWindowsDesktop.h:25: ║
║ 11: note: namespace 'nkentseu' defined here                                                  ║
║    25 | namespace nkentseu {                                                                 ║
║       |           ^                                                                          ║
║ 2 errors generated.                                                                          ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

✗ ✗ Compilation failed: C:\Users\CEO BRUNO ZAMBA\Desktop\ani-2053\chapitre-03\exo1-la_fenetre_nue\c3-exo1_main.cpp

┌──────────────────────────────────────────────────────────────────────────────────────────────┐
│  ✗ Build Failed                                                                 Time: 4.76s  │
│ Errors: 2  | Failed files: 1                                                                 │
└──────────────────────────────────────────────────────────────────────────────────────────────┘

════════════════════════════════════════════════════════════════════════════════
                                  BUILD FAILED                                  
════════════════════════════════════════════════════════════════════════════════
Projects Built:  0/1
Failed:         1
Errors:         2
Time:           4.76s
Status:         ✗ FAILURE
════════════════════════════════════════════════════════════════════════════════

Echecs (1) — a corriger :
  ✗ LaFenetreNue

PS C:\Users\CEO BRUNO ZAMBA\Desktop\ani-2053\chapitre-03\exo1-la_fenetre_nue> jenga build

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

Build Order (1 projects):
  1. LaFenetreNue [WINDOWED_APP]


╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║  Project: LaFenetreNue                                                   Kind: WINDOWED_APP  ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

ℹ Found 1 source file(s)

╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║                             Compilation Error: c3-exo1_main.cpp                              ║
╠══════════════════════════════════════════════════════════════════════════════════════════════╣
║ C:\Users\CEO BRUNO                                                                           ║
║ ZAMBA\Desktop\ani-2053\chapitre-03\exo1-la_fenetre_nue\c3-exo1_main.cpp:3:25: error:         ║
║ expected ';' after namespace name                                                            ║
║     3 | using namespace nkentseu                                                             ║
║       |                         ^                                                            ║
║       |                         ;                                                            ║
║ 1 error generated.                                                                           ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

✗ ✗ Compilation failed: C:\Users\CEO BRUNO ZAMBA\Desktop\ani-2053\chapitre-03\exo1-la_fenetre_nue\c3-exo1_main.cpp

┌──────────────────────────────────────────────────────────────────────────────────────────────┐
│  ✗ Build Failed                                                                 Time: 2.48s  │
│ Errors: 2  | Failed files: 1                                                                 │
└──────────────────────────────────────────────────────────────────────────────────────────────┘

════════════════════════════════════════════════════════════════════════════════
                                  BUILD FAILED                                  
════════════════════════════════════════════════════════════════════════════════
Projects Built:  0/1
Failed:         1
Errors:         2
Time:           2.48s
Status:         ✗ FAILURE
════════════════════════════════════════════════════════════════════════════════

Echecs (1) — a corriger :
  ✗ LaFenetreNue

PS C:\Users\CEO BRUNO ZAMBA\Desktop\ani-2053\chapitre-03\exo1-la_fenetre_nue> jenga build

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

Build Order (1 projects):
  1. LaFenetreNue [WINDOWED_APP]


╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║  Project: LaFenetreNue                                                   Kind: WINDOWED_APP  ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

ℹ Found 1 source file(s)

╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║                             Compilation Error: c3-exo1_main.cpp                              ║
╠══════════════════════════════════════════════════════════════════════════════════════════════╣
║ C:\Users\CEO BRUNO                                                                           ║
║ ZAMBA\Desktop\ani-2053\chapitre-03\exo1-la_fenetre_nue\c3-exo1_main.cpp:14:65: error:        ║
║ expected ';' after expression                                                                ║
║    14 |         logger.Error("[app] Echec de la Creation de la fenetre")                     ║
║       |                                                                 ^                    ║
║       |                                                                 ;                    ║
║ C:\Users\CEO BRUNO                                                                           ║
║ ZAMBA\Desktop\ani-2053\chapitre-03\exo1-la_fenetre_nue\c3-exo1_main.cpp:17:19: error: no     ║
║ member named 'Isopen' in 'nkentseu::NkWindow'                                                ║
║    17 |     while (window.Isopen()){                                                         ║
║       |            ~~~~~~ ^                                                                  ║
║ 2 errors generated.                                                                          ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

✗ ✗ Compilation failed: C:\Users\CEO BRUNO ZAMBA\Desktop\ani-2053\chapitre-03\exo1-la_fenetre_nue\c3-exo1_main.cpp

┌──────────────────────────────────────────────────────────────────────────────────────────────┐
│  ✗ Build Failed                                                                 Time: 2.49s  │
│ Errors: 3  | Failed files: 1                                                                 │
└──────────────────────────────────────────────────────────────────────────────────────────────┘

════════════════════════════════════════════════════════════════════════════════
                                  BUILD FAILED                                  
════════════════════════════════════════════════════════════════════════════════
Projects Built:  0/1
Failed:         1
Errors:         3
Time:           2.50s
Status:         ✗ FAILURE
════════════════════════════════════════════════════════════════════════════════

Echecs (1) — a corriger :
  ✗ LaFenetreNue

PS C:\Users\CEO BRUNO ZAMBA\Desktop\ani-2053\chapitre-03\exo1-la_fenetre_nue> jenga build

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

Build Order (1 projects):
  1. LaFenetreNue [WINDOWED_APP]


╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║  Project: LaFenetreNue                                                   Kind: WINDOWED_APP  ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

ℹ Found 1 source file(s)
✓   [1/1] Compiled: c3-exo1_main.cpp
ℹ Linking...
✓ Built: Build\Bin\Debug-Windows\LaFenetreNue\LaFenetreNue.exe

┌──────────────────────────────────────────────────────────────────────────────────────────────┐
│  ✓ Build Successful                                                             Time: 3.57s  │
└──────────────────────────────────────────────────────────────────────────────────────────────┘

════════════════════════════════════════════════════════════════════════════════
                                BUILD COMPLETED                                 
════════════════════════════════════════════════════════════════════════════════
Projects Built:  1/1
Time:           3.58s
Status:         ✓ SUCCESS
════════════════════════════════════════════════════════════════════════════════

PS C:\Users\CEO BRUNO ZAMBA\Desktop\ani-2053\chapitre-03\exo1-la_fenetre_nue> jenga run

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
  ▶  EXECUTION  —  LaFenetreNue.exe
     C:\Users\CEO BRUNO ZAMBA\Desktop\ani-2053\chapitre-03\Build\Bin\Debug-Windows\LaFenetreNue\LaFenetreNue.exe
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━


━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
  ◀  FIN D'EXECUTION'  —  termine avec le code 3489660927  (71.36s)
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
PS C:\Users\CEO BRUNO ZAMBA\Desktop\ani-2053\chapitre-03\exo1-la_fenetre_nue> jenga build

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

Build Order (1 projects):
  1. LaFenetreNue [WINDOWED_APP]


╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║  Project: LaFenetreNue                                                   Kind: WINDOWED_APP  ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

ℹ Found 1 source file(s)

╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║                             Compilation Error: c3-exo1_main.cpp                              ║
╠══════════════════════════════════════════════════════════════════════════════════════════════╣
║ C:\Users\... ...                                                                           ║
║ ..\Desktop\ani-2053\chapitre-03\exo1-la_fenetre_nue\c3-exo1_main.cpp:20:46: error: no     ║
║ member named 'pollEvent' in 'nkentseu::NkEventSystem'                                        ║
║    20 |         while ((event = nkentseu::NkEvents().pollEvent() != nullptr))                ║
║       |                         ~~~~~~~~~~~~~~~~~~~~ ^                                       ║
║ 1 error generated.                                                                           ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

✗ ✗ Compilation failed: C:\...\....\Desktop\ani-2053\chapitre-03\exo1-la_fenetre_nue\c3-exo1_main.cpp

┌──────────────────────────────────────────────────────────────────────────────────────────────┐
│  ✗ Build Failed                                                                 Time: 2.54s  │
│ Errors: 2  | Failed files: 1                                                                 │
└──────────────────────────────────────────────────────────────────────────────────────────────┘

════════════════════════════════════════════════════════════════════════════════
                                  BUILD FAILED                                  
════════════════════════════════════════════════════════════════════════════════
Projects Built:  0/1
Failed:         1
Errors:         2
Time:           2.54s
Status:         ✗ FAILURE
════════════════════════════════════════════════════════════════════════════════

Echecs (1) — a corriger :
  ✗ LaFenetreNue

PS C:\....\....\Desktop\ani-2053\chapitre-03\exo1-la_fenetre_nue> jenga build

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

Build Order (1 projects):
  1. LaFenetreNue [WINDOWED_APP]


╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║  Project: LaFenetreNue                                                   Kind: WINDOWED_APP  ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

ℹ Found 1 source file(s)

╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║                             Compilation Error: c3-exo1_main.cpp                              ║
╠══════════════════════════════════════════════════════════════════════════════════════════════╣
║ C:\...\.... ...                                                                           ║
║...\Desktop\ani-2053\chapitre-03\exo1-la_fenetre_nue\c3-exo1_main.cpp:20:58: error:        ║
║ incompatible integer to pointer conversion assigning to 'nkentseu::NkEvent *' from 'bool'    ║
║    20 |         while ((event = nkentseu::NkEvents().PollEvent() != nullptr))                ║
║       |                         ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^~~~~~~~~~                  ║
║ 1 error generated.                                                                           ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

✗ ✗ Compilation failed: C:\...\....\Desktop\ani-2053\chapitre-03\exo1-la_fenetre_nue\c3-exo1_main.cpp

┌──────────────────────────────────────────────────────────────────────────────────────────────┐
│  ✗ Build Failed                                                                 Time: 2.51s  │
│ Errors: 2  | Failed files: 1                                                                 │
└──────────────────────────────────────────────────────────────────────────────────────────────┘

════════════════════════════════════════════════════════════════════════════════
                                  BUILD FAILED                                  
════════════════════════════════════════════════════════════════════════════════
Projects Built:  0/1
Failed:         1
Errors:         2
Time:           2.52s
Status:         ✗ FAILURE
════════════════════════════════════════════════════════════════════════════════

Echecs (1) — a corriger :
  ✗ LaFenetreNue

PS C:\...\...\Desktop\ani-2053\chapitre-03\exo1-la_fenetre_nue> jenga build

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

Build Order (1 projects):
  1. LaFenetreNue [WINDOWED_APP]


╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║  Project: LaFenetreNue                                                   Kind: WINDOWED_APP  ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

ℹ Found 1 source file(s)
✓   [1/1] Compiled: c3-exo1_main.cpp
ℹ Linking...
✓ Built: Build\Bin\Debug-Windows\LaFenetreNue\LaFenetreNue.exe

┌──────────────────────────────────────────────────────────────────────────────────────────────┐
│  ✓ Build Successful                                                             Time: 2.91s  │
└──────────────────────────────────────────────────────────────────────────────────────────────┘

════════════════════════════════════════════════════════════════════════════════
                                BUILD COMPLETED                                 
════════════════════════════════════════════════════════════════════════════════
Projects Built:  1/1
Time:           2.92s
Status:         ✓ SUCCESS
════════════════════════════════════════════════════════════════════════════════

PS C:\...\...\Desktop\ani-2053\chapitre-03\exo1-la_fenetre_nue> jenga run  

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
  ▶  EXECUTION  —  LaFenetreNue.exe
     C:\Users\... ...\Desktop\ani-2053\chapitre-03\Build\Bin\Debug-Windows\LaFenetreNue\LaFenetreNue.exe
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━


━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
  ◀  FIN D'EXECUTION  —  termine normalement  (10.54s)
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
PS C:\...\...\Desktop\ani-2053\chapitre-03\exo1-la_fenetre_nue> 
```
# II-LE PLUS PETIT PROGRAMME
## A-NOTRE REEL CODE "c3-exo1_main.cpp"
```cpp
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
```
### A-1-COMPTAGE DE LIGNES ET COMPARAISON
Il es visible que le code du chapitre celui presenter pas le prof lors de l'introduction des exercices sur la plateforme et presenter ci -dessous  es tres cours  par rapport au notre ces differencessnt du a de nombreux facteur comme :
* le code ci-dessous le code de bases presenter manque des fonction comme 
* La creation proprement dites de la fenetre avec window.create
* la gestion de la boucle d'evenements tant avec un booleen qu'avec les fonctions evenementielle, 
* Abscences du using namespaces nkentseu
#### A-1-1-1CODE MINIMALES PROPOSER
```cpp
#include "NKWindow/NKWindow.h"
#include "NKWindow/NKMain.h"

int nkmain(const NkEntryState &state) {
    NkWindowConfig cfg;
    cfg.title  = "Ma fenetre";
    cfg.width  = 1280;
    cfg.height = 720;

    NkWindow window(cfg);
    if (!window.IsOpen()) {
        logger.Error("[app] creation fenetre echouee");
        return -1;
    }
    while (window.IsOpen()) { /* les evenements arrivent ici */ }
    return 0;
}
```
### A-1-1-2-Quelque Similitude
```
* include : NkWindow/NkWindow.h et NkWindow/NkMain.h
* int nkmain
* variable.title
* variable.width
* variable.height
* creation et gestion du cas de non creation 
* boucle while pour la gestion des evenements
* return 0 (la porte de sortie)
```
## B-NOTRE FICHIER JENGA (pour le project celui qui uniqument notre fenetre)
```py
#!/usr/bin/env python3
# -*- coding: utf-8 -*-
# exo1-la_fenetre_nue - jenga Workspace

from Jenga import*
with project("LaFenetreNue"):
    windowedapp()
    language("C++")
    cppdialect("C++17")
    location(".")
    files(["c3-exo1_main.cpp"])
    usenkentseukit()
```
## C-NOTRE FICHIER JENGA(Pour le workspace celui qui vas gerer tous notre chapitre-03)
```py
#!/usr/bin/env python3
# -*- coding: utf-8 -*-
# exo1-la_fenetre_nue - jenga Workspace

from Jenga import*
with workspace("chapitre-03"):
    configurations(['Debug' , 'Release'])
    targetoses([TargetOS.WINDOWS])
    targetarchs([TargetArch.X86_64])

    useconfig("../chapitre-03/BRUNO/NkentseuKit.jenga")

    with include("exo1-la_fenetre_nue/exo1-la_fenetre_nue.jenga"):
        pass
```