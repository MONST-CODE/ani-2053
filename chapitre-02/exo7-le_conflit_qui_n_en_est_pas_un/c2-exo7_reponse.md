# Le conflit qui n'en es pas un 

il es question de modifier 2 parties independantes d'un fichier cloner dans deux repertoires differents et voi une  reaction plustot plus intelllignete de github
* Code de base
```
# include <iostream>

int main() {
    //Salutations
    std::cout << "Hello, World!" << std::endl;
    std::cout<<"Entrer votre Nom "<<std::endl;
    std::string nom;
    std::cin>>nom;
    std::cout<<"bonjour "<<nom<<std::endl;
    //double
    int age;
    std::cout<<"Entrer votre age "<<std::endl;
    std::cin>>age;
    std::cout<<" ======================================"<<std::endl;
    std::cout<<"||  le Double de votre age est "<<2*age<<"||"<<std::endl;
    std::cout<<" ======================================="<<std::endl;
    //Reprenons
    std::cout<<"On reprend "<<std::endl;
    std::cout<<"si tu ne donne pas je tchek"<<std::endl;
    std::cout<<"Ou je call leTeguis en renfort "<<std::endl;
    std::cout<<"j'ai les nerfs"<<std::endl;
    std::cout<<"je suis en train de coder et ca ne veux pas fonctionner"<<std::endl;
    std::cout<<"je suis en train de wanda"<<std::endl;
    std::cout<<"je vais abandonner 😭😭😭"<<std::endl;
    std::cout<<"je suis en train de pleurer"<<std::endl;
    
}
```
## Lancement des commandes
* Premier repertoire 
```
// Ici suppresion du "#include <iostream>"
PS C:\Users\CEO BRUNO ZAMBA\Desktop\git_essai> git add .                                                                               
PS C:\Users\CEO BRUNO ZAMBA\Desktop\git_essai> git commit -m "nous sommes dans le premier repertoire celui qui es au bureau reprenons-1"
[main 5d8229d] nous sommes dans le premier repertoire celui qui es au bureau reprenons-1
 1 file changed, 2 insertions(+), 2 deletions(-)
PS C:\Users\CEO BRUNO ZAMBA\Desktop\git_essai> git push                                                                                 
Enumerating objects: 5, done.
Counting objects: 100% (5/5), done.
Delta compression using up to 16 threads
Compressing objects: 100% (3/3), done.
Writing objects: 100% (3/3), 357 bytes | 119.00 KiB/s, done.
Total 3 (delta 2), reused 0 (delta 0), pack-reused 0 (from 0)
remote: Resolving deltas: 100% (2/2), completed with 2 local objects.
To https://github.com/MONST-CODE/git_essai
   6635db5..5d8229d  main -> main
PS C:\Users\CEO BRUNO ZAMBA\Desktop\git_essai>                                                                                          
```
* Deuxieme Repertoire (echec car pastrop d'espace on a toujurs on non fast forwards)
```cpp
//Ici supression du Return O ;
PS C:\Users\CEO BRUNO ZAMBA\Desktop\patr\git_essai> git add .                                                          
PS C:\Users\CEO BRUNO ZAMBA\Desktop\patr\git_essai> git commit -m "Nous sommes dans le deuxieme repertoire reprenons-1 "
[main 38c358c] Nous sommes dans le deuxieme repertoire reprenons-1
PS C:\Users\CEO BRUNO ZAMBA\Desktop\patr\git_essai> git push                                                            
To https://github.com/MONST-CODE/git_essai.git
 ! [rejected]        main -> main (fetch first)
error: failed to push some refs to 'https://github.com/MONST-CODE/git_essai.git'
hint: Updates were rejected because the remote contains work that you do not
hint: have locally. This is usually caused by another repository pushing to
hint: the same ref. If you want to integrate the remote changes, use
hint: 'git pull' before pushing again.
hint: See the 'Note about fast-forwards' in 'git push --help' for details.
PS C:\Users\CEO BRUNO ZAMBA\Desktop\patr\git_essai> git pull                                                            
remote: Enumerating objects: 5, done.
remote: Counting objects: 100% (5/5), done.
remote: Compressing objects: 100% (1/1), done.
remote: Total 3 (delta 2), reused 3 (delta 2), pack-reused 0 (from 0)
Unpacking objects: 100% (3/3), 337 bytes | 9.00 KiB/s, done.
From https://github.com/MONST-CODE/git_essai
   6635db5..5d8229d  main       -> origin/main
Merge made by the 'ort' strategy.
 commmit.cpp | 4 ++--
 1 file changed, 2 insertions(+), 2 deletions(-)
PS C:\Users\CEO BRUNO ZAMBA\Desktop\patr\git_essai> 
```
* Deuxieme repertoire reussite
```
PS C:\Users\CEO BRUNO ZAMBA\Desktop\patr\git_essai> git add .                                                           
PS C:\Users\CEO BRUNO ZAMBA\Desktop\patr\git_essai> git commit -m "Nous sommes dans le deuxieme repertoire reprenons-2 "
[main cbaee50] Nous sommes dans le deuxieme repertoire reprenons-2
 1 file changed, 5 insertions(+)
PS C:\Users\CEO BRUNO ZAMBA\Desktop\patr\git_essai> git push                                                            
fatal: unable to access 'https://github.com/MONST-CODE/git_essai.git/': Could not resolve host: github.com
PS C:\Users\CEO BRUNO ZAMBA\Desktop\patr\git_essai> git push
Enumerating objects: 41, done.
Counting objects: 100% (39/39), done.
Delta compression using up to 16 threads
Compressing objects: 100% (24/24), done.
Writing objects: 100% (28/28), 3.02 KiB | 343.00 KiB/s, done.
Total 28 (delta 12), reused 0 (delta 0), pack-reused 0 (from 0)
remote: Resolving deltas: 100% (12/12), completed with 3 local objects.
To https://github.com/MONST-CODE/git_essai.git
   5d8229d..cbaee50  main -> main
PS C:\Users\CEO BRUNO ZAMBA\Desktop\patr\git_essai> 
```
* Resultat
```
# include <iostream>

int main() {
    //Salutations
    std::cout << "Hello, World!" << std::endl;
    std::cout<<"Entrer votre Nom "<<std::endl;
    std::string nom;
    std::cin>>nom;
    std::cout<<"bonjour "<<nom<<std::endl;
    //double
    int age;
    std::cout<<"Entrer votre age "<<std::endl;
    std::cin>>age;
    std::cout<<" ======================================"<<std::endl;
    std::cout<<"||  le Double de votre age est "<<2*age<<"||"<<std::endl;
    std::cout<<" ======================================="<<std::endl;
    //Reprenons
    std::cout<<"On reprend "<<std::endl;
    std::cout<<"si tu ne donne pas je tchek"<<std::endl;
    std::cout<<"Ou je call leTeguis en renfort "<<std::endl;
    std::cout<<"j'ai les nerfs"<<std::endl;
    std::cout<<"je suis en train de coder et ca ne veux pas fonctionner"<<std::endl;
    std::cout<<"je suis en train de wanda"<<std::endl;
    std::cout<<"je vais abandonner 😭😭😭"<<std::endl;
    std::cout<<"je suis en train de pleurer"<<std::endl;
    




    return 0 ;
}
```