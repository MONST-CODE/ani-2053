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
* Commit de Chaque Section

