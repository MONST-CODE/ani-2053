## PREMIER PROJET

# Fichier Jenga
```
from Jenga import *
from jengaconfig import *

with project("MonEssai") :

  consoleapp()
  language("C++")
  cppdialect("C++17")
  location(".")

  files(["main.cpp"])

  targetdir("%{wks.location}/Build/Bin/%{cfg.buildcfg}-%{cfg.system}")
  objdir("%{wks.location}/Build/Obj/%{cfg.buildcfg}-%{cfg.system}/%{prj.name}")
        #Dependson n'etait pas present lors du drenier exo5 je l'ai ajoute pour observer la difference  
  #nkentseudependson(["NKPlatform"])

  with filter("system :Windows") :
    pass

```
# Fichier main.cpp 

Comme vous le remarquez dans le respect de l'exercices il n'affiche rien 
```
#include <iostream>

int main() {
    return 0;
}
```
# Logs de Compilation
```
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
[NKCode] ATTENTION : aucun wheel Jenga trouve (dist/*.whl) -> le paquet n'aura PAS de Jenga embarque, et les boutons Construire/Executer seront inoperants. Produisez-le avec ./cri.sh dans le depot Jenga.

Configuration: debug
Target:        Windows x86_64
Toolchain:     clang-mingw

Build Order (1 projects):
  1. MonEssai [CONSOLE_APP]


╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║  Project: MonEssai                                                        Kind: CONSOLE_APP  ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

ℹ Found 1 source file(s)
✓   [1/1] Compiled: main.cpp
ℹ Linking...
✓ Built: Build\Bin\Debug-Windows\MonEssai.exe

┌──────────────────────────────────────────────────────────────────────────────────────────────┐
│  ✓ Build Successful                                                             Time: 0.53s  │
└──────────────────────────────────────────────────────────────────────────────────────────────┘

════════════════════════════════════════════════════════════════════════════════
                                BUILD COMPLETED                                 
════════════════════════════════════════════════════════════════════════════════
Projects Built:  1/1
Time:           0.53s
Status:         ✓ SUCCESS
════════════════════════════════════════════════════════════════════════════════
```
