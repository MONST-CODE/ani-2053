# LES 07 FENETRES
## 1-LA PREMIERES FENETRES LA PARFAITE
### 1-1-LA CONFIG
Pour notre fenetre parfaite la config implementr fut la suivante 
```cpp
//configurations de notre fenetre

    config.title = "7 fois la fenetre";
    config.width = 800;
    config.height = 600;
    config.resizable = true;
    config.centered      = true;        
    config.movable       = true;
    config.closable      = true;
    config.minimizable   = true;
    config.maximizable   = true;
    config.canFullscreen = true;
    config.fullscreen    = true;
```
### 1-1-LE RENDU OBSERVER
* resizable : oui mais nuancer  car le rendu de la fenetre ne subit pas le meme recalcul bon meme la SDL3 ne fait pas ca 
* centered : oui
* movable : oui
* closable : oui
* minimizable : fonctionne 
* maximizable fonctionne on ne sort pas de la fenetre 
* canfullscreen : non ne fonctionne
* fullscreen : non fonctionne pas

## 2-LA DEUXIEME FENETRE
### 2-1- la config fullscreen a false
Pour notre fenetre parfaite la config implementr fut la suivante 
```cpp
//configurations de notre fenetre

    config.title = "7 fois la fenetre";
    config.width = 800;
    config.height = 600;
    config.resizable = true;
    config.centered      = true;        
    config.movable       = true;
    config.closable      = true;
    config.minimizable   = true;
    config.maximizable   = true;
    config.canFullscreen = true;
    config.fullscreen    = false;  
```
### 2-1-Le RENDU OBSERVER
* resizable : oui mais nuancer  car le rendu de la fenetre ne subit pas le meme recalcul bon meme la SDL3 ne fait pas ca 
* centered : oui
* movable : oui
* closable : oui
* minimizable : fonctionne 
* maximizable fonctionne on ne sort pas de la fenetre 
* canfullscreen : non ne fonctionne
* fullscreen : fonctionne car on ne peut passer en plein ecran 
## 3-config canfullscren a false
### 1-1-LA CONFIG
Pour notre fenetre parfaite la config implementr fut la suivante 
```cpp
//configurations de notre fenetre

    config.title = "7 fois la fenetre";
    config.width = 800;
    config.height = 600;
    config.resizable = true;
    config.centered      = true;        
    config.movable       = true;
    config.closable      = true;
    config.minimizable   = true;
    config.maximizable   = true;
    config.canFullscreen = false;
    config.fullscreen    = true;
```
### 3-1-LE RENDU OBSERVER
* resizable : oui mais nuancer  car le rendu de la fenetre ne subit pas le meme recalcul bon meme la SDL3 ne fait pas ca 
* centered : oui
* movable : oui
* closable : oui
* minimizable : fonctionne 
* maximizable fonctionne on ne sort pas de la fenetre 
* canfullscreen : non ne fonctionne
* fullscreen : non fonctionne pas
## 4- config minimizable a false
### 4-1-LA CONFIG
Pour notre fenetre parfaite la config implementr fut la suivante 
```cpp
//configurations de notre fenetre

    config.title = "7 fois la fenetre";
    config.width = 800;
    config.height = 600;
    config.resizable = true;
    config.centered      = true;        
    config.movable       = true;
    config.closable      = true;
    config.minimizable   = false;
    config.maximizable   = true;
    config.canFullscreen = true;
    config.fullscreen    = true;
```
### 4-1-LE RENDU OBSERVER
* resizable : oui mais nuancer  car le rendu de la fenetre ne subit pas le meme recalcul bon meme la SDL3 ne fait pas ca 
* centered : oui
* movable : oui
* closable : oui
* minimizable : ne fonctionne plus
* maximizable fonctionne on ne sort pas de la fenetre 
* canfullscreen : non ne fonctionne
* fullscreen : non fonctionne pas 
## 5-Config maximizable a false
### 1-1-LA CONFIG
Pour notre fenetre parfaite la config implementr fut la suivante 
```cpp
//configurations de notre fenetre

    config.title = "7 fois la fenetre";
    config.width = 800;
    config.height = 600;
    config.resizable = true;
    config.centered      = true;        
    config.movable       = true;
    config.closable      = true;
    config.minimizable   = true;
    config.maximizable   = false;
    config.canFullscreen = true;
    config.fullscreen    = true;
```
### 5-1-LE RENDU OBSERVER
* resizable : oui mais nuancer  car le rendu de la fenetre ne subit pas le meme recalcul bon meme la SDL3 ne fait pas ca 
* centered : oui
* movable : oui
* closable : oui
* minimizable : fonctionne 
* maximizable : ne fonctionne pas
* canfullscreen : non ne fonctionne
* fullscreen : non fonctionne pas
## 6-config closable a false 
### 6-1-LA CONFIG closable a false
Pour notre fenetre parfaite la config implementr fut la suivante 
```cpp
//configurations de notre fenetre

    config.title = "7 fois la fenetre";
    config.width = 800;
    config.height = 600;
    config.resizable = true;
    config.centered      = true;        
    config.movable       = true;
    config.closable      = false;
    config.minimizable   = true;
    config.maximizable   = true;
    config.canFullscreen = true;
    config.fullscreen    = true;
```
### 6-1-LE RENDU OBSERVER
* resizable : oui mais nuancer  car le rendu de la fenetre ne subit pas le meme recalcul bon meme la SDL3 ne fait pas ca 
* centered : oui
* movable : oui
* closable : non ne fonctionne pas la fenetre peut toujours etre fermer
* minimizable : fonctionne 
* maximizable fonctionne on ne sort pas de la fenetre 
* canfullscreen : non ne fonctionne
* fullscreen : non fonctionne pas
## 7-Le cas movable a false
### 1-1-LA ONFIG
Pour notre fenetre parfaite la config implementr fut la suivante 
```cpp
//configurations de notre fenetre

    config.title = "7 fois la fenetre";
    config.width = 800;
    config.height = 600;
    config.resizable = true;
    config.centered      = true;        
    config.movable       = false;
    config.closable      = true;
    config.minimizable   = true;
    config.maximizable   = true;
    config.canFullscreen = true;
    config.fullscreen    = true;
```
### 7-1-LE RENDU OBSERVER
* resizable : oui mais nuancer  car le rendu de la fenetre ne subit pas le meme recalcul bon meme la SDL3 ne fait pas ca 
* centered : oui
* movable : non
* closable : oui
* minimizable : fonctionne 
* maximizable fonctionne on ne sort pas de la fenetre 
* canfullscreen : non ne fonctionne
* fullscreen : non fonctionne pas