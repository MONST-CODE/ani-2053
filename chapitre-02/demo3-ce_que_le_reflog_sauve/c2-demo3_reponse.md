# DEMO 3 : Ce_que_le_reflog_sauve 
```cpp
//initialisation de notre depot
PS C:\...\...\Desktop\Exo1-git-reflog> git init
Initialized empty Git repository in C:/Users/CEO BRUNO ZAMBA/Desktop/Exo1-git-reflog/.git/
//Creation de nos fichiers test
PS C:\...\...\Desktop\Exo1-git-reflog> git add .
PS C:\...\...\Desktop\Exo1-git-reflog> git commit -m "vide"    
[main (root-commit) 3d51881] vide
 1 file changed, 1 insertion(+)
 create mode 100644 vide.txt
PS C:\...\...\Desktop\Exo1-git-reflog> git add .           
PS C:\...\....\Desktop\Exo1-git-reflog> git commit -m "fg.cpp"
[main f50346b] fg.cpp
 1 file changed, 5 insertions(+)
 create mode 100644 fg.cpp
PS C:\...\....\Desktop\Exo1-git-reflog> git add .             
PS C:\...\...\Desktop\Exo1-git-reflog> git commit -m "ex.cpp"
[main 8b3c2cb] ex.cpp
 2 files changed, 8 insertions(+), 1 deletion(-)
 create mode 100644 ex.cpp
PS C:\...\....\Desktop\Exo1-git-reflog> tree /F
Structure du dossier
Le numéro de série du volume est 60B3-DB66
C:.
    ex.cpp
    fg.cpp
    vide.txt
    
Aucun sous-dossier existant 

// Usage du Reset --hard

PS C:\...\...\Desktop\Exo1-git-reflog> git reset --hard HEAD~1
>> 
HEAD is now at f50346b fg.cpp
PS C:\...\...\Desktop\Exo1-git-reflog> tree /F                
Structure du dossier
Le numéro de série du volume est 60B3-DB66
C:.
    fg.cpp
    vide.txt
    
Aucun sous-dossier existant 

PS C:\...\....\Desktop\Exo1-git-reflog> git reset --hard HEAD~1
>> 
HEAD is now at 3d51881 vide

// Stop ici ces Bon car on a atteint le premier commit du depot on ne peut plus rien ces un peu comme  creuser et croiser une pierre indestructible (On s'arrete) 

PS C:\...\...\Desktop\Exo1-git-reflog> git reset --hard HEAD~1
>> 
fatal: ambiguous argument 'HEAD~1': unknown revision or path not in the working tree.
Use '--' to separate paths from revisions, like this:
'git <command> [<revision>...] -- [<file>...]'
PS C:\...\...\Desktop\Exo1-git-reflog> tree /F                
Structure du dossier
Le numéro de série du volume est 60B3-DB66
C:.
    vide.txt
    
Aucun sous-dossier existant 

//Usage de Reflog et test verificatifs pas a pas pour montrer les differentes evolution

PS C:\...\...\Desktop\Exo1-git-reflog> git reflog
>> 
3d51881 (HEAD -> main) HEAD@{0}: reset: moving to HEAD~1
f50346b HEAD@{1}: reset: moving to HEAD~1
8b3c2cb HEAD@{2}: commit: ex.cpp
f50346b HEAD@{3}: commit: fg.cpp
3d51881 (HEAD -> main) HEAD@{4}: commit (initial): vide
PS C:\...\....\Desktop\Exo1-git-reflog> git reset --hard 3d51881
HEAD is now at 3d51881 vide
PS C:\...\....\Desktop\Exo1-git-reflog> git reset --hard f50346b
HEAD is now at f50346b fg.cpp
PS C:\...\...\Desktop\Exo1-git-reflog> tree /F                 
Structure du dossier
Le numéro de série du volume est 60B3-DB66
C:.
    fg.cpp
    vide.txt
    
Aucun sous-dossier existant 

PS C:\...\...\Desktop\Exo1-git-reflog> git reset --hard 8b3c2cb
HEAD is now at 8b3c2cb ex.cpp
PS C:\...\....\Desktop\Exo1-git-reflog> tree /F                 
Structure du dossier
//Fin environnement regnerer completement avec succes
Le numéro de série du volume est 60B3-DB66
C:.
    ex.cpp
    fg.cpp
    vide.txt
    
Aucun sous-dossier existant 

PS C:\...\....\Desktop\Exo1-git-reflog> 
```