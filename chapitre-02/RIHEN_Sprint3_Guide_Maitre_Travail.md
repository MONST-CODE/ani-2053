# RIHEN ACADEMY — SPRINT 3
## Guide maître de travail — NKWindow, événements et entrées

> Manuel de travail personnel, conçu à partir des supports RIHEN Academy fournis dans la conversation.
> Il sert à comprendre, expérimenter, construire et rédiger les tâches du Sprint 3.
>
> **Principe de travail :** on utilise les squelettes et démarches ci-dessous pour produire son propre code et ses propres observations. Les valeurs expérimentales et conclusions de comportement doivent être mesurées sur la machine et le kit utilisés pour le rendu.

---

# 1. CARTE DU SPRINT

## Chapitre 3 — Fenêtre / NKWindow

### Série 1 — QCM

12 questions.

### Série 2 — Exercices
1. `c3-exo1` — La fenêtre nue
2. `c3-exo2` — Les sept droits
3. `c3-exo3` — Les bornes
4. `c3-exo4` — Le facteur d'échelle
5. `c3-exo5` — Le titre qui informe
6. `c3-exo6` — Les sept curseurs
7. `c3-exo7` — Le glisser qui sort
8. `c3-exo8` — Le presse-papiers, dans les deux sens
9. `c3-exo9` — Les quatre dialogues
10. `c3-exo10` — La fenêtre sans bordure
11. `c3-exo11` — Deux fenêtres
12. `c3-exo12` — L'inventaire des écrans

### Série 3 — Démonstrations
1. `c3-demo1` — Trente mille lignes pour une fenêtre
2. `c3-demo2` — Le défaut invisible
3. `c3-demo3` — La barre de titre à soi
4. `c3-demo4` — Le même programme sur deux systèmes

## Chapitre 4 — Événements / entrées

### Série 4 — QCM
12 questions.

### Série 5 — Exercices
1. `c4-exo1` — Le journal des événements
2. `c4-exo2` — La lettre et la position
3. `c4-exo3` — Fermer proprement
4. `c4-exo4` — Le pointeur qui meurt
5. `c4-exo5` — Le clic consommé
6. `c4-exo6` — Les trois hauteurs, sur le même geste
7. `c4-exo7` — Le front montant
8. `c4-exo8` — La manette
9. `c4-exo9` — La zone morte
10. `c4-exo10` — Les touches reconfigurables
11. `c4-exo11` — Le glisser-déposer complet
12. `c4-exo12` — Le rejeu

### Série 6 — Démonstrations
1. `c4-demo1` — Le chemin d'une touche
2. `c4-demo2` — Les trois hauteurs
3. `c4-demo3` — La reconfiguration en direct
4. `c4-demo4` — Le jeu qui se joue tout seul

---

# 2. ENVIRONNEMENT DE BASE

Le support montre une base de ce type :

```cpp
#include "NKWindow/NKWindow.h"
#include "NKWindow/NKMain.h"

int nkmain(const NkEntryState& state)
{
    NkWindowConfig cfg;
    cfg.title = "Ma fenetre";
    cfg.width = 1280;
    cfg.height = 720;

    NkWindow window(cfg);

    if (!window.IsOpen())
    {
        logger.Error("[app] creation fenetre echouee");
        return -1;
    }

    while (window.IsOpen())
    {
        // événements
    }

    return 0;
}
```

À retenir :

- `NKMain.h` fournit le point d'entrée portable ;
- l'API courante rencontrée dans ton kit attend `nkmain(const NkEntryState& state)` ;
- la configuration sert à la création ;
- l'objet `NkWindow` représente ensuite la fenêtre vivante ;
- `IsOpen()` sert à contrôler la durée de vie ;
- une modification runtime doit être faite via une méthode de l'objet quand elle existe (`SetTitle`, etc.).

---

# 3. API `NkWindow` DÉJÀ IDENTIFIÉE

```cpp
NkString GetTitle() const;
void SetTitle(const NkString &title);

math::NkVec2u GetSize() const;
math::NkVec2u GetPosition() const;

float32 GetDpiScale() const;

math::NkVec2u GetDisplaySize() const;
math::NkVec2u GetDisplayPosition() const;

NkError GetLastError() const;
NkWindowConfig GetConfig() const;
```

## Sens à garder en tête

### `GetSize()`
Information sur la taille actuelle de la fenêtre / zone cliente selon l'API de la version utilisée.

### `GetDisplaySize()`
Information sur l'écran / display auquel la fenêtre est associée.

### `GetDpiScale()`
Facteur d'échelle associé au contexte d'affichage.

### Cible de rendu
Surface dans laquelle le système de rendu produit effectivement les pixels. Ce n'est pas automatiquement le display et ce n'est pas nécessairement synonyme de la configuration initiale de la fenêtre. Si un exercice demande explicitement cette valeur, **retrouver le type/méthode dans le kit réel** au lieu d'inventer un getter.

---

# 4. RECHERCHE GLOBALE DANS VS CODE

Raccourci : **Ctrl + Shift + F**.

Recherches utiles :

```text
RenderTarget
GetRender
TargetSize
Create(
SetTitle
NkWindowResizeEvent
PollEvent
PollEventCopy
CaptureMouse
GetDpiScale
GetDisplaySize
```

Pour limiter aux sources C/C++ :

```text
**/*.{h,hpp,cpp,cxx}
```

Toujours vérifier le fichier réel de déclaration **et** l'implémentation lorsqu'un détail de comportement semble ambigu.

---

# 5. LES TROIS HAUTEURS DES ENTRÉES

## Hauteur 1 — événement

Question : **qu'est-ce qui vient d'arriver ?**

Exemples :

```text
KeyPressed
MouseMoved
WindowClose
```

## Hauteur 2 — état

Question : **quel est l'état actuel ?**

Exemples :

```text
la touche est-elle enfoncée ?
quel est l'axe actuel ?
```

## Hauteur 3 — intention / action

Question : **que veut faire le joueur ?**

Exemples :

```text
sauter
avancer
tirer
interagir
```

Une action nommée peut recevoir plusieurs commandes. Le gameplay ne doit alors plus connaître directement le clavier.

---

# 6. SÉRIE 1 — QCM `NKWindow`

Réponses de référence du support :

1. `nkmain`
2. point d'entrée manquant / en-tête oublié
3. empêcher la fenêtre de devenir trop petite
4. supprimer le déchirement en attendant le balayage
5. dessiner soi-même la barre de titre et ses boutons
6. la cible de rendu qui connaît les pixels réels
7. à chaque image
8. continuer à recevoir les mouvements quand le curseur sort pendant un glisser
9. pixels bruts
10. éviter de bloquer le rendu
11. faire tourner un programme sans affichage
12. ne rien faire sur une plateforme sans curseur, afin de conserver le code applicatif identique

---

# 7. C3-EXO1 — LA FENÊTRE NUE

## Mission

Ouvrir une fenêtre, la garder ouverte et se terminer proprement.

## Compétences

- includes corrects ;
- `nkmain` ;
- `NkWindowConfig` ;
- constructeur `NkWindow` ;
- `IsOpen` ;
- boucle de vie.

## Squelette

```cpp
#include "NKWindow/NKWindow.h"
#include "NKWindow/NKMain.h"

int nkmain(const NkEntryState& state)
{
    // TODO : traiter state si nécessaire

    // TODO : config
    // TODO : fenêtre
    // TODO : IsOpen
    // TODO : boucle

    return 0;
}
```

## Tests

- fenêtre visible ;
- fenêtre reste ouverte ;
- fermeture normale ;
- programme se termine réellement.

## `c3-exo1_reponse.md`

```md
# C3-EXO1 — La fenêtre nue

## Objectif
...

## API utilisées
...

## Méthode
1. ...
2. ...

## Observation
...

## Difficulté
...

## Correction
...

## Conclusion
...
```

---

# 8. C3-EXO2 — LES SEPT DROITS

## Mission

Ouvrir sept fenêtres successives, chacune avec un seul droit désactivé, et noter ce que l'utilisateur ne peut plus faire.

## Travail

Retrouver dans le `NkWindowConfig` du kit les sept propriétés concernées au lieu d'utiliser des noms supposés.

Table de travail :

| Fenêtre | Propriété | Action tentée | Résultat réel |
|---|---|---|---|
| 1 | ... | ... | ... |
| 2 | ... | ... | ... |
| 3 | ... | ... | ... |
| 4 | ... | ... | ... |
| 5 | ... | ... | ... |
| 6 | ... | ... | ... |
| 7 | ... | ... | ... |

## Leçon

La configuration décrit les capacités initiales de la fenêtre ; il faut distinguer ce qui est configuré de ce qui est observé réellement.

---

# 9. C3-EXO3 — LES BORNES

## Mission

Fixer une taille minimale, tenter de descendre sous cette limite, puis retirer la contrainte et recommencer.

## Variables centrales

```text
minWidth
minHeight
```

## Expérience

1. choisir une taille initiale ;
2. fixer les bornes ;
3. réduire au maximum ;
4. noter la plus petite taille ;
5. supprimer les bornes ;
6. recommencer ;
7. comparer.

## Rapport

```md
# C3-EXO3 — Les bornes

## Configuration initiale
...

## Bornes demandées
...

## Plus petite taille observée avec bornes
...

## Plus petite taille observée sans bornes
...

## Explication
...
```

---

# 10. C3-EXO4 — LE FACTEUR D'ÉCHELLE

## Mission

Afficher côte à côte la taille rendue par la fenêtre, celle demandée à la cible de rendu et le facteur d'échelle, puis obtenir une situation où le facteur n'est pas 1.

## API déjà identifiée

```cpp
auto size = window.GetSize();
auto displaySize = window.GetDisplaySize();
float32 scale = window.GetDpiScale();
```

### Important

`GetDisplaySize()` concerne le display/écran dans l'API `NkWindow`. Ne pas le renommer en « RenderTargetSize » sans vérifier le code.

## Première étape

Faire fonctionner seulement l'observation :

```text
Window: ...
Display: ...
DPI Scale: ...
```

## Deuxième étape

Rechercher dans le kit le composant qui expose la cible de rendu si le rendu est séparé :

```text
RenderTarget
GetRender
TargetSize
```

## Expérience DPI

1. relever l'échelle actuelle ;
2. exécuter ;
3. noter ;
4. changer l'échelle système ;
5. exécuter de nouveau ;
6. comparer.

## Ne jamais inventer les mesures

Le `md` doit contenir tes résultats réels.

## `c3-exo4_reponse.md`

```md
# C3-EXO4 — Le facteur d'échelle

## Hypothèse
...

## Réglage d'écran
...

## Mesure 1
Window = ...
Display = ...
DPI = ...
Target = ...

## Mesure 2
Window = ...
Display = ...
DPI = ...
Target = ...

## Ce qui change
...

## Ce qui reste stable
...

## Interprétation
...
```

---

# 11. C3-EXO5 — LE TITRE QUI INFORME

## Mission

Afficher dans le titre :

- nom du document ;
- `*` s'il est modifié ;
- taille courante.

Mise à jour uniquement lorsqu'une information a changé, et non à chaque image.

## État à gérer

```text
documentName
modified
width
height
```

## Architecture

```text
resize --------┐
               ├──> nouveau titre ──> SetTitle
modified ------┘
```

## Piège

Ne pas modifier uniquement `config.title` après création et s'attendre à changer une fenêtre déjà construite. Pour le runtime, chercher la méthode de l'objet (`SetTitle`).

## Construction du texte

Ne pas faire :

```cpp
NkString text = std::cout << ...;
```

`std::cout` est un flux de sortie. Construire d'abord le texte, puis éventuellement l'afficher et le passer à `SetTitle`.

---

# 12. C3-EXO6 — LES SEPT CURSEURS

## Mission

Découper la fenêtre en sept zones ; le curseur varie selon la zone. Puis ne demander le curseur qu'une seule fois au démarrage et expliquer le résultat.

## Recherche

```text
Ctrl+Shift+F → SetCursor
```

Puis retrouver les constantes / types de curseur réels du kit.

## Découpage possible

```text
haut-gauche | haut | haut-droite
gauche      | centre | droite
bas
```

Le découpage peut être organisé autrement ; il faut seulement obtenir sept zones distinctes et vérifiables.

## Expérience comparative

A. mise à jour selon la zone ;

B. appel unique au démarrage.

Le compte-rendu doit expliquer pourquoi le second cas ne suit pas le déplacement de la souris.

---

# 13. C3-EXO7 — LE GLISSER QUI SORT

## Mission

Même glisser deux fois : sans capture, puis avec capture.

## Expérience

```text
entrée fenêtre
↓
bouton maintenu
↓
sortie de fenêtre
↓
observer les mouvements
```

Puis refaire après `CaptureMouse`.

## Rapport

| Cas | Mouvement hors fenêtre reçu ? | Glisser continu ? |
|---|---|---|
| sans capture | ... | ... |
| avec capture | ... | ... |

---

# 14. C3-EXO8 — LE PRESSE-PAPIERS, DANS LES DEUX SENS

## Mission

Texte :

```text
presse-papiers → programme → majuscules → presse-papiers
```

Image :

```text
presse-papiers → programme → inversion RVB → presse-papiers
```

## Règle du support

Utiliser l'API publique de `NkWindow`, pas Win32 directement.

## Image

Inverser seulement `R`, `G`, `B` ; conserver l'alpha.

## Rapport obligatoire

- texte initial exact ;
- texte final exact ;
- dimensions de l'image ;
- bits par pixel ;
- ce qui a fonctionné ;
- limitation éventuelle.

---

# 15. C3-EXO9 — LES QUATRE DIALOGUES

## Mission

Employer les quatre dialogues natifs et traiter l'annulation dans chacun.

## Test systématique

Pour chaque dialogue :

1. ouvrir ;
2. choisir une valeur si possible ;
3. valider ;
4. annuler ;
5. fermer la boîte ;
6. vérifier que le programme reste cohérent.

## Recherche API

Dans le header public :

```text
dialog
async
cancel
```

Le support précise que les dialogues de ce moteur sont asynchrones.

---

# 16. C3-EXO10 — LA FENÊTRE SANS BORDURE

## Mission

Créer une fenêtre sans bordure avec :

- titre ;
- réduire ;
- agrandir ;
- fermer ;
- déplacement à la souris ;
- double-clic pour agrandir.

## Décomposition

```text
apparence
+ hit-test
+ clic
+ drag
+ double-clic
+ état fenêtre
```

## Piège majeur

Une fenêtre sans bordure transfère à l'application des comportements qui étaient auparavant fournis par le système.

---

# 17. C3-EXO11 — DEUX FENÊTRES

## Mission

Deux fenêtres ; afficher pour chaque clic laquelle l'a reçu ; expliquer ensuite ce qui manque pour dessiner réellement dans les deux.

## À identifier dans l'API

- focus ;
- référence de fenêtre dans l'événement, si elle existe ;
- association événement/instance ;
- cible de rendu.

Ne pas supposer le mécanisme : le retrouver dans le kit.

## Erreur déjà rencontrée

Avec une version actuelle de `NkWindow`, un appel :

```cpp
window.Create()
```

peut être invalide si la déclaration est :

```cpp
bool Create(const NkWindowConfig& config);
```

Dans ce cas :

```cpp
window.Create(config);
```

---

# 18. C3-EXO12 — L'INVENTAIRE DES ÉCRANS

## Mission

Pour chaque écran :

- taille ;
- position ;
- facteur d'échelle ;
- écran portant la fenêtre.

Puis déplacer la fenêtre et vérifier que les informations suivent.

## Plan

```text
liste displays
↓
pour chaque display
↓
position / taille / scale
↓
identifier le display courant de la fenêtre
```

---

# 19. C3-DEMO1 — TRENTE MILLE LIGNES POUR UNE FENÊTRE

## Démonstration

Montrer l'arborescence du module et deux backends qui répondent à un même appel public.

## Schéma oral

```text
application
  ↓
API NKWindow
  ↓
backend plateforme
  ↓
API native
```

## Ce qu'il faut conclure

La façade commune absorbe la diversité des plateformes, sans obliger le code applicatif à devenir un programme Win32/X11/Cocoa/etc.

---

# 20. C3-DEMO2 — LE DÉFAUT INVISIBLE

## Mission

Montrer une interface correcte sur une machine normale mais incorrecte à forte densité, puis corriger l'endroit où la taille est demandée.

## Idée

Le bug vient d'une confusion entre :

```text
espace logique
vs
pixels réels / cible de rendu
```

## Démonstration

1. construire un élément visuel avec une mauvaise source de taille ;
2. observer sur un réglage normal ;
3. observer sur un réglage haute densité ;
4. remplacer la source par celle adaptée au rendu ;
5. comparer.

---

# 21. C3-DEMO3 — LA BARRE DE TITRE À SOI

## Mission

Montrer la fenêtre sans bordure : déplacement, agrandissement, boutons.

## Conclusion

Retirer la barre système signifie récupérer l'apparence, mais aussi reprendre une partie de sa responsabilité : interaction, comportement et intégration.

---

# 22. C3-DEMO4 — LE MÊME PROGRAMME SUR DEUX SYSTÈMES

## Mission

Même binaire ou même source recompilée, deux systèmes, relever ce qui change sans changer le code applicatif.

## Tableau

| Aspect | Système A | Système B |
|---|---|---|
| fenêtre | ... | ... |
| DPI | ... | ... |
| événements | ... | ... |
| backend | ... | ... |

---

# 23. SÉRIE 4 — QCM ÉVÉNEMENTS / ENTRÉES

1. `NkScancode` = position physique.
2. Pour un déplacement, utiliser `NkScancode` afin de ne pas dépendre de l'agencement.
3. Pointeur de `PollEvent` valide jusqu'au prochain `PollEvent`.
4. `true` d'un gestionnaire = événement consommé.
5. Les modificateurs sont attachés à l'événement pour conserver leur état au moment de l'entrée.
6. La file prioritaire fait passer devant fermeture, veille, perte de contexte.
7. Le déplacement brut de souris sert notamment à la visée FPS.
8. Avant les axes d'une manette, vérifier qu'elle est branchée.
9. Une action nommée est une intention qu'on peut relier à plusieurs entrées.
10. Son premier bénéfice : le code des règles ne connaît plus le clavier.
11. Ce qui varie selon l'utilisateur doit vivre dans un fichier de configuration.
12. Ne gérer que clavier/souris rend le programme fragile lors de certains changements système comme veille/déconnexion d'écran.

---

# 24. C4-EXO1 — LE JOURNAL DES ÉVÉNEMENTS

## Mission

Journaliser chaque événement avec sa famille et son type, puis mesurer combien d'événements produit une seconde d'utilisation normale.

## Boucle

```text
PollEvent
↓
famille
↓
type
↓
log
```

## Tests

- mouvement ;
- clic ;
- frappe ;
- resize ;
- fermeture ;
- drop si possible.

## Rapport

Préciser la durée de mesure, la séquence d'actions et le total réellement obtenu.

---

# 25. C4-EXO2 — LA LETTRE ET LA POSITION

## Mission

Afficher lettre et code physique, changer l'agencement, recommencer.

## Principe

```text
NkKey      → logique / touche
NkScancode → position physique
```

## À démontrer

Ce qui change avec AZERTY/QWERTY et ce qui reste physiquement stable.

---

# 26. C4-EXO3 — FERMER PROPREMENT

## Mission

La fermeture doit passer par le même chemin depuis l'événement de fermeture.

## Chemin

```text
NkWindowCloseEvent
↓
Close()
↓
IsOpen == false
↓
fin de boucle
```

## Tests

Tester les différentes manières de demander la fermeture proposées par le sujet et expliquer la convergence vers le même chemin applicatif.

---

# 27. C4-EXO4 — LE POINTEUR QUI MEURT

## Mission

Conserver volontairement un pointeur d'événement d'une trame à l'autre, provoquer plusieurs événements et constater le problème, puis corriger avec `PollEventCopy`.

## Idée

```text
PollEvent()
↓
pointeur temporaire
```

n'est pas équivalent à :

```text
PollEventCopy()
↓
copie conservée par l'application
```

## Rapport

Expliquer :

- ce qu'on voulait conserver ;
- ce qui s'est réellement passé ;
- pourquoi ;
- comment la copie corrige.

---

# 28. C4-EXO5 — LE CLIC CONSOMMÉ

## Mission

Un panneau occupe un coin de la fenêtre. Un clic dans ce coin doit être consommé et ne pas atteindre le second gestionnaire.

## Logique

```text
handler panneau
↓
hit-test
↓
true si clic dans panneau
```

Hors panneau, le premier doit laisser passer afin que le second puisse travailler.

## Preuve

Le journal doit montrer :

```text
clic panneau → A seulement
clic extérieur → A puis B / B selon architecture
```

---

# 29. C4-EXO6 — LES TROIS HAUTEURS, SUR LE MÊME GESTE

## Mission

Faire avancer un carré à droite trois fois :

1. par événement ;
2. par interrogation d'état ;
3. par action nommée.

## Tableau de comparaison

| Technique | Le code connaît-il le clavier ? | Idéal pour |
|---|---|---|
| événement | à observer | transitions discrètes |
| état | plus direct | maintien / continu |
| action | non | gameplay découplé |

Le compte-rendu doit comparer les trois codes et dire ce que chacun connaît du matériel.

---

# 30. C4-EXO7 — LE FRONT MONTANT

## Mission

Faire sauter à l'espace avec interrogation d'état ; constater les sauts multiples ; ajouter une détection de front ; comparer avec la version événementielle.

## Algorithme

```cpp
pressedNow = ...;
justPressed = pressedNow && !pressedBefore;
pressedBefore = pressedNow;
```

Ce n'est qu'un squelette logique : adapter les types et l'API réelle.

## Explication

```text
false → true = nouvel appui
true  → true  = maintien
true  → false = relâchement
```

---

# 31. C4-EXO8 — LA MANETTE

## Mission

Piloter le même carré au clavier et à la manette sans dupliquer la logique. Traiter le débranchement en mettant le jeu en pause.

## Architecture

```text
clavier ─┐
         ├──> action / intention ───> gameplay
manette ─┘
```

## Cas débranchement

```text
GamepadRemoved / événement équivalent
↓
manette indisponible
↓
pause
```

Ne pas laisser une ancienne valeur continuer silencieusement à commander le jeu.

---

# 32. C4-EXO9 — LA ZONE MORTE

## Mission

Afficher la valeur brute d'un axe au repos pendant 10 secondes, relever la plus grande valeur absolue, choisir une zone morte et justifier.

## Mesure

```text
maxAbs = maximum(abs(valeur observée))
```

Le seuil final vient de **ta mesure réelle**.

## Rapport

```md
## Durée
10 s

## Max absolu observé
...

## Zone morte choisie
...

## Justification
...
```

---

# 33. C4-EXO10 — LES TOUCHES RECONFIGURABLES

## Mission

Écrire les mappings d'actions dans un fichier, charger au démarrage et offrir une modification à l'utilisateur.

## Architecture

```text
fichier
↓
lecture
↓
actions
↓
gameplay
```

## Principe

Le jeu connaît :

```text
"sauter"
"gauche"
"tirer"
```

Il ne doit pas contenir la touche physique comme dépendance de la logique métier.

---

# 34. C4-EXO11 — LE GLISSER-DÉPOSER COMPLET

## Mission

Traiter :

- entrée ;
- survol ;
- sortie ;
- texte ;
- fichier ;
- image.

Ajouter un feedback visuel pendant le survol.

## Machine d'état

```text
hors zone
  ↓ enter
sur zone
  ↓ leave
hors zone
```

Le feedback doit être visible et lié à cet état.

---

# 35. C4-EXO12 — LE REJEU

## Mission

Enregistrer toutes les actions déclenchées pendant une minute avec horodatage, puis les rejouer sans toucher au clavier.

## Structure logique

```text
timestamp
actionName
valeur éventuelle
```

Pipeline :

```text
entrées matérielles
↓
actions
↓
enregistreur
↓
fichier / mémoire
↓
rejoueur
↓
actions identiques
```

## Preuve

Faire un court scénario reproductible et montrer que la seconde exécution produit le même enchaînement.

---

# 36. C4-DEMO1 — LE CHEMIN D'UNE TOUCHE

## Mission

Suivre une touche depuis le backend de plateforme jusqu'au code applicatif et nommer les étapes.

## Schéma

```text
matériel
↓
pilote / OS
↓
backend plateforme
↓
abstraction NKWindow
↓
NkEvent
↓
PollEvent
↓
application
```

---

# 37. C4-DEMO2 — LES TROIS HAUTEURS

## Mission

Montrer le même geste à trois niveaux et faire choisir l'approche pour :

- menu ;
- déplacement ;
- saut ;
- raccourci ;
- visée.

La démonstration doit surtout montrer ce que l'abstraction gagne lorsqu'on remplace la dépendance directe au clavier par des actions.

---

# 38. C4-DEMO3 — LA RECONFIGURATION EN DIRECT

## Mission

Faire modifier les touches pendant l'exécution puis continuer à jouer.

## Preuve

```text
avant : touche A
changement de configuration
après : touche B
```

Le programme n'est pas recompilé pour ce changement.

---

# 39. C4-DEMO4 — LE JEU QUI SE JOUE TOUT SEUL

## Mission

Montrer une minute enregistrée puis rejouée à l'identique, et expliquer ce que cela permet pour les tests.

## Applications

- tests de régression ;
- reproduction d'un bug ;
- tests automatiques ;
- comparaison de versions.

---

# 40. GABARIT UNIVERSEL `*_reponse.md`

Utiliser ce squelette pour écrire ses propres observations :

```md
# [IDENTIFIANT] — [TITRE]

## 1. Objectif
...

## 2. Notions étudiées
- ...
- ...

## 3. API étudiées
- ...
- ...

## 4. Hypothèse
...

## 5. Méthode
1. ...
2. ...
3. ...

## 6. Résultats réels
...

## 7. Tableau de comparaison
| Cas | Résultat |
|---|---|
| ... | ... |

## 8. Explication
...

## 9. Difficultés
...

## 10. Correction
...

## 11. Ce que je retiens
...

## 12. Limites / remarques
...
```

---

# 41. COMMENTAIRES C++ : CE QUI A DE LA VALEUR

Préférer :

```cpp
// Le pointeur renvoyé par PollEvent n'est pas conservé au-delà de sa
// fenêtre de validité. Si l'information doit survivre, on utilise une copie.
```

à :

```cpp
// On incrémente i.
++i;
```

Un commentaire utile explique **pourquoi**, pas seulement **ce que la ligne fait**.

---

# 42. PIÈGES DÉJÀ RENCONTRÉS DANS TON PROJET

## Signature de `nkmain`

Si le linker demande :

```text
nkmain(nkentseu::NkEntryState const&)
```

vérifier la déclaration :

```cpp
int nkmain(const nkentseu::NkEntryState& state)
```

## `Create`

Si le header courant dit :

```cpp
bool Create(const NkWindowConfig& config);
```

alors :

```cpp
window.Create(config);
```

et non :

```cpp
window.Create();
```

## Casse des includes

Utiliser la casse réelle du dossier/header :

```cpp
#include "NKWindow/NKWindow.h"
#include "NKWindow/NKMain.h"
```

si le kit réel se trouve ainsi.

## `std::cout` et `NkString`

`std::cout` est un flux, pas une chaîne.

Séparer :

```text
construction du texte
↓
affichage éventuel
↓
SetTitle
```

## `i = i++`

Pour incrémenter clairement :

```cpp
++i;
```

---

# 43. MATRICE DE DÉBOGAGE

| Symptôme | Première piste |
|---|---|
| `undefined reference to WinMain` | `NKMain.h` / point d'entrée |
| `undefined reference to nkmain(...)` | signature de `nkmain` |
| `too few arguments to Create` | `Create(config)` attendu |
| warning `non-portable include path` | casse des chemins |
| fenêtre ferme immédiatement | boucle de vie / création |
| titre ne change pas | `SetTitle` runtime |
| plusieurs erreurs après une première | corriger d'abord la première |
| pointeur d'événement incohérent | durée de vie de `PollEvent()` |
| double activation | état sans front montant |
| jeu dépend du clavier | logique couplée au matériel |
| axe instable au repos | zone morte |
| manette débranchée mais jeu actif | gestion de l'état du périphérique |

---

# 44. PROTOCOLE EXPÉRIMENTAL

Une réponse solide suit :

```text
Hypothèse
↓
Implémentation
↓
Test contrôlé
↓
Observation réelle
↓
Interprétation
```

Ne pas transformer une valeur d'exemple en « résultat ». Une mesure doit venir de la machine utilisée.

---

# 45. PROTOCOLE DE COMPILATION

Après chaque modification significative :

```bash
jenga build
```

Lire la première erreur.

Corriger.

Recompiler.

Puis traiter la suivante.

Si le message est `undefined reference`, penser à l'étape d'édition de liens : symbole attendu absent, mauvais prototype ou mauvais point d'entrée.

---

# 46. ORDRE CONSEILLÉ DE PROGRESSION

```text
c3-exo4
→ c3-exo5
→ c3-exo6
→ c3-exo7
→ c3-exo8
→ c3-exo9
→ c3-exo11
→ c3-exo12
→ c3-demo1..4
→ c4-exo1
→ c4-exo2
→ c4-exo3
→ c4-exo4
→ c4-exo5
→ c4-exo6
→ c4-exo7
→ c4-exo8
→ c4-exo9
→ c4-exo10
→ c4-exo11
→ c4-exo12
→ c4-demo1..4
```

Commencer par les mécanismes qui seront réutilisés dans les grosses tâches.

---

# 47. CHECKLIST DE RENDU

## Fichiers

- [ ] nom exact ;
- [ ] dossier exact ;
- [ ] `*.cpp` compilé ;
- [ ] `*_reponse.md` présent ;
- [ ] aucun fichier temporaire ;
- [ ] dépôt public selon l'énoncé.

## Code

- [ ] signature de `nkmain` correspondant au kit courant ;
- [ ] includes avec la bonne casse ;
- [ ] API recherchée dans le kit réel ;
- [ ] pas d'appel système direct lorsqu'une abstraction NKWindow est demandée ;
- [ ] boucle de vie correcte ;
- [ ] fermeture propre ;
- [ ] pas de pointeur événement conservé par erreur ;
- [ ] données expérimentales affichées avec une unité/description claire.

## Markdown

- [ ] objectif ;
- [ ] méthode ;
- [ ] résultats réels ;
- [ ] observations ;
- [ ] difficulté ;
- [ ] correction ;
- [ ] conclusion.

---

# 48. FICHE ORALE FINALE

À la fin du Sprint, être capable d'expliquer sans lire :

### Fenêtre

- rôle de `nkmain` ;
- rôle de `NKMain.h` ;
- différence configuration / instance ;
- `GetSize` vs `GetDisplaySize` ;
- `GetDpiScale` ;
- notion de cible de rendu ;
- fenêtre sans bordure ;
- capture souris.

### Entrées

- événement vs état vs action ;
- `NkKey` vs `NkScancode` ;
- durée de vie de `PollEvent` ;
- consommation d'un événement ;
- mouvement brut ;
- zone morte ;
- débranchement manette ;
- configuration externe ;
- rejeu.

---

# 49. TABLEAU DE SUIVI PERSONNEL

| Tâche | Code écrit | Build | Test réel | `md` rédigé | Relecture | Déposé |
|---|---|---|---|---|---|---|
| c3-exo4 | ☐ | ☐ | ☐ | ☐ | ☐ | ☐ |
| c3-exo5 | ☐ | ☐ | ☐ | ☐ | ☐ | ☐ |
| c3-exo6 | ☐ | ☐ | ☐ | ☐ | ☐ | ☐ |
| c3-exo7 | ☐ | ☐ | ☐ | ☐ | ☐ | ☐ |
| c3-exo8 | ☐ | ☐ | ☐ | ☐ | ☐ | ☐ |
| c3-exo9 | ☐ | ☐ | ☐ | ☐ | ☐ | ☐ |
| c3-exo10 | ☐ | ☐ | ☐ | ☐ | ☐ | ☐ |
| c3-exo11 | ☐ | ☐ | ☐ | ☐ | ☐ | ☐ |
| c3-exo12 | ☐ | ☐ | ☐ | ☐ | ☐ | ☐ |
| c3-demo1 | ☐ | n/a | ☐ | ☐ | ☐ | ☐ |
| c3-demo2 | ☐ | n/a | ☐ | ☐ | ☐ | ☐ |
| c3-demo3 | ☐ | n/a | ☐ | ☐ | ☐ | ☐ |
| c3-demo4 | ☐ | n/a | ☐ | ☐ | ☐ | ☐ |
| c4-exo1 | ☐ | ☐ | ☐ | ☐ | ☐ | ☐ |
| c4-exo2 | ☐ | ☐ | ☐ | ☐ | ☐ | ☐ |
| c4-exo3 | ☐ | ☐ | ☐ | ☐ | ☐ | ☐ |
| c4-exo4 | ☐ | ☐ | ☐ | ☐ | ☐ | ☐ |
| c4-exo5 | ☐ | ☐ | ☐ | ☐ | ☐ | ☐ |
| c4-exo6 | ☐ | ☐ | ☐ | ☐ | ☐ | ☐ |
| c4-exo7 | ☐ | ☐ | ☐ | ☐ | ☐ | ☐ |
| c4-exo8 | ☐ | ☐ | ☐ | ☐ | ☐ | ☐ |
| c4-exo9 | ☐ | ☐ | ☐ | ☐ | ☐ | ☐ |
| c4-exo10 | ☐ | ☐ | ☐ | ☐ | ☐ | ☐ |
| c4-exo11 | ☐ | ☐ | ☐ | ☐ | ☐ | ☐ |
| c4-exo12 | ☐ | ☐ | ☐ | ☐ | ☐ | ☐ |
| c4-demo1 | ☐ | n/a | ☐ | ☐ | ☐ | ☐ |
| c4-demo2 | ☐ | n/a | ☐ | ☐ | ☐ | ☐ |
| c4-demo3 | ☐ | n/a | ☐ | ☐ | ☐ | ☐ |
| c4-demo4 | ☐ | n/a | ☐ | ☐ | ☐ | ☐ |

---

# 50. SOURCES / PORTÉE

Ce manuel reprend les intitulés, chemins de dépôt, objectifs et éléments de cours visibles dans les supports RIHEN Academy fournis dans cette conversation.

Lorsque le support ne donne pas le nom exact d'une API, le guide indique explicitement de la rechercher dans le kit local `BRUNO`.

Les résultats numériques, timings, dimensions, échelles, mesures d'axes et observations de comportement doivent être remplis à partir de la machine réellement utilisée.

---

# FIN

Le fil directeur du Sprint est simple :

```text
une API
↓
un mécanisme
↓
une expérience
↓
une observation
↓
une explication
```

Quand cette chaîne est maîtrisée, les exercices ne sont plus douze ou vingt-quatre problèmes isolés : ce sont des variations sur un petit ensemble de concepts que tu peux réutiliser.
