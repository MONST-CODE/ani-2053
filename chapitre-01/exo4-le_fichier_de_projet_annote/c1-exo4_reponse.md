## ANNOTATIONS ANLYSES ET INCOMPREHENSION : CAS DE NKGlad.jenga
```
#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
NKGlad - GLAD loader as standalone static library.
"""

from Jenga import *  #import des fonction et outils necessaire pour le fonctionnement denotre fichier .jenga 
from jengaconfig import * #fonction top secret nous permettant d'ecrire moins mais chaque avantage a un inconvenients 

with project("NKGlad"):
    staticlib()         #Bibliotheque static
    language("C")       #Language C
    location(".")       #A La Racine 

    includedirs([
        "include",
    ])

    files([
        "include/**.h",
    ])

    objdir("%{wks.location}/Build/Obj/%{cfg.buildcfg}-%{cfg.system}/%{prj.name}")
    targetdir("%{wks.location}/Build/Lib/%{cfg.buildcfg}-%{cfg.system}")

    with filter("system:Windows && options:windows-runtime=uwp"):
        objdir("%{wks.location}/Build/Obj/%{cfg.buildcfg}-%{cfg.system}-uwp/%{prj.name}")
        targetdir("%{wks.location}/Build/Lib/%{cfg.buildcfg}-%{cfg.system}-uwp")

    with filter("system:Windows && !options:windows-runtime=uwp && !system:XboxSeries && !system:XboxOne"):
        files([
            "src/gl.c",
            "src/wgl.c",
        ])     #System Windows et sa configurtaion elle nes pas tres explicite 

    with filter("system:Linux && options:linux-backend=xlib || system:Linux && !options:linux-backend && !options:headless"):
        files([
            "src/gl.c",
            "src/glx.c",
        ])     #System LInux et sa configurtaion elle nes pas tres explicite 

    with filter("system:Linux && options:linux-backend=xcb"):
        objdir("%{wks.location}/Build/Obj/%{cfg.buildcfg}-%{cfg.system}-xcb/%{prj.name}")
        targetdir("%{wks.location}/Build/Lib/%{cfg.buildcfg}-%{cfg.system}-xcb")
        files([
            "src/gl.c",
            "src/glx.c",
        ])     #System LInux et sa configurtaion elle nes pas tres explicite 

    with filter("system:Linux && options:linux-backend=wayland"):
        objdir("%{wks.location}/Build/Obj/%{cfg.buildcfg}-%{cfg.system}-wayland/%{prj.name}")
        targetdir("%{wks.location}/Build/Lib/%{cfg.buildcfg}-%{cfg.system}-wayland")
        files([
            "src/egl.c",
            "src/gles2.c",
        ])           #System LInux et sa configurtaion elle nes pas tres explicite 

    with filter("system:Linux && options:linux-backend=headless || system:Linux && options:headless"):
        objdir("%{wks.location}/Build/Obj/%{cfg.buildcfg}-%{cfg.system}-headless/%{prj.name}")
        targetdir("%{wks.location}/Build/Lib/%{cfg.buildcfg}-%{cfg.system}-headless")
        files([
            "src/gles2.c",
        ])       #System LInux et sa configurtaion elle nes pas tres explicite 

    with filter("system:macOS"):    #Mac Os
        files(["src/gl.c"])

    with filter("system:Android"):  #Android 
        files([
            "src/egl.c",
            "src/gles2.c",
        ])

    with filter("system:HarmonyOS"):   #System HarmonyOs
        files([
            "src/egl.c",
            "src/gles2.c",
        ])

    with filter("system:iOS"):  #System IOS
        files(["src/gles2.c"])

    with filter("system:Web"):
        files(["src/gles2.c"])
