# Le Commit Partiel 
il s'effectue en deux etapes  simples 
* choix de la section
* Commit de chaque section et push d'un coup 

## Choix de la section  
```bash
#La Commande a taper est
git add -p
```
vous verez ceci 
```cpp
PS C:\Users\CEO BRUNO ZAMBA\Desktop\git_essai> git add -p commmit.cpp
>> 
diff --git a/commmit.cpp b/commmit.cpp
new file mode 100644
index 0000000..562b18c
--- /dev/null
+++ b/commmit.cpp
@@ -0,0 +1,16 @@
+#include <iostream>
+
+int main() {
+    //Salutations
+    std::cout << "Hello, World!" << std::endl;
+    std::cout<<"Entrer votre Nom "<<std::endl;
+    std::string nom;
+    std::cin>>nom;
+    std::cout<<"bonjour "<<nom<<std::endl;
+    //double
+    int age;
+    std::cout<<"Entrer votre age "<<std::endl;
+    std::cin>>age;
+    std::cout<<"le Double de votreage est"<<2*age<<std::endl;
+    return 0;
+}
\ No newline at end of file
(1/1) Stage addition [y,n,q,a,d,e,p,P,?]? e
```
vous taper e qui veut dire edit un fichier aparaitra 

NB : (Attention : Ne touchez pas aux symboles + au début des lignes, laissez-les tels quels).

Apres modifications et apres avoir supprimer la partie qui devras venir en seconde section fermer le fichier vous aurez ceci ces lignes informes sur les modifications effectuer  

```c
<stdin>:16: trailing whitespace.
    
<stdin>:17: trailing whitespace.
    
<stdin>:18: trailing whitespace.
    
<stdin>:19: trailing whitespace.
    
<stdin>:20: trailing whitespace.
    
warning: 5 lines add whitespace errors.
```
## Commit de Chaque Section

* 1ere section
```bash
PS C:\Users\CEO BRUNO ZAMBA\Desktop\git_essai> git commit -m "ajout de la partie salutations"
[main 4408675] ajout de la partie salutations
 1 file changed, 16 insertions(+)
 create mode 100644 commmit.cpp
```
* 2eme section 

```bash
PS C:\''''\'''''\'''\git_essai> git add commit.cpp
fatal: pathspec 'commit.cpp' did not match any files
PS C:\'''\''''\'''\git_essai> git add commmit.cpp
PS C:\''''\''''\'''\git_essai> git commit -m "ajout de la partie double de l'age"
[main e67bd9a] ajout de la partie double de l'age
 1 file changed, 5 insertions(+), 5 deletions(-)
 ```
 * Push final
 ```bash
PS C:\'''\''''\'''\git_essai> git push origin main       
Enumerating objects: 7, done.
Counting objects: 100% (7/7), done.
Delta compression using up to 16 threads
Compressing objects: 100% (6/6), done.
Writing objects: 100% (6/6), 746 bytes | 746.00 KiB/s, done.
Total 6 (delta 3), reused 0 (delta 0), pack-reused 0 (from 0)
remote: Resolving deltas: 100% (3/3), completed with 1 local object.
To https://github.com/MONST-CODE/git_essai
   7f12003..e67bd9a  main -> main
PS C:\\''''\''''\git_essai> 
```
# Nuance nos test etait biaiser du fait que notre fichier etait neuf (a son Premier commit ) Reprenons .

```cpp
// On Reesaye mais ca a cuit 
PS C:\'\''''\''''\git_essai> git add -p commmit.cpp                            
>> 
diff --git a/commmit.cpp b/commmit.cpp
index fdbc8d5..d6034b9 100644
--- a/commmit.cpp
+++ b/commmit.cpp
@@ -11,6 +11,12 @@ int main() {
     int age;
     std::cout<<"Entrer votre age "<<std::endl;
     std::cin>>age;
-    std::cout<<"le Double de votre age est "<<2*age<<std::endl;
+    std::cout<<" ======================================"<<std::endl;
+    std::cout<<"||  le Double de votre age est "<<2*age<<"||"<<std::endl;
+    std::cout<<" ======================================="<<std::endl;
+    //Reprenons
+    std::cout<<"On reprend "<<std::endl;
+    std::cout<<"si tu ne donne pas je tchek"<<std::endl;
+    std::cout<<"Ou je call leTeguis en renfort "<<std::endl;
     return 0;
 }
\ No newline at end of file
(1/1) Stage this hunk [y,n,q,a,d,e,p,P,?]? y

PS C:\...\...\Desktop\git_essai> git add -p commmit.cpp
>> 
No changes.
PS C:\Users\CEO BRUNO ZAMBA\Desktop\git_essai> git add -p commmit.cpp
diff --git a/commmit.cpp b/commmit.cpp
index d6034b9..06b12a5 100644
--- a/commmit.cpp
+++ b/commmit.cpp
@@ -18,5 +18,6 @@ int main() {
     std::cout<<"On reprend "<<std::endl;
     std::cout<<"si tu ne donne pas je tchek"<<std::endl;
     std::cout<<"Ou je call leTeguis en renfort "<<std::endl;
+    std::cout<<"j'ai les nerfs"<<std::endl;
     return 0;
 }
\ No newline at end of file
(1/1) Stage this hunk [y,n,q,a,d,e,p,P,?]? e

PS C:\....\...\Desktop\git_essai> git commmit -m "1ere partie"
git: 'commmit' is not a git command. See 'git --help'.

The most similar command is
        commit
PS C:\....\...\Desktop\git_essai> git commit -m "1ere partie" 
[main 62f9618] 1ere partie
 1 file changed, 8 insertions(+), 1 deletion(-)
PS C:\...\...\Desktop\git_essai> git add commmit.cpp         
PS C:\....\.....\Desktop\git_essai> git commit -m "2eme Partie"
On branch main
Your branch is ahead of 'origin/main' by 1 commit.
  (use "git push" to publish your local commits)

nothing to commit, working tree clean
PS C:\....\...\Desktop\git_essai> git push
Enumerating objects: 5, done.
Counting objects: 100% (5/5), done.
Delta compression using up to 16 threads
Compressing objects: 100% (3/3), done.
Writing objects: 100% (3/3), 545 bytes | 545.00 KiB/s, done.
Total 3 (delta 1), reused 0 (delta 0), pack-reused 0 (from 0)
remote: Resolving deltas: 100% (1/1), completed with 1 local object.
To https://github.com/MONST-CODE/git_essai
   7ba3440..62f9618  main -> main
//Reel partie qui a marcher 
PS C:\....\....\Desktop\git_essai> git add -p commmit.cpp      
diff --git a/commmit.cpp b/commmit.cpp
index 06b12a5..ca25007 100644
--- a/commmit.cpp
+++ b/commmit.cpp
@@ -19,5 +19,8 @@ int main() {
     std::cout<<"si tu ne donne pas je tchek"<<std::endl;
     std::cout<<"Ou je call leTeguis en renfort "<<std::endl;
     std::cout<<"j'ai les nerfs"<<std::endl;
+    std::cout<<"je suis en train de coder et ca ne veux pas fonctionner"<<std::endl;
+    std::cout<<"je suis en train de wanda"<<std::endl;
+    std::cout<<"je vais abandonner 😭😭😭"<<std::endl;
     return 0;
 }
\ No newline at end of file
(1/1) Stage this hunk [y,n,q,a,d,e,p,P,?]? e
<stdin>:10: trailing whitespace.
    
<stdin>:11: trailing whitespace.
    
warning: 2 lines add whitespace errors.

PS C:\....\....\Desktop\git_essai> git commit -m "1ere reel partie"  
[main 8dd60d5] 1ere reel partie
 1 file changed, 3 insertions(+)
PS C:\\....\Desktop\git_essai> git add commmit.cpp             
PS C:\..\...\Desktop\git_essai> git commit -m "2eme Partie"     
[main 3698f12] 2eme Partie
 1 file changed, 2 insertions(+), 2 deletions(-)
PS C:\...\...\Desktop\git_essai> git push                        
Enumerating objects: 8, done.
Counting objects: 100% (8/8), done.
Delta compression using up to 16 threads
Compressing objects: 100% (6/6), done.
Writing objects: 100% (6/6), 677 bytes | 677.00 KiB/s, done.
Total 6 (delta 4), reused 0 (delta 0), pack-reused 0 (from 0)
remote: Resolving deltas: 100% (4/4), completed with 2 local objects.
To https://github.com/MONST-CODE/git_essai
   62f9618..3698f12  main -> main
PS C:\...\....\Desktop\git_essai> 