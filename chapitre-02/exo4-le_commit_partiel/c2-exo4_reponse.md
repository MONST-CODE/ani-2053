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
