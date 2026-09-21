# Les Trois endroits
* Creation de notre dossier et de notre fichier 
```
PS C:\....\....\Desktop\essai> git init
Initialized empty Git repository in C:/Users/CEO BRUNO ZAMBA/Desktop/essai/.git/
PS C:\...\...\Desktop\essai> git add 1.md
PS C:\...\...\Desktop\essai> git commit -m "premier fichier"
[main (root-commit) a71d3a9] premier fichier
 1 file changed, 0 insertions(+), 0 deletions(-)
 create mode 100644 1.md
```
* Controle permanent et apres chaque etape du status 
```
PS C:\...\..\Desktop\essai> git status                     
On branch main
Changes not staged for commit:
  (use "git add <file>..." to update what will be committed)
  (use "git restore <file>..." to discard changes in working directory)
        modified:   1.md

no changes added to commit (use "git add" and/or "git commit -a")
PS C:\..\...\Desktop\essai> git add 1.md                     
PS C:\....\...\Desktop\essai> git status  
On branch main
Changes to be committed:
  (use "git restore --staged <file>..." to unstage)
        modified:   1.md

PS C:\...\...\Desktop\essai> git commit -m "premier fichier a etre modifier "
[main f954ac2] premier fichier a etre modifier
 1 file changed, 1 insertion(+)
PS C:\...\..\Desktop\essai> git status                                      
On branch main
nothing to commit, working tree clean
PS C:\.....\...\Desktop\essai> 
```