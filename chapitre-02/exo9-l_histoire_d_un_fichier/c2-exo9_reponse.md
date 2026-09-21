# L'Histoire d'un fichier 
 pour obtenir l'historique des commit d'un fichier d'un fichier la commande est 
 ```
 git log --follow <chemin_du_fichier>
```
## Cas de Nkentseu.jenga 

Dans notre cas nous avons choisis Nkentseu.jenga qui es situer a la racine de Nkentseu . ON obtient donc 
* historique commit
```
git log --follow Nkentseu.jenga 
commit addf709dcc2defa0d74dfa6f367b24f846551141
Author: LeTeguis <69282466+LeTeguis@users.noreply.github.com>
Date:   Thu Sep 10 17:23:43 2026 +0100

    NKCode beta.8 a beta.11 : la ligne publiee rejoint enfin main (#86)
    
    * NkEditMesh : la table CHAINEE etait le cout de chaque edition -- table plate, et le banc qui mesure enfin la PORTEE de chaque operation
    
    Deux choses, dans l ordre impose : d abord la mesure, ensuite le code.
    
    1. BANC DE PORTEE (--perf, hors reference)
```
* Historique et modif 
```
git log --follow -p <chemin_du_fichier>
```
```
1
Author: LeTeguis <69282466+LeTeguis@users.noreply.github.com>
Date:   Thu Sep 10 17:23:43 2026 +0100

    NKCode beta.8 a beta.11 : la ligne publiee rejoint enfin main (#86)
    
    * NkEditMesh : la table CHAINEE etait le cout de chaque edition -- table plate, et le banc qui mesure enfin la PORTEE de chaque operation
    
    Deux choses, dans l ordre impose : d abord la mesure, ensuite le code.
    
    1. BANC DE PORTEE (--perf, hors reference)
```
* Voire toutes les modifs subit par un fichier absolument toutes 
```
git blame <chemin_du_fichier>
```
```
git blame Nkentseu.jenga
a41122c30 (RihenUniverse     2026-03-01 17:17:22 +0100    1) #!/usr/bin/env python3
ba3b05072 (LeTeguis          2026-07-06 12:12:11 +0100    2) 
453f53a88 (Rihen             2026-03-01 14:24:20 +0100    3) # -*- coding: utf-8 -*-
ba3b05072 (LeTeguis          2026-07-06 12:12:11 +0100    4) 
bcc7c99d4 (LeTeguis          2026-05-21 13:36:03 +0100    5) r"""
ba3b05072 (LeTeguis          2026-07-06 12:12:11 +0100    6) 
453f53a88 (Rihen             2026-03-01 14:24:20 +0100    7) =============================================================================
ba3b05072 (LeTeguis          2026-07-06 12:12:11 +0100    8) 
453f53a88 (Rihen             2026-03-01 14:24:20 +0100    9) Nkentseu.jenga => Workspace principal du framework Nkentseu
ba3b05072 (LeTeguis          2026-07-06 12:12:11 +0100   10) 
453f53a88 (Rihen             2026-03-01 14:24:20 +0100   11) =============================================================================
```

