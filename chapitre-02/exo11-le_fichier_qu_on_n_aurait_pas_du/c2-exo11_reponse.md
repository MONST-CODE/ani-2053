# Le fichier que l'on Aurait pas du
* Ajout  commit et Push de notre fichier (Le fichier que on auraitpas du) 
```
PS C:\..\...\Desktop\Exo1-git-reflog> git add .
PS C:\..\...\Desktop\Exo1-git-reflog> git commit -m "Fichier Volumineux (10 ~ 11 Mb)" 
>> 
[main 0f8a1b9] Fichier Volumineux (10 ~ 11 Mb)
 1 file changed, 0 insertions(+), 0 deletions(-)
 create mode 100644 tout.zip
PS C:\...\...\Desktop\Exo1-git-reflog> git push
fatal: The current branch main has no upstream branch.
To push the current branch and set the remote as upstream, use

    git push --set-upstream origin main

To have this happen automatically for branches without a tracking
upstream, see 'push.autoSetupRemote' in 'git help config'.

PS C:\...\....\Desktop\Exo1-git-reflog> git push origin main                                   
Enumerating objects: 19, done.
Counting objects: 100% (19/19), done.
Delta compression using up to 16 threads
Compressing objects: 100% (16/16), done.
error: RPC failed; curl 55 Send failure: Connection was reset
send-pack: unexpected disconnect while reading sideband packet
Writing objects: 100% (18/18), 11.25 MiB | 322.00 KiB/s, done.
Total 18 (delta 3), reused 0 (delta 0), pack-reused 0 (from 0)
fatal: the remote end hung up unexpectedly
Everything up-to-date
PS C:\...\...\Desktop\Exo1-git-reflog> git push origin main
Enumerating objects: 19, done.
Counting objects: 100% (19/19), done.
Delta compression using up to 16 threads
Compressing objects: 100% (16/16), done.
Writing objects: 100% (18/18), 11.25 MiB | 1.76 MiB/s, done.
Total 18 (delta 3), reused 0 (delta 0), pack-reused 0 (from 0)
remote: Resolving deltas: 100% (3/3), done.
To https://github.com/MONST-CODE/Lereflog
   c69b7e2..0f8a1b9  main -> main
```
* Suppresion Manuelle Puis Nouvel synchronisation avec git(add et commit)
```
PS C:\..\...\Desktop\Exo1-git-reflog> git add .
>> git commit -m "Suppression du fichier volumineux"
[main c87f4d4] Suppression du fichier volumineux
 1 file changed, 0 insertions(+), 0 deletions(-)
 delete mode 100644 tout.zip
 ```
 * Recueil du poids de .git
 ```
PS C:\...\...\Desktop\Exo1-git-reflog> du -sh .git         
>>                                                  
du : Le terme «du» n'est pas reconnu comme nom d'applet de commande, fonction, fichier de script ou 
programme exécutable. Vérifiez l'orthographe du nom, ou si un chemin d'accès existe, vérifiez que le 
chemin d'accès est correct et réessayez.
Au caractère Ligne:1 : 1
+ du -sh .git
+ ~~
    + CategoryInfo          : ObjectNotFound: (du:String) [], CommandNotFoundException
    + FullyQualifiedErrorId : CommandNotFoundException
 
PS C:\..\...\Desktop\Exo1-git-reflog> ^C
PS C:\...\...\Desktop\Exo1-git-reflog> (Get-ChildItem .git -Recurse | Measure-Object -Property Length -Sum).Sum / 1MB
>> 
11.2840528488159
PS C:\..\..\Desktop\Exo1-git-reflog> 