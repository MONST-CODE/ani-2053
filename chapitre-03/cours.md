## Sprint 3
# Dans le livre : chapitres 3 et 4.

Ce que vous saurez faire en sortant de ce chapitre. 
* Ouvrir une fenêtre, la piloter, et trier ce qu'elle reçoit — clavier, souris, manette, système — aux trois hauteurs auxquelles on peut le faire.

- Ce chapitre réunit deux chapitres du livre : le chapitre 3 ouvre la fenêtre, le chapitre 4 lui apprend à écouter. Ils vont ensemble parce qu'une fenêtre qui ne reçoit rien ne sert à rien, et qu'un événement sans fenêtre n'existe pas.

## 1-Le plus petit programme
```
#include "NKWindow/NKWindow.h"
#include "NKWindow/NKMain.h"

int nkmain(const NkEntryState &state) {
    NkWindowConfig cfg;
    cfg.title  = "Ma fenetre";
    cfg.width  = 1280;
    cfg.height = 720;

    NkWindow window(cfg);
    if (!window.IsOpen()) {
        logger.Error("[app] creation fenetre echouee");
        return -1;
    }
    while (window.IsOpen()) { /* les evenements arrivent ici */ }
    return 0;
}
```
## 2-Trois choses à remarquer.

Vous n'écrivez pas de main. Vous écrivez nkmain. Derrière lui, le module fournit le point d'entrée natif de chaque plateforme : le WinMain de Windows, l'android_main d'Android, l'UIApplicationMain d'iOS. C'est le rôle de NKMain.h.

La configuration se donne au constructeur. La fenêtre est créée à ce moment-là ; ce qui vient après se règle par des méthodes.

On vérifie IsOpen. Une création peut échouer — pilote absent, serveur graphique inaccessible, permissions. Un programme qui continue après cela travaille dans le vide.

Le piège du chapitre. Oublier #include "NKWindow/NKMain.h" donne undefined reference to WinMain : une erreur d'édition de liens qui ne nomme aucun de vos fichiers. Retenez le symptôme général — une erreur de lien qui parle d'un symbole que vous n'avez jamais écrit est presque toujours un point d'entrée manquant.

Configurer et piloter la fenêtre
NkWindowConfig se lit par familles : l'identité et la taille (titre, largeur, hauteur), ce que l'utilisateur a le droit de faire (redimensionner, fermer, réduire), l'apparence et le rendu (bordure, transparence, contexte graphique).

Une fois ouverte, la fenêtre se pilote sur trois plans : l'état (visible, réduite, plein écran), la géométrie (position, taille) et le comportement.

Le facteur d'échelle mérite une attention à part : sur un écran dense, un pixel logique n'est pas un pixel physique. Le confondre donne une interface deux fois trop petite sur la moitié des machines.

Le module donne aussi le curseur (sa forme se redemande à chaque image, il faut le savoir), le fait de retenir la souris pour une caméra à la première personne, le presse-papiers en texte comme en image, et les dialogues du système — dont il existe une version asynchrone, parce qu'un dialogue bloquant gèle la boucle de rendu.

Quatorze plateformes sont derrière, dont une qui n'ouvre rien. Il y a trois manières honnêtes de traiter ce qui n'existe pas partout, et aucune ne consiste à faire semblant.

D'où viennent les événements
Un événement fait un chemin : le matériel, le système, la plateforme, puis le module — qui le traduit en une forme identique partout. C'est la quatrième étape qui vous intéresse, parce que c'est la seule que vous verrez.

Une distinction à ne jamais confondre : la lettre d'une touche et sa position physique. Pour un raccourci on veut la lettre ; pour un déplacement, la position — sinon un clavier AZERTY déplace le joueur avec ZQSD chez les uns et WASD chez les autres, et l'un des deux se plaint.

## 3-Les douze familles
* Famille	Ce qu'elle porte
WINDOW	fermeture, redimensionnement, déplacement, focus
* KEYBOARD	touche pressée, relâchée, caractère saisi
* MOUSE	boutons, déplacement, molette, entrée et sortie
* TOUCH	doigts posés, glissés, levés
* GAMEPAD	boutons, axes, branchement, vibration, batterie
* DROP	fichier, image ou texte déposé
* GRAPHICS	ce qui concerne le contexte de rendu
* SYSTEM	veille, réveil, changement d'écran
* APPLICATION	lancement, tick, rendu, fermeture
* TRANSFER	presse-papiers
* GENERIC_HID	périphériques exotiques
* CUSTOM	les vôtres
## Notez Bien
APPLICATION est celle qu'on oublie, et c'est la plus coûteuse à ignorer. Elle porte la mise en veille et le passage à l'arrière-plan. Sur mobile, ne pas les écouter a une conséquence immédiate : le système tue votre application sans prévenir, et le travail de l'utilisateur est perdu.

## 4-Trois hauteurs pour lire les entrées
* Première hauteur — la file. On la vide à chaque tour de boucle, on reconnaît le type, on consomme. La file a deux priorités, et un pointeur d'événement ne survit pas au prochain appel : si vous voulez le garder, copiez-le.

* Deuxième hauteur — l'état. Parfois on ne veut pas savoir quand la touche a été pressée, mais si elle l'est maintenant. On interroge alors l'état, manette comprise. Le déplacement brut de la souris existe pour les caméras, parce que la position à l'écran s'arrête au bord et pas le geste.

* Troisième hauteur — les intentions. C'est la partie que presque personne n'emploie, et qui change la façon d'écrire un jeu.
### Infos
Votre code contient NkKey::NK_SPACE à l'endroit du saut. Trois demandes arrivent et toutes les trois le cassent : l'utilisateur veut reconfigurer ses touches, il veut jouer à la manette, et vous voulez écrire un test qui joue tout seul. La cause est unique : votre code des règles connaît le clavier.

```
actions.CreateAction("sauter", [&](auto…, bool appuye, bool repetition) {
    if (appuye && !repetition) joueur.Sauter();
});
actions.AddCommand(NkActionCommand("sauter", NkInputCode::Key(NkKey::NK_SPACE)));
actions.AddCommand(NkActionCommand("sauter",
    NkInputCode::Gamepad(NkGamepadButton::NK_GP_SOUTH)));
```
Une action est un geste ponctuel, un axe une valeur continue. On les nomme, on leur attache autant de commandes qu'on veut, et le code des règles ne connaît plus que le nom. Les trois demandes du dessus deviennent gratuites — et ce qui varie d'un utilisateur à l'autre se range dans un fichier.
### Fin
Ce résumé et le cours magistral suffisent pour faire les exercices de ce sprint. Le livre du cours va plus loin : il montre le code réel du moteur, les fautes qu'on y a faites, et pourquoi. Il est disponible auprès de l'enseignant.