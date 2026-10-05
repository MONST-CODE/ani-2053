# RIHEN ACADEMY — SPRINT 3
## GUIDE MAÎTRE ULTRA — CHAPITRES 3 & 4
### NKWindow · événements · entrées · méthode de résolution · validation · rédaction

> **Nature du document** : manuel de compréhension et de travail personnel.
>
> **But** : transformer chaque consigne courte du Sprint 3 en une consigne que l'on peut réellement comprendre, exécuter, tester et expliquer.
>
> **Méthode** : comprendre avant de coder, vérifier l'API réelle du kit avant d'inventer un nom de fonction, mesurer les comportements réellement observés, puis rédiger une réponse qui distingue clairement le fait, l'essai et la conclusion.
>
> **Important** : les morceaux de code ci-dessous sont des **références pédagogiques**. Ils ne remplacent ni la lecture du code du kit, ni la compilation, ni les observations de ta machine. Le travail final doit rester compris, adapté et vérifié par toi.

---

# 0. AUDIT DES SOURCES — CE QUI A ÉTÉ RETENU

## 0.1 Source pédagogique principale : RIHEN Academy Sprint 3

Le PDF fourni pour le Sprint 3 contient :

- le chapitre 3 sur la fenêtre `NKWindow` ;
- le chapitre 4 sur les événements et les entrées ;
- 12 exercices de fenêtre ;
- 4 démonstrations de fenêtre ;
- 12 QCM sur les événements et les entrées ;
- 12 exercices d'événements et d'entrées ;
- 4 démonstrations d'événements et d'entrées ;
- les noms exacts des dossiers et fichiers attendus pour les exercices.

Le document pédagogique insiste également sur plusieurs points méthodologiques : le code réellement évalué est celui du dépôt au moment du commit évalué ; les missions masquées existent ; le style peut être signalé sans être la base de la note ; les démonstrations sont destinées à montrer une compréhension, pas uniquement à faire tourner un programme.

## 0.2 Source technique prioritaire : dépôt actuel Nkentseu

Le dépôt public actuel de `Rihen-Universe/Nkentseu` se présente comme un framework C++ modulaire, C++17/20, sans STL pour les conteneurs et algorithmes principaux, avec un système de build maison nommé Jenga et plusieurs plateformes. Le README précise que le dépôt est en développement actif et avertit notamment que certains documents d'architecture peuvent diverger du code réel. Pour cette raison, **le code courant du kit doit être préféré à une ancienne documentation lorsqu'ils divergent**. citeturn962687view0

## 0.3 Dépôts de camarades fournis

Les trois dépôts suivants ont été pris en compte comme pistes demandées par l'utilisateur :

- `noumssiprisca6-star/ani-2053/chapitre-03`
- `dikoume-stephane/ani-2053/chapitre-03`
- `Nyeck-Abondo/ani-2053/chapitre-03`

**Limitation réelle** : les pages GitHub de ces trois dépôts n'ont pas pu être récupérées de façon fiable par l'outil web utilisé dans cette session. Je ne présente donc aucun de leurs choix de code comme une information vérifiée. Cette retenue est volontaire : mieux vaut une lacune déclarée qu'un faux “audit” de code.

---

# 1. LA RÈGLE D'OR DU SPRINT

Avant chaque exercice, pose-toi toujours les cinq questions suivantes :

1. **Qu'est-ce que le professeur me demande d'observer ou de démontrer ?**
2. **Quel objet du moteur est concerné ?**
3. **Quelle API réelle de mon kit réalise cette action ?**
4. **Quel test simple va prouver que mon programme fait bien ce qui est demandé ?**
5. **Qu'est-ce que je dois écrire dans le `.md` pour prouver ma compréhension ?**

Un exercice réussi n'est pas seulement : « ça compile ».

Il faut distinguer :

```text
COMPILATION
    ↓
EXÉCUTION
    ↓
COMPORTEMENT ATTENDU
    ↓
OBSERVATION
    ↓
EXPLICATION
    ↓
RÉPONSE ÉCRITE
```

---

# 2. VOCABULAIRE DU SPRINT — EXPLICATION EN FRANÇAIS COURANT

## 2.1 « Fenêtre »

Une fenêtre est ici la surface avec laquelle l'utilisateur interagit : elle possède une taille, une position, des capacités, un titre, un état et un lien avec le rendu.

### Exemple simple

Quand tu ouvres Notepad, la grande zone blanche n'est pas “toute l'application” au sens technique. Il existe une fenêtre qui possède une position, une largeur, une hauteur, une barre de titre, etc.

---

## 2.2 `NkWindowConfig`

C'est la configuration qui décrit **comment on souhaite créer la fenêtre**.

On peut y trouver, selon la version réelle du kit :

- le titre ;
- la largeur et la hauteur ;
- les dimensions minimales et maximales ;
- le fait qu'elle puisse être redimensionnée ;
- le fait qu'elle soit visible ;
- l'apparence du cadre ;
- le plein écran ;
- certaines options de comportement.

### Idée fondamentale

La configuration sert surtout à **définir les conditions de départ**.

Une fois la fenêtre créée, certaines propriétés se pilotent avec les méthodes de `NkWindow`.

---

## 2.3 `IsOpen()`

Cela permet de savoir si la fenêtre est encore ouverte.

### Exemple

C'est comme demander :

> « La porte est-elle encore ouverte ? »

Tant que la réponse est oui, la boucle de programme continue.

---

## 2.4 `GetSize()`

Dans le code actuel de `NkWindow`, `GetSize()` représente la taille de la **zone cliente**, c'est-à-dire la zone utile de la fenêtre et non la bordure décorative complète. Le contrat du `NkWindowConfig` emploie également largeur/hauteur, `GetSize()` et `SetSize()` comme dimensions de cette zone cliente. Cette précision est capitale pour éviter de confondre fenêtre physique, cadre et surface de rendu. 

---

## 2.5 `GetDisplaySize()`

Cela concerne la taille du moniteur / écran auquel on se réfère, pas simplement « la taille de ma fenêtre ».

### Exemple

Un écran peut faire 1920×1080 tandis que ta fenêtre ne fait que 1280×720.

---

## 2.6 `GetDpiScale()`

Le facteur d'échelle permet de représenter le cas où les pixels logiques et les pixels physiques ne correspondent pas un pour un.

### Exemple très simple

Sur un écran standard :

```text
1 unité logique ≈ 1 pixel physique
```

Sur un écran haute densité :

```text
1 unité logique peut correspondre à plusieurs pixels physiques
```

Le PDF utilise précisément ce phénomène pour montrer pourquoi une interface peut sembler correcte sur une machine puis trop petite sur une autre.

---

## 2.7 « événement »

Un événement est une information sur **quelque chose qui vient de se produire**.

Exemples :

```text
La fenêtre reçoit une demande de fermeture.
Une touche est pressée.
Un bouton de souris est relâché.
La fenêtre est redimensionnée.
Un périphérique est branché.
Un fichier est déposé.
```

---

## 2.8 « état »

L'état répond plutôt à :

> « Qu'est-ce qui est vrai maintenant ? »

Exemple :

```text
Événement : la touche espace vient d'être pressée.
État : la touche espace est-elle actuellement maintenue ?
```

---

## 2.9 « action nommée »

Au lieu d'écrire :

```text
si la touche espace est pressée → sauter
```

on préfère, à un niveau plus abstrait :

```text
si l'action "sauter" est déclenchée → sauter
```

L'action peut alors être associée à plusieurs commandes : clavier, manette, autre configuration.

---

# 3. SQUELETTE DE DÉPART FIABLE

Le PDF donne une base conceptuelle de programme très courte : inclusion de `NKWindow`, inclusion de `NKMain`, création d'une configuration, création d'une fenêtre, vérification de `IsOpen()`, puis boucle de vie. Le rôle de `NKMain.h` est notamment d'éviter d'avoir à écrire directement le point d'entrée natif spécifique à chaque plateforme. citeturn962687view0

Dans ton kit actuel, vérifie toujours la **signature exacte** attendue par le linker. Dans les versions récentes observées dans ton environnement, la forme rencontrée est de type :

```cpp
#include "NKWindow/NKWindow.h"
#include "NKWindow/NKMain.h"

int nkmain(const nkentseu::NkEntryState& state)
{
    // Le paramètre state appartient au point d'entrée du moteur.
    // On évite de l'inventer ou de le remplacer par main().

    nkentseu::NkWindowConfig config;

    // Configuration minimale de départ.
    config.title  = "Mon exercice";
    config.width  = 1280;
    config.height = 720;

    // La fenêtre est créée à partir de cette configuration.
    nkentseu::NkWindow window(config);

    // Toujours vérifier la réussite de la création.
    if (!window.IsOpen())
    {
        return -1;
    }

    // Boucle de vie minimale.
    while (window.IsOpen())
    {
        // Les événements et les traitements de l'exercice arrivent ici.
    }

    return 0;
}
```

### Si ton kit refuse cette signature

Ne modifie pas « au hasard » le type de retour ou le nom de la fonction. Lis l'erreur du linker et vérifie le `NKMain.h` réel du kit installé. Une erreur du type :

```text
undefined reference to nkmain(nkentseu::NkEntryState const&)
```

signifie généralement que le moteur recherche une signature précise et que ton programme n'en fournit pas une identique.

---

# 4. MÉTHODE DE LECTURE D'UNE CONSIGNE COURTE

Prenons une phrase de professeur :

> « Affichez la taille, le facteur d'échelle et la cible de rendu. »

Ne code pas immédiatement.

Découpe :

```text
affichez
= produire une information visible

la taille
= taille de quel objet ? fenêtre ? écran ? surface ?

facteur d'échelle
= demander l'information de DPI / scaling

target de rendu
= identifier l'objet ou l'API qui représente réellement la cible de rendu
```

Puis seulement :

```text
API réelle → test → affichage → observation
```

C'est cette méthode qui évite 80 % des erreurs d'interprétation.

---

# 5. CHAPITRE 3 — NKWINDOW

---

# C3-EXO1 — LA FENÊTRE NUE

## 5.1 Ce que le professeur dit, en très court

Créer le plus petit programme capable d'ouvrir une fenêtre, de la garder ouverte et de sortir proprement.

## 5.2 Ce que cela veut réellement dire

Le professeur ne demande pas :

- une interface graphique compliquée ;
- un menu ;
- une animation ;
- plusieurs fichiers inutiles ;
- un moteur de jeu complet.

Il demande uniquement de montrer que tu sais faire vivre le cycle minimal :

```text
point d'entrée
→ configuration
→ création
→ vérification
→ vie de la fenêtre
→ fermeture
→ fin du programme
```

## 5.3 Exemple accessible

Imagine une lampe :

```text
j'appuie sur l'interrupteur
→ elle s'allume
→ elle reste allumée
→ j'éteins
→ le système s'arrête proprement
```

Ici :

```text
création fenêtre
→ fenêtre ouverte
→ attente / boucle
→ fermeture
→ retour de nkmain
```

## 5.4 Résolution la plus sûre

Commencer par le squelette minimal validé par le PDF, puis ne rien ajouter tant que la fenêtre nue n'est pas stable.

## 5.5 Code de référence commenté

```cpp
#include "NKWindow/NKWindow.h"
#include "NKWindow/NKMain.h"

int nkmain(const nkentseu::NkEntryState& state)
{
    // Configuration de départ de la fenêtre.
    nkentseu::NkWindowConfig config;

    // Titre visible par l'utilisateur.
    config.title = "C3-EXO1 - Fenetre nue";

    // Taille initiale choisie pour l'expérience.
    config.width = 1280;
    config.height = 720;

    // Création de la fenêtre à partir de la configuration.
    nkentseu::NkWindow window(config);

    // Une création peut échouer : on ne poursuit pas à l'aveugle.
    if (!window.IsOpen())
    {
        return -1;
    }

    // Tant que la fenêtre est ouverte, l'application continue.
    while (window.IsOpen())
    {
        // Pour cet exercice, rien de complexe n'est nécessaire ici.
        // Le but est de comprendre le cycle de vie minimal.
    }

    // Sortie normale du point d'entrée.
    return 0;
}
```

## 5.6 Test obligatoire

Tu dois vérifier séparément :

- la fenêtre apparaît ;
- elle ne disparaît pas immédiatement ;
- le bouton de fermeture fonctionne ;
- le programme se termine réellement ;
- aucun crash ne se produit.

## 5.7 Rapport `.md`

```md
# C3-EXO1 — La fenêtre nue

## Objectif

Construire le plus petit programme capable d'ouvrir une fenêtre, de la maintenir ouverte et de la fermer proprement.

## API utilisées

- NkWindowConfig
- NkWindow
- IsOpen
- nkmain

## Méthode

1. Création de la configuration.
2. Création de la fenêtre.
3. Vérification de IsOpen().
4. Attente dans la boucle principale.
5. Sortie après fermeture.

## Observation

Décrire ce qui s'est réellement produit sur la machine.

## Difficultés

...

## Correction

...

## Conclusion

...
```

---

# C3-EXO2 — LES SEPT DROITS

## 6.1 Traduction de la consigne

Tu dois créer **sept expériences séparées**.

Dans chaque expérience, tu désactives **un seul droit / pouvoir de l'utilisateur**.

Puis tu essaies l'action correspondante et tu notes le résultat.

Le but n'est pas de connaître sept noms par cœur : le but est de comprendre qu'une configuration peut retirer des capacités à la fenêtre.

## 6.2 Exemple simple

Imagine une porte dont tu peux régler :

```text
ouvrir
fermer
bouger
agrandir
réduire
etc.
```

Pour chaque test :

```text
je coupe une capacité
→ je tente l'action
→ j'observe
→ je note
```

## 6.3 Première difficulté importante

Le mot « droit » dans le sujet est une manière pédagogique de parler d'une capacité comportementale.

**Ne devine pas les noms des champs.**

Le `NkWindowConfig` actuel expose notamment des propriétés comme `resizable`, `movable`, `closable`, `minimizable`, `maximizable`, ainsi que d'autres options d'état et d'apparence ; le fichier réel doit rester ta référence pour la version de ton kit.

## 6.4 Résolution la plus sûre

Créer une petite table expérimentale et construire chaque fenêtre à partir de la même configuration de base, en modifiant un seul champ à la fois.

```text
BASE
 ├─ test 1 : un droit désactivé
 ├─ test 2 : un autre droit désactivé
 ├─ ...
 └─ test 7 : dernier droit désactivé
```

## 6.5 Structure de code recommandée

```cpp
#include "NKWindow/NKWindow.h"
#include "NKWindow/NKMain.h"

int nkmain(const nkentseu::NkEntryState& state)
{
    nkentseu::NkWindowConfig config;

    config.title = "C3-EXO2 - Test des droits";
    config.width = 800;
    config.height = 500;

    // IMPORTANT : ne modifier qu'une propriété par expérimentation.
    // Exemple :
    // config.resizable = false;

    nkentseu::NkWindow window(config);

    if (!window.IsOpen())
    {
        return -1;
    }

    while (window.IsOpen())
    {
    }

    return 0;
}
```

## 6.6 Tableau à remplir

| Test | Propriété modifiée | Action tentée | Résultat réel | Explication |
|---|---|---|---|---|
| 1 | ... | ... | ... | ... |
| 2 | ... | ... | ... | ... |
| 3 | ... | ... | ... | ... |
| 4 | ... | ... | ... | ... |
| 5 | ... | ... | ... | ... |
| 6 | ... | ... | ... | ... |
| 7 | ... | ... | ... | ... |

## 6.7 Ce qu'il ne faut surtout pas écrire

Évite une conclusion comme :

> « Ça ne marche pas. »

Écris plutôt :

> « Avec `resizable = false`, le redimensionnement manuel par le bord de la fenêtre n'a plus produit de changement visible de taille. Le comportement observé correspond à la désactivation de la capacité de redimensionnement. »

---

# C3-EXO3 — LES BORNES

## 7.1 Traduction ultra simple

Tu vas faire deux expériences :

### Expérience A

Tu imposes une taille minimale.

Puis tu essaies de rendre la fenêtre encore plus petite.

### Expérience B

Tu enlèves la taille minimale.

Puis tu recommences.

Enfin, tu compares les tailles minimales réellement observées.

## 7.2 Exemple

Tu dis :

```text
minimum = 400 × 300
```

Puis tu tires le bord de la fenêtre vers l'intérieur.

La question est :

> « Jusqu'où le système me laisse-t-il aller ? »

## 7.3 Résolution la plus sûre

Faire une expérience contrôlée : même taille initiale, même fenêtre, même machine, seule la contrainte change.

## 7.4 Code de référence

```cpp
#include "NKWindow/NKWindow.h"
#include "NKWindow/NKMain.h"

int nkmain(const nkentseu::NkEntryState& state)
{
    nkentseu::NkWindowConfig config;

    config.title = "C3-EXO3 - Les bornes";
    config.width = 1000;
    config.height = 700;

    // Taille minimale imposée pour l'expérience.
    config.minWidth = 400;
    config.minHeight = 300;

    nkentseu::NkWindow window(config);

    if (!window.IsOpen())
    {
        return -1;
    }

    while (window.IsOpen())
    {
    }

    return 0;
}
```

### Deuxième passage

Refais exactement la même expérience en retirant ou neutralisant la contrainte minimale de la configuration.

## 7.5 Rapport

```md
# C3-EXO3 — Les bornes

## Configuration de départ
Largeur : ...
Hauteur : ...

## Avec borne minimale
Minimum demandé : ... × ...
Plus petite taille observée : ... × ...

## Sans borne minimale
Plus petite taille observée : ... × ...

## Comparaison
...

## Explication
...

## Conclusion
...
```

---

# C3-EXO4 — LE FACTEUR D'ÉCHELLE

## 8.1 Traduction ultra simple

Le professeur veut que tu montres **plusieurs notions de taille qui ne doivent pas être confondues**.

Il faut notamment afficher la taille de la fenêtre / zone de rendu pertinente, la taille réellement associée à la cible de rendu selon le contrat de ton kit, et le facteur d'échelle.

## 8.2 Exemple très simple

Une fenêtre peut être visuellement donnée comme :

```text
1280 × 720
```

alors que l'environnement graphique applique un facteur de densité particulier.

Le but est de voir que « largeur de fenêtre » et « pixels physiques utilisés pour rendre » ne sont pas des concepts à mélanger sans vérifier le contrat de l'API.

## 8.3 API confirmées dans le code actuel

Le `NkWindow` courant expose au minimum :

```cpp
GetSize()
GetDpiScale()
GetDisplaySize()
GetSurfaceDesc()
```

Le point délicat : **ne pas inventer ce que retourne `GetSurfaceDesc()`**. Pour cette partie précise, ouvre la définition de `NkSurfaceDesc` dans ton kit local et relève ses champs avant d'écrire la dernière ligne d'affichage.

## 8.4 Résolution la plus sûre

Commence par afficher les données dont le contrat est sûr :

```cpp
auto windowSize = window.GetSize();
auto displaySize = window.GetDisplaySize();
float scale = window.GetDpiScale();
```

Puis, si l'exercice exige explicitement la surface de rendu, exploite `GetSurfaceDesc()` seulement après avoir lu sa définition réelle.

## 8.5 Base de code

```cpp
#include "NKWindow/NKWindow.h"
#include "NKWindow/NKMain.h"

int nkmain(const nkentseu::NkEntryState& state)
{
    nkentseu::NkWindowConfig config;
    config.title = "C3-EXO4 - Facteur d'echelle";
    config.width = 1280;
    config.height = 720;

    nkentseu::NkWindow window(config);

    if (!window.IsOpen())
    {
        return -1;
    }

    auto windowSize = window.GetSize();
    auto displaySize = window.GetDisplaySize();
    float scale = window.GetDpiScale();

    // Remplacer / compléter la partie surface après lecture du vrai NkSurfaceDesc.
    // Exemple conceptuel :
    // auto surface = window.GetSurfaceDesc();

    // Utiliser le mécanisme de journalisation disponible dans ton kit.
    // L'exemple d'affichage doit être adapté à la vraie API de logger utilisée dans ton projet.

    while (window.IsOpen())
    {
        // Ici, on peut rafraîchir les valeurs après un redimensionnement si nécessaire.
        // Ne pas figer des valeurs qui sont censées représenter l'état courant.
    }

    return 0;
}
```

## 8.6 Expérience DPI

Il faut obtenir un facteur différent de 1 si possible :

- écran différent ; ou
- réglage d'échelle système différent.

Ne fabrique pas la valeur. Relève-la.

## 8.7 Rapport

```md
# C3-EXO4 — Le facteur d'échelle

## Machine / écran utilisé
...

## Valeurs observées
- Taille fenêtre / zone cliente : ...
- Taille écran : ...
- Facteur d'échelle : ...
- Informations de cible de rendu : ...

## Test avec échelle = 1
...

## Test avec échelle différente de 1
...

## Interprétation
...

## Conclusion
...
```

---

# C3-EXO5 — LE TITRE QUI INFORME

## 9.1 Traduction

Le titre de la fenêtre doit montrer trois informations :

```text
nom du document
+ * si le document est modifié
+ taille actuelle de la fenêtre
```

Exemple :

```text
rapport.txt * — 1280×720
```

## 9.2 « Au bon moment, pas à chaque image » signifie quoi ?

Le professeur veut éviter une mauvaise pratique consistant à faire :

```cpp
while (window.IsOpen())
{
    window.SetTitle(...); // à chaque tour
}
```

Même si cela fonctionne, le titre n'a pas besoin d'être réécrit des milliers de fois lorsque rien n'a changé.

## 9.3 Résolution la plus sûre

Mettre à jour le titre quand l'information dépendante change :

- document modifié ou sauvegardé ;
- taille de fenêtre modifiée.

Pour une première version pédagogique, tu peux commencer par reconstruire le titre lorsque tu détectes une variation de taille, puis brancher la logique `modified` lorsque le modèle de document existe.

## 9.4 Code de référence

```cpp
// Pseudo-architecture volontairement simple :
bool modified = false;
NkString documentName = "document.txt";

// La vraie construction de NkString doit suivre les outils de ton kit.
// Ne traite pas std::cout comme une NkString.

// Quand la taille change :
// 1. récupérer GetSize()
// 2. reconstruire le titre
// 3. appeler SetTitle()

// Exemple de logique :
// "document.txt" + (modified ? " *" : "") + " — " + largeur + "x" + hauteur
```

## 9.5 Piège important

Ne fais pas :

```cpp
NkString nom = std::cout << ...;
```

`std::cout` est un flux de sortie, pas un `NkString`.

Et ne tente pas de modifier `config.title` en pensant que cela changera automatiquement le titre d'une fenêtre déjà créée : après création, utilise la méthode de pilotage de fenêtre prévue par le kit, notamment `SetTitle()`.

---

# C3-EXO6 — LES SEPT CURSEURS

## 10.1 Traduction

Découpe ta fenêtre en sept zones.

Quand la souris passe dans une zone, le curseur doit prendre une forme différente.

Puis fais une deuxième expérience : ne définis le curseur qu'une seule fois au démarrage et observe le comportement.

## 10.2 Exemple simple

Imagine une fenêtre divisée en bandes verticales :

```text
| 1 | 2 | 3 | 4 | 5 | 6 | 7 |
```

Chaque bande donne un curseur différent.

## 10.3 API confirmées

Le `NkWindow` actuel expose `SetCursor(NkCursorType)` et les types courants comprennent notamment :

```text
Arrow
TextInput
Hand
ResizeNS
ResizeWE
ResizeNWSE
ResizeNESW
```

Le code actuel indique aussi que la forme du curseur doit être réappliquée selon le comportement du backend, avec un commentaire particulièrement important pour Windows : le système peut réimposer le curseur lors des mouvements. Pour cet exercice, respecte donc le comportement décrit par le code du kit plutôt que d'inventer une règle universelle.

Le code mère documente également la lecture de la position souris via `NkInput.MouseX()` et `NkInput.MouseY()` en coordonnées client.

## 10.4 Résolution la plus sûre

1. lire la position souris ;
2. calculer la zone ;
3. choisir le `NkCursorType` correspondant ;
4. appeler `SetCursor()` selon la stratégie nécessaire au backend ;
5. refaire le test avec une définition unique au démarrage.

## 10.5 Structure

```cpp
// Exemple conceptuel :
// int x = NkInput.MouseX();
// int y = NkInput.MouseY();
//
// si la souris est dans zone 0 → Arrow
// zone 1 → TextInput
// ...
// zone 6 → ResizeNESW
```

## 10.6 Rapport d'observation

```md
# C3-EXO6 — Les sept curseurs

## Découpage choisi
...

## Association zone → curseur
...

## Test dynamique
Le curseur change-t-il quand je passe d'une zone à l'autre ?
...

## Test avec une seule affectation au démarrage
...

## Explication
...
```

---

# C3-EXO7 — LE GLISSER QUI SORT

## 11.1 Traduction

Tu dois commencer un glisser dans la fenêtre, puis continuer à déplacer la souris **hors de la fenêtre**.

Tu fais le test :

1. sans capture souris ;
2. avec capture souris.

Puis tu expliques la différence du point de vue de la personne qui utilise le programme.

## 11.2 Exemple accessible

Imagine une barre de réglage.

Tu commences à tirer le bouton à l'intérieur, puis tu sors de la fenêtre.

Sans capture : la fenêtre peut cesser de recevoir certaines informations de mouvement selon le comportement de la plateforme.

Avec capture : l'application demande à continuer à recevoir les mouvements nécessaires au geste commencé.

## 11.3 API confirmée

`NkWindow::CaptureMouse(bool)` existe dans le code actuel.

## 11.4 Résolution la plus sûre

Ne cherche pas à inventer un getter de capture. Le header actuel n'expose pas un simple `IsMouseCaptured()` fiable correspondant à cette expérience.

Fais donc une expérience comportementale :

```text
clic/prise à l'intérieur
→ déplacement vers l'extérieur
→ journal des mouvements reçus
→ comparaison sans/avec capture
```

## 11.5 Pseudo-code d'expérience

```cpp
// Départ :
window.CaptureMouse(false);

// Tester le glisser à l'extérieur.
// Observer ce que reçoit réellement l'application.

// Deuxième test :
window.CaptureMouse(true);

// Refaire exactement le même trajet.
```

## 11.6 Rapport

Ne dis pas seulement « avec capture ça marche mieux ».

Décris :

- ce que tu fais ;
- où le curseur sort ;
- quels événements continuent d'être reçus ;
- ce qui change du point de vue utilisateur.

---

# C3-EXO8 — LE PRESSE-PAPIERS, DANS LES DEUX SENS

## 12.1 Traduction

Deux sous-expériences :

### Partie texte

```text
lire le texte du presse-papiers
→ transformer en majuscules
→ réécrire dans le presse-papiers
```

### Partie image

```text
lire l'image
→ inverser les couleurs
→ remettre l'image dans le presse-papiers
```

## 12.2 Exemple texte

Avant :

```text
Bonjour Bruno
```

Après :

```text
BONJOUR BRUNO
```

## 12.3 Point technique important

Le `NkWindow` actuel expose les opérations texte et les opérations image du presse-papiers. Pour l'image, le code actuel définit `NkClipboardImage` comme une image RGBA8, c'est-à-dire quatre composantes par pixel.

Il existe aussi plusieurs surcharges historiques de lecture image. Pour éviter l'ambiguïté, préfère l'API structurée correspondant à la version de ton kit et vérifie la déclaration locale avant de coder.

## 12.4 Inversion des couleurs

Si un pixel vaut :

```text
R G B A
```

une inversion couleur simple est conceptuellement :

```text
255-R
255-G
255-B
A inchangé
```

### Pourquoi alpha ne doit pas être inversé ?

Parce que l'exercice porte sur la couleur visible. L'alpha représente l'opacité/transparence.

## 12.5 Résolution sûre

### Texte

```cpp
NkString texte = window.GetClipboardText();

// Construire une nouvelle chaîne en majuscules
// puis la remettre :
// window.SetClipboardText(texteMajuscule);
```

### Image

```cpp
nkentseu::NkClipboardImage image;

if (window.GetClipboardImage(image) && image.IsValid())
{
    // image.pixels contient les octets RGBA8.
    // Pour chaque pixel :
    // R' = 255 - R
    // G' = 255 - G
    // B' = 255 - B
    // A' = A

    window.SetClipboardImage(image);
}
```

Le nom et les détails exacts des conteneurs doivent être alignés sur la version locale du header.

## 12.6 Ce qu'il faut mesurer

Le sujet demande une vraie observation. Dans le rapport, indique au minimum :

- texte avant ;
- texte après ;
- image avant ;
- dimensions ;
- format / nombre de composantes selon ce que l'API te donne ;
- image après ;
- cas où la lecture ou l'écriture n'a pas fonctionné.

Ne transforme pas un échec de l'OS ou du backend en faux succès.

---

# C3-EXO9 — LES QUATRE DIALOGUES

## 13.1 Traduction

Le professeur veut que tu utilises les **quatre dialogues natifs** disponibles dans le framework, puis que tu traites correctement le cas où l'utilisateur annule.

Exemple humain :

```text
Je demande une action.
L'utilisateur ouvre la boîte.
Il change d'avis.
Il clique sur Annuler.
→ le programme continue normalement.
```

## 13.2 Résolution la plus sûre

Ce point exige une lecture du header local des dialogues avant de coder, car les noms exacts des quatre API ne sont pas confirmés dans les sources consultées ici.

**N'invente pas quatre noms de fonctions.**

Cherche dans le module de fenêtre / dialogue les quatre opérations réellement exposées, note leurs signatures, puis fais pour chacune :

```text
appel
→ résultat
→ test d'annulation
→ aucune utilisation de donnée invalide
→ poursuite normale
```

## 13.3 Structure de rapport

```md
# C3-EXO9 — Les quatre dialogues

## Dialogue 1
API : ...
Résultat normal : ...
Résultat en cas d'annulation : ...

## Dialogue 2
...

## Dialogue 3
...

## Dialogue 4
...

## Test de robustesse
J'ai annulé chaque dialogue sans valider de choix.
Le programme : ...

## Conclusion
...
```

---

# C3-EXO10 — LA FENÊTRE SANS BORDURE

## 14.1 Traduction

Tu retires la décoration système et tu recrées toi-même une mini-barre de titre comprenant :

- un titre ;
- trois boutons ;
- le déplacement à la souris ;
- le double-clic pour agrandir.

Tu mesures ensuite le temps nécessaire.

## 14.2 Exemple très simple

Quand tu fais :

```text
frame = false
```

le système ne dessine plus sa barre classique pour toi.

Tu dois alors construire ta propre zone de titre.

## 14.3 API fenêtre actuellement confirmées

Le code actuel expose notamment :

```text
SetDecorated(bool)
SetTitle(...)
Minimize()
Maximize()
Restore()
IsMaximized()
BeginDragMove()
BeginResize(...)
```

## 14.4 Résolution la plus sûre

Séparer le problème en quatre morceaux :

```text
1. rendre la fenêtre sans décoration
2. dessiner / représenter la barre personnalisée
3. gérer les clics des trois boutons
4. gérer le drag et le double-clic
```

Ne mélange pas la logique de fenêtre et le dessin dans une énorme fonction.

## 14.5 Architecture pédagogique

```text
BARRE
 ├── titre
 ├── bouton réduire
 ├── bouton agrandir/restaurer
 └── bouton fermer

ZONE CLIENT
 └── contenu
```

## 14.6 Rapport

Le temps demandé doit être **mesuré**, pas inventé :

```md
Temps de réalisation : ...
Difficulté principale : ...
Fonctionnalité perdue par rapport à la barre système : ...
Fonctionnalité reconstruite : ...
```

---

# C3-EXO11 — DEUX FENÊTRES

## 15.1 Traduction

Ouvre deux fenêtres.

Quand l'utilisateur clique, affiche laquelle des deux a reçu le clic.

Puis réponds à la seconde partie :

> « Qu'est-ce qui manquerait pour dessiner correctement dans les deux ? »

Cette seconde question teste ta compréhension de l'association entre fenêtre, surface et contexte de rendu.

## 15.2 Exemple simple

```text
Fenêtre A : Éditeur
Fenêtre B : Inspecteur

clic A → message "clic reçu par A"
clic B → message "clic reçu par B"
```

## 15.3 API confirmée

`NkWindow::GetId()` existe dans le `NkWindow` actuel.

## 15.4 Point délicat

La structure exacte du champ « window id » dans le type d'événement souris doit être lue dans les headers d'événements de ton kit local avant de produire du code définitif.

## 15.5 Résolution sûre

Architecture :

```text
windowA
windowB

poll event
↓
identifier la fenêtre source
↓
comparer avec windowA.GetId()/windowB.GetId()
↓
afficher A ou B
```

## 15.6 Rapport

```md
# C3-EXO11 — Deux fenêtres

## Fenêtre A
Identifiant : ...

## Fenêtre B
Identifiant : ...

## Test
...

## Ce qu'il faut en plus pour dessiner dans les deux
...

## Conclusion
...
```

---

# C3-EXO12 — L'INVENTAIRE DES ÉCRANS

## 16.1 Traduction

Pour chaque écran connecté, tu dois afficher :

- sa taille ;
- sa position ;
- son facteur d'échelle ;
- lequel porte ta fenêtre.

Puis tu déplaces la fenêtre d'un écran à l'autre et tu regardes si les informations suivent.

## 16.2 Exemple simple

```text
Écran 0 : 1920×1080, position (0,0)
Écran 1 : 1920×1080, position (1920,0)

Fenêtre actuellement sur écran 1
```

Les valeurs exactes doivent venir de ta machine.

## 16.3 API confirmées

Le `NkWindow` actuel expose notamment :

```text
EnumerateMonitors()
GetCurrentMonitor()
GetMonitorCount()
GetDisplaySize()
GetDisplayPosition()
GetDpiScale()
```

La structure exacte des informations de moniteur doit être vérifiée dans le `NkSystemEvent` / header de moniteur de la version locale avant d'écrire le code final.

## 16.4 Résolution sûre

Construire une boucle d'inventaire :

```text
nombre de moniteurs
→ chaque moniteur
→ afficher taille + position + scale
→ identifier moniteur courant
```

Puis répéter après déplacement.

---

# 6. DÉMONSTRATIONS DU CHAPITRE 3

## C3-DEMO1 — TRENTE MILLE LIGNES POUR UNE FENÊTRE

### Ce que la démonstration veut réellement montrer

Une même API publique peut cacher énormément de travail de plateforme.

Le dépôt actuel présente une architecture en couches : applications, Engine, Runtime, System, Foundation puis OS/matériel. Le `NKWindow` appartient à Runtime, tandis que les couches inférieures absorbent la diversité des plateformes. citeturn962687view0

### Déroulé de présentation

```text
1. montrer l'arborescence
2. montrer le module NKWindow
3. montrer deux implémentations/backend
4. montrer un même appel public
5. expliquer ce qui change dessous
6. conclure : l'application reste stable, le backend absorbe la différence
```

### Conclusion type à personnaliser

> « L'intérêt de l'abstraction est de permettre au programme applicatif d'appeler une interface stable, pendant que le code spécifique à la plateforme prend en charge les détails propres à Windows, Linux, etc. »

---

## C3-DEMO2 — LE DÉFAUT INVISIBLE

### Idée

Montrer une interface correcte sur un affichage standard et incorrecte sur un affichage à forte densité.

### Test

```text
Machine A
→ affichage normal

Machine B
→ DPI élevé
→ interface trop petite / mal dimensionnée
```

### Correction

Montrer que la différence vient du choix de la source de taille, puis corriger en demandant la bonne information au bon niveau.

### À expliquer oralement

> « Une taille numérique n'a de sens qu'en fonction de ce qu'elle représente : fenêtre, surface cliente, cible de rendu, écran ou pixels physiques. »

---

## C3-DEMO3 — LA BARRE DE TITRE À SOI

Montrer :

- déplacement ;
- agrandissement ;
- boutons ;
- puis ce qui a été perdu par rapport à la décoration système.

### À ne pas oublier

La vraie compétence évaluée n'est pas uniquement « j'ai dessiné une jolie barre ».

Il faut être capable de dire :

```text
barre système
→ fonctionnalités prises en charge automatiquement

barre personnalisée
→ fonctionnalités désormais à ma charge
```

---

## C3-DEMO4 — LE MÊME PROGRAMME SUR DEUX SYSTÈMES

Faire tourner le même binaire ou la même source recompilée sur deux systèmes et noter ce qui change sans modifications spécifiques de ta part.

### Tableau recommandé

| Aspect | Système A | Système B | Commentaire |
|---|---|---|---|
| taille visuelle | ... | ... | ... |
| décoration | ... | ... | ... |
| curseur | ... | ... | ... |
| comportement fermeture | ... | ... | ... |
| DPI | ... | ... | ... |
| autre | ... | ... | ... |

---

# 7. CHAPITRE 4 — ÉVÉNEMENTS ET ENTRÉES

---

# 17. QCM — LES 12 IDÉES À MAÎTRISER

Le PDF pose notamment les notions suivantes. L'objectif ici est de les comprendre, pas seulement de mémoriser la lettre d'une réponse.

## 17.1 `NkScancode`

Il correspond à la position physique d'une touche plutôt qu'au caractère imprimé.

### Exemple

Le joueur veut se déplacer avec une disposition qui garde la même géométrie physique : le code de mouvement doit pouvoir s'appuyer sur la position.

---

## 17.2 Mouvement dans un jeu

La notion clé donnée par le cours est l'emploi du scancode lorsque l'on veut que la disposition du clavier n'altère pas la logique de déplacement.

---

## 17.3 Durée de vie du pointeur événement

Le pointeur obtenu par `PollEvent()` ne doit pas être considéré comme éternel. Le PDF insiste sur sa validité jusqu'au prochain appel de `PollEvent()`.

---

## 17.4 Retour `true` d'un gestionnaire

Dans le modèle présenté, `true` signifie que l'événement a été consommé et ne doit plus atteindre les abonnés suivants.

---

## 17.5 Modificateurs

Les modificateurs accompagnent l'événement afin de représenter leur état au moment où l'événement a eu lieu, et non un état éventuellement différent au moment où on traite plus tard l'information.

---

## 17.6 File prioritaire

Elle sert à laisser passer devant les événements qui ne doivent pas attendre, notamment certaines situations système importantes.

---

## 17.7 Mouvement brut de souris

Il est pertinent pour les usages où l'on veut mesurer le mouvement lui-même, par exemple une caméra de jeu à la première personne, plutôt que la position bornée du curseur à l'écran.

---

## 17.8 Axes de manette

Avant de lire les axes, vérifier que la manette correspondante est effectivement disponible.

---

## 17.9 Action nommée

Une action nommée est une intention ponctuelle déclenchable par plusieurs commandes.

---

## 17.10 Premier bénéfice des actions

Le bénéfice central est que le code métier ne connaît plus directement le clavier.

---

## 17.11 Ce qui varie selon l'utilisateur

Le cours pousse vers une configuration externe plutôt qu'une logique figée dans le code.

---

## 17.12 Veille / déconnexion / système

Une application qui n'écoute que le clavier et la souris peut rater des changements système importants.

---

# C4-EXO1 — LE JOURNAL DES ÉVÉNEMENTS

## 18.1 Traduction

Tu dois construire un programme qui journalise chaque événement reçu en indiquant au moins sa famille et son type.

Puis tu provoques plusieurs actions :

```text
bouger souris
appuyer touches
redimensionner fenêtre
déposer un fichier
```

Enfin, tu mesures combien d'événements une seconde d'utilisation normale peut produire.

## 18.2 Exemple simple

Tu veux savoir ce que le moteur reçoit pendant :

```text
un déplacement de souris
```

Tu observes plusieurs entrées dans le journal.

## 18.3 Architecture de base

```cpp
while (window.IsOpen())
{
    auto* event = PollEvent();

    if (!event)
        continue;

    // Identifier famille + type selon les fonctions/types réels du kit.
    // Journaliser immédiatement.
}
```

## 18.4 Résolution sûre

Ne tente pas de deviner la méthode d'énumération de famille si ton kit n'est pas exactement celui du PDF. Cherche les fonctions / enums de type d'événement dans `NKEvent`.

## 18.5 Mesure

Pour 1 seconde :

```text
compteur = 0
heure de départ = maintenant

pendant 1 seconde
    PollEvent
    compteur++

afficher compteur
```

---

# C4-EXO2 — LA LETTRE ET LA POSITION

## 19.1 Traduction

Pour chaque touche pressée, afficher deux informations :

```text
ce que la touche représente / produit
ET
sa position physique
```

Puis changer la disposition du clavier et refaire le test.

## 19.2 Exemple

Le but est de constater que :

```text
caractère / lettre
≠
position physique
```

## 19.3 Résolution sûre

Le rapport doit contenir une comparaison avant/après changement de disposition.

---

# C4-EXO3 — FERMER PROPREMENT

## 20.1 Traduction

La fenêtre doit se fermer lorsque le moteur signale une demande de fermeture.

La consigne insiste sur le fait que plusieurs façons d'arriver à cette demande doivent suivre le même chemin applicatif.

## 20.2 Code de logique

```cpp
while (window.IsOpen())
{
    auto* event = PollEvent();

    if (!event)
        continue;

    if (event->Is<nkentseu::NkWindowCloseEvent>())
    {
        window.Close();
    }
}
```

Le nom exact de `PollEvent()` et de `NkWindowCloseEvent` a été rencontré dans l'environnement de travail précédent ; conserve néanmoins la déclaration de ton kit comme vérité ultime.

## 20.3 Ce que tu dois vérifier

- clic sur X ;
- comportement via le gestionnaire de fenêtres ;
- chemin déclenché par ton mécanisme de test ;
- aucune fermeture sur un événement sans rapport.

---

# C4-EXO4 — LE POINTEUR QUI MEURT

## 21.1 Traduction

Le professeur te demande volontairement de faire une mauvaise chose pour observer le problème : conserver un pointeur d'événement puis l'utiliser après qu'un nouvel événement a été récupéré.

## 21.2 Pourquoi ?

Le pointeur de `PollEvent()` est lié à la durée de vie définie par le système d'événements.

Le PDF indique qu'il n'est pas sûr au-delà du prochain appel à `PollEvent()`.

## 21.3 Expérience

```text
PollEvent() → eventA
PollEvent() → eventB
relire eventA
```

Puis observer ce qui se passe.

## 21.4 Correction

Le sujet donne explicitement `PollEventCopy` comme piste de correction.

### Principe

```cpp
// Représentation conceptuelle
NkEventCopy copy;
if (PollEventCopy(copy))
{
    // La copie possède sa propre durée de vie.
}
```

Le type exact doit être vérifié dans le header de ton kit.

---

# C4-EXO5 — LE CLIC CONSOMMÉ

## 22.1 Traduction

Deux gestionnaires existent :

```text
Gestionnaire 1 : panneau
Gestionnaire 2 : reste de l'application
```

Si le clic tombe sur le panneau, le premier le consomme.

Le deuxième ne doit alors pas être appelé.

## 22.2 Exemple

```text
+---------------------------+
|       panneau             |
|   [ bouton ]              |
|                           |
|                           |
+---------------------------+
```

Clique dans le panneau → événement consommé.

## 22.3 Logique

```cpp
bool panelHandled = true;

if (panelHandled)
{
    return true; // l'événement s'arrête ici
}

// le second handler n'est atteint que si le premier n'a pas consommé
```

## 22.4 Vérification

Le journal doit prouver :

```text
clic panneau
→ handler 1 appelé
→ handler 2 absent
```

---

# C4-EXO6 — LES TROIS HAUTEURS, SUR LE MÊME GESTE

## 23.1 Traduction

Tu fais avancer un carré vers la droite de trois manières différentes :

1. en réagissant à des événements ;
2. en interrogeant l'état courant ;
3. avec une action nommée.

Puis tu compares ce que chaque solution sait du clavier.

## 23.2 Exemple très simple

Même intention :

```text
appuyer / maintenir → carré vers la droite
```

Mais trois niveaux d'abstraction.

## 23.3 Niveau 1 — événement

Question :

> « Est-ce qu'un événement de touche est arrivé ? »

## 23.4 Niveau 2 — état

Question :

> « La touche est-elle maintenue maintenant ? »

## 23.5 Niveau 3 — action

Question :

> « L'intention “aller à droite” est-elle active ? »

## 23.6 Conclusion attendue

Plus tu montes dans l'abstraction, plus le code métier est découplé du matériel.

---

# C4-EXO7 — LE FRONT MONTANT

## 24.1 Traduction

Tu veux qu'un personnage saute **une seule fois** lorsqu'on appuie sur espace.

### Mauvaise version

Tu fais seulement :

```text
si espace est pressée maintenant → saut
```

Le problème : si on maintient la touche, plusieurs images voient « pressée ».

### Correction

Détecter le passage :

```text
pas pressée
    ↓
pressée
```

C'est le **front montant**.

## 24.2 Formule simple

```cpp
bool risingEdge = current && !previous;
```

Puis :

```cpp
if (risingEdge)
{
    joueur.Sauter();
}
```

Et à la fin de la boucle :

```cpp
previous = current;
```

## 24.3 Comparaison événement

Un événement de pression décrit directement l'instant de pression.

Le front montant reconstruit cet instant à partir de deux états successifs.

---

# C4-EXO8 — LA MANETTE

## 25.1 Traduction

Le même carré doit être contrôlable par :

```text
clavier
OU
manette
```

mais la logique de déplacement ne doit être écrite qu'une seule fois.

Si la manette est retirée pendant le jeu :

```text
pause
```

et non :

```text
le personnage continue mystérieusement
```

## 25.2 Architecture correcte

```text
clavier ─┐
         ├──> intention de déplacement ───> logique du carré
manette ─┘
```

C'est la même idée que les actions nommées : séparer **entrée** et **règle de jeu**.

---

# C4-EXO9 — LA ZONE MORTE

## 26.1 Traduction

Tu regardes la valeur brute d'un axe de manette pendant 10 secondes sans toucher à la manette.

Tu trouves :

```text
la plus grande valeur absolue observée
```

Puis tu choisis une zone morte légèrement supérieure à cette perturbation mesurée et tu expliques pourquoi.

## 26.2 Exemple

Au repos, tu observes :

```text
0.00
0.01
-0.02
0.015
```

Si la plus grande valeur absolue est 0.02, une zone morte supérieure à 0.02 peut être étudiée.

**La valeur finale doit venir de ta mesure, pas d'un nombre copié.**

---

# C4-EXO10 — LES TOUCHES RECONFIGURABLES

## 27.1 Traduction

Les commandes doivent être écrites dans un fichier de configuration.

Au démarrage :

```text
programme
→ lit le fichier
→ charge les actions
```

L'utilisateur doit pouvoir modifier cette configuration.

Ensuite, une partie du jeu doit être jouable avec ses propres touches.

## 27.2 Exemple

Configuration :

```text
droite = D
sauter = ESPACE
```

Puis l'utilisateur change :

```text
droite = L
sauter = W
```

Le code des règles ne change pas.

## 27.3 Extrait conceptuel donné dans le cours

Le PDF présente une API d'actions nommées de la forme :

```cpp
actions.CreateAction("sauter", [&](auto…, bool appuye, bool repetition) {
    if (appuye && !repetition)
        joueur.Sauter();
});

actions.AddCommand(
    NkActionCommand("sauter", NkInputCode::Key(NkKey::NK_SPACE))
);
```

et associe également une commande de manette à la même action.

Le nom exact des types/classes doit être aligné sur le kit local.

## 27.4 Architecture à retenir

```text
FICHIER CONFIG
      ↓
BINDINGS
      ↓
ACTIONS
      ↓
RÈGLES DU JEU
```

---

# C4-EXO11 — LE GLISSER-DÉPOSER COMPLET

## 28.1 Traduction

Tu dois traiter six situations autour du glisser-déposer :

```text
entrée
survol
sortie
+
3 natures de contenu
```

Le programme doit aussi fournir un retour visuel lorsque le contenu est au-dessus de la zone acceptée.

## 28.2 Exemple

```text
je prends un fichier
→ j'entre dans la zone
→ la zone devient visuellement active
→ je bouge au-dessus
→ je quitte
```

## 28.3 Architecture

```text
DROP_ENTERED
   ↓
zone active = true

DROP_OVER
   ↓
continuer indication visuelle

DROP_LEFT
   ↓
zone active = false

DROP_CONTENT
   ↓
traiter selon type
```

Les noms précis des classes d'événement doivent être lus dans le `NKEvent` courant.

---

# C4-EXO12 — LE REJEU

## 29.1 Traduction

Pendant une minute :

```text
enregistrer toutes les actions + leur temps
```

Puis :

```text
ne toucher à aucun clavier
→ rejouer les actions enregistrées
```

La partie doit se comporter de la même façon.

## 29.2 Pourquoi c'est puissant ?

Parce que les règles du jeu ne dépendent plus directement du clavier physique.

Tu peux alors :

```text
enregistrer
→ sauvegarder
→ reproduire
→ comparer
```

## 29.3 Format simple

Conceptuellement :

```text
timestamp | action
0 ms      | gauche
120 ms    | gauche
260 ms    | saut
540 ms    | droite
```

## 29.4 Résolution la plus sûre

Commencer avec deux ou trois actions seulement.

Faire une boucle de lecture qui compare le temps écoulé au timestamp suivant.

Puis seulement agrandir le système.

---

# 8. DÉMONSTRATIONS DU CHAPITRE 4

## C4-DEMO1 — LE CHEMIN D'UNE TOUCHE

### À raconter

```text
matériel
→ système d'exploitation
→ backend de plateforme
→ NKEvent
→ PollEvent / état / action
→ code de l'application
```

Le cours explique justement que l'événement traverse la plateforme puis est traduit dans une forme commune au niveau du module.

### Exigence de présentation

Ne récite pas uniquement une liste. Montre le chemin logique et précise ce que devient l'information à chaque étage.

---

## C4-DEMO2 — LES TROIS HAUTEURS

Présenter le même geste traité par :

```text
événement
état
intention
```

Puis discuter de cas d'usage :

| Usage | Question naturelle |
|---|---|
| menu | quel événement vient d'arriver ? |
| mouvement | quelle commande est maintenue ? |
| saut | quelle intention ponctuelle ? |
| raccourci | quelle combinaison a été déclenchée ? |
| visée | quel déplacement brut a été mesuré ? |

Le but est de comprendre que plusieurs niveaux sont utiles, pas d'appliquer le même niveau partout.

---

## C4-DEMO3 — LA RECONFIGURATION EN DIRECT

Une personne change les touches pendant que le programme tourne.

Tu joues ensuite avec la nouvelle configuration.

### Ce que cela prouve

La configuration des commandes est une donnée du système d'entrée, pas une règle métier codée en dur.

---

## C4-DEMO4 — LE JEU QUI SE JOUE TOUT SEUL

Montre :

```text
1 minute enregistrée
        ↓
rejeu automatique
```

Puis explique pourquoi cette capacité devient utile pour les tests de non-régression.

---

# 9. MATRICE DE DÉCISION — QUEL NIVEAU UTILISER ?

| Besoin | Niveau naturel | Pourquoi |
|---|---|---|
| savoir qu'un clic vient d'arriver | événement | information ponctuelle |
| savoir si une touche est actuellement maintenue | état | situation présente |
| déplacer selon une commande abstraite | action | découplage matériel |
| caméra FPS | mouvement brut | le geste dépasse les bords de l'écran |
| menu | événement/action | dépend de l'intention de l'interface |
| reconfiguration | action | commandes remplaçables |
| rejeu | action | indépendant du matériel |

---

# 10. PIÈGES CRITIQUES À ÉVITER

## 10.1 Confondre `std::cout` et `NkString`

Mauvais modèle mental :

```cpp
NkString s = std::cout << ...;
```

Le flux de sortie n'est pas une chaîne `NkString`.

---

## 10.2 Appeler `Create()` sans argument lorsque le kit attend une configuration

Le code courant utilisé dans ton environnement expose une création sous forme de :

```cpp
window.Create(config);
```

ou une construction directe par configuration selon le chemin utilisé.

Ne fais pas :

```cpp
window.Create()
```

si le header réel demande `const NkWindowConfig&`.

---

## 10.3 Écrire `()` au lieu de `{}` pour un bloc

Mauvais :

```cpp
if (!window.Create())
    (...)
```

Correct :

```cpp
if (!window.Create(config))
{
    return -1;
}
```

---

## 10.4 Mettre `i = i++`

Cela ne constitue pas une incrémentation sûre.

Privilégie :

```cpp
++i;
```

---

## 10.5 Croire que `GetDisplaySize()` est la taille de ta fenêtre

Ce n'est pas la même information.

---

## 10.6 Inventer une API

Si tu n'as pas vu :

```cpp
SomeFunction()
```

dans le header réel, ne pars pas du principe qu'elle existe.

Cherche d'abord.

---

## 10.7 Garder un pointeur d'événement après un nouveau `PollEvent()`

C'est précisément la faute étudiée dans C4-EXO4.

---

## 10.8 Mettre toutes les entrées directement dans les règles du jeu

Cela rend ensuite :

- la reconfiguration plus difficile ;
- le support manette plus difficile ;
- les tests automatiques plus difficiles ;
- le rejeu plus difficile.

---

# 11. CHECKLIST UNIVERSELLE AVANT CHAQUE COMMIT

## Code

- [ ] le dossier est exactement au bon emplacement ;
- [ ] le nom des fichiers est exactement celui demandé ;
- [ ] les includes respectent la casse réelle ;
- [ ] le point d'entrée correspond au `NKMain` actuel ;
- [ ] le code compile ;
- [ ] le programme s'exécute ;
- [ ] le scénario demandé a réellement été testé ;
- [ ] aucun comportement n'est inventé ;
- [ ] les valeurs expérimentales sont mesurées.

## Rapport

- [ ] objectif ;
- [ ] notions utilisées ;
- [ ] méthode ;
- [ ] test ;
- [ ] observation ;
- [ ] difficulté ;
- [ ] correction ;
- [ ] conclusion.

## Dépôt

- [ ] dépôt public si la consigne l'exige ;
- [ ] chemin exact ;
- [ ] fichier `.cpp` exact ;
- [ ] fichier `.md` exact ;
- [ ] commit final poussé ;
- [ ] vérifier une dernière fois le contenu sur GitHub.

---

# 12. MODÈLE UNIVERSEL DE `reponse.md`

```md
# Cx-EXOx — TITRE

## 1. Objectif

Cette expérience a pour objectif de ...

## 2. Notions importantes

- Notion 1 : ...
- Notion 2 : ...
- Notion 3 : ...

## 3. Interprétation de la consigne

La consigne signifie concrètement que ...

## 4. Méthode

1. ...
2. ...
3. ...

## 5. Code / API utilisés

- ...
- ...

## 6. Tests réalisés

### Test 1
...

### Test 2
...

## 7. Observations

...

## 8. Difficultés rencontrées

...

## 9. Correction

...

## 10. Résultat final

...

## 11. Conclusion

...
```

---

# 13. TABLEAU DE DÉPÔT — CHAPITRE 3

| Exercice | Dossier exact | Fichier code | Réponse |
|---|---|---|---|
| C3-EXO1 | `ani-2053/chapitre-03/exo1-la_fenetre_nue` | `c3-exo1_main.cpp` | `c3-exo1_reponse.md` |
| C3-EXO2 | `ani-2053/chapitre-03/exo2-les_sept_droits` | `c3-exo2_main.cpp` | `c3-exo2_reponse.md` |
| C3-EXO3 | `ani-2053/chapitre-03/exo3-les_bornes` | `c3-exo3_main.cpp` | `c3-exo3_reponse.md` |
| C3-EXO4 | `ani-2053/chapitre-03/exo4-le_facteur_d_echelle` | `c3-exo4_main.cpp` | `c3-exo4_reponse.md` |
| C3-EXO5 | `ani-2053/chapitre-03/exo5-le_titre_qui_informe` | `c3-exo5_main.cpp` | `c3-exo5_reponse.md` |
| C3-EXO6 | `ani-2053/chapitre-03/exo6-les_sept_curseurs` | `c3-exo6_main.cpp` | `c3-exo6_reponse.md` |
| C3-EXO7 | `ani-2053/chapitre-03/exo7-le_glisser_qui_sort` | `c3-exo7_main.cpp` | `c3-exo7_reponse.md` |
| C3-EXO8 | `ani-2053/chapitre-03/exo8-le_presse_papiers_dans_les_deux_sens` | `c3-exo8_main.cpp` | `c3-exo8_reponse.md` |
| C3-EXO9 | `ani-2053/chapitre-03/exo9-les_quatre_dialogues` | `c3-exo9_main.cpp` | `c3-exo9_reponse.md` |
| C3-EXO10 | `ani-2053/chapitre-03/exo10-la_fenetre_sans_bordure` | `c3-exo10_main.cpp` | `c3-exo10_reponse.md` |
| C3-EXO11 | `ani-2053/chapitre-03/exo11-deux_fenetres` | `c3-exo11_main.cpp` | `c3-exo11_reponse.md` |
| C3-EXO12 | `ani-2053/chapitre-03/exo12-l_inventaire_des_ecrans` | `c3-exo12_main.cpp` | `c3-exo12_reponse.md` |

Ces chemins et noms proviennent du PDF Sprint 3.1 fourni. 

---

# 14. TABLEAU DE DÉPÔT — DÉMONSTRATIONS CHAPITRE 3

| Démo | Dossier | Fichier |
|---|---|---|
| C3-DEMO1 | `ani-2053/chapitre-03/demo1-trente_mille_lignes_pour_une_fenetre` | `c3-demo1_reponse.md` |
| C3-DEMO2 | `ani-2053/chapitre-03/demo2-le_defaut_invisible` | `c3-demo2_reponse.md` |
| C3-DEMO3 | `ani-2053/chapitre-03/demo3-la_barre_de_titre_a_soi` | `c3-demo3_reponse.md` |
| C3-DEMO4 | `ani-2053/chapitre-03/demo4-le_meme_programme_sur_deux_systemes` | `c3-demo4_reponse.md` |

---

# 15. TABLEAU DE DÉPÔT — CHAPITRE 4

| Exercice | Dossier exact | Fichier code | Réponse |
|---|---|---|---|
| C4-EXO1 | `ani-2053/chapitre-03/exo1-le_journal_des_evenements` | `c4-exo1_main.cpp` | `c4-exo1_reponse.md` |
| C4-EXO2 | `ani-2053/chapitre-03/exo2-la_lettre_et_la_position` | `c4-exo2_main.cpp` | `c4-exo2_reponse.md` |
| C4-EXO3 | `ani-2053/chapitre-03/exo3-fermer_proprement` | `c4-exo3_main.cpp` | `c4-exo3_reponse.md` |
| C4-EXO4 | `ani-2053/chapitre-03/exo4-le_pointeur_qui_meurt` | `c4-exo4_main.cpp` | `c4-exo4_reponse.md` |
| C4-EXO5 | `ani-2053/chapitre-03/exo5-le_clic_consomme` | `c4-exo5_main.cpp` | `c4-exo5_reponse.md` |
| C4-EXO6 | `ani-2053/chapitre-03/exo6-les_trois_hauteurs_sur_le_meme_geste` | `c4-exo6_main.cpp` | `c4-exo6_reponse.md` |
| C4-EXO7 | `ani-2053/chapitre-03/exo7-le_front_montant` | `c4-exo7_main.cpp` | `c4-exo7_reponse.md` |
| C4-EXO8 | `ani-2053/chapitre-03/exo8-la_manette` | `c4-exo8_main.cpp` | `c4-exo8_reponse.md` |
| C4-EXO9 | `ani-2053/chapitre-03/exo9-la_zone_morte` | `c4-exo9_main.cpp` | `c4-exo9_reponse.md` |
| C4-EXO10 | `ani-2053/chapitre-03/exo10-les_touches_reconfigurables` | `c4-exo10_main.cpp` | `c4-exo10_reponse.md` |
| C4-EXO11 | `ani-2053/chapitre-03/exo11-le_glisser_deposer_complet` | `c4-exo11_main.cpp` | `c4-exo11_reponse.md` |
| C4-EXO12 | `ani-2053/chapitre-03/exo12-le_rejeu` | `c4-exo12_main.cpp` | `c4-exo12_reponse.md` |

---

# 16. TABLEAU DE DÉPÔT — DÉMONSTRATIONS CHAPITRE 4

| Démo | Dossier | Fichier |
|---|---|---|
| C4-DEMO1 | `ani-2053/chapitre-03/demo1-le_chemin_d_une_touche` | `c4-demo1_reponse.md` |
| C4-DEMO2 | `ani-2053/chapitre-03/demo2-les_trois_hauteurs` | `c4-demo2_reponse.md` |
| C4-DEMO3 | `ani-2053/chapitre-03/demo3-la_reconfiguration_en_direct` | `c4-demo3_reponse.md` |
| C4-DEMO4 | `ani-2053/chapitre-03/demo4-le_jeu_qui_se_joue_tout_seul` | `c4-demo4_reponse.md` |

---

# 17. PROCÉDURE DE TRAVAIL « ZÉRO CONFUSION »

Pour chaque exercice :

```text
ÉTAPE 1 — lire le titre
ÉTAPE 2 — reformuler avec ses propres mots
ÉTAPE 3 — identifier les mots techniques
ÉTAPE 4 — ouvrir le header réel
ÉTAPE 5 — relever l'API exacte
ÉTAPE 6 — faire le squelette minimal
ÉTAPE 7 — compiler
ÉTAPE 8 — ajouter UNE fonctionnalité
ÉTAPE 9 — tester
ÉTAPE 10 — mesurer
ÉTAPE 11 — rédiger
ÉTAPE 12 — commit
```

### Règle « une variable, une raison »

Quand tu ajoutes une variable, sois capable de dire en une phrase pourquoi elle existe.

### Règle « une API, une preuve »

Quand tu cites une fonction, sois capable de montrer où tu l'as trouvée et quel test démontre son effet.

### Règle « une conclusion, une observation »

Chaque conclusion doit reposer sur un test réel.

---

# 18. CE QUI EST DÉJÀ VÉRIFIÉ DANS LE `NkWindow` ACTUEL

Les capacités suivantes sont confirmées comme faisant partie de l'interface actuelle observée dans le code mère :

```text
NkWindow()
NkWindow(const NkWindowConfig&)
Create(const NkWindowConfig&)
Close()
IsOpen()
IsValid()
GetId()
GetTitle()
SetTitle()
GetSize()
GetPosition()
GetDpiScale()
GetDisplaySize()
GetDisplayPosition()
EnumerateMonitors()
GetCurrentMonitor()
GetMonitorCount()
SetSize()
SetPosition()
SetVisible()
Minimize()
Maximize()
Restore()
IsMaximized()
IsMinimized()
BeginDragMove()
SetClipboardText()
GetClipboardText()
GetClipboardImage(...)
SetClipboardImage(...)
HasClipboardImage()
BeginResize(...)
SetFullscreen()
SetDecorated()
IsDecorated()
SetOpacity()
GetOpacity()
SetAlwaysOnTop()
IsAlwaysOnTop()
SetClickThrough()
IsClickThrough()
SetBackgroundColor()
GetBackgroundColor()
SetMousePosition()
SetMousePositionClient()
ShowMouse()
CaptureMouse()
SetCursor()
ClipMouseToClient()
GetSurfaceDesc()
```

La liste est donnée comme **repère de travail**, pas comme invitation à utiliser toutes les API. Les signatures exactes doivent être vérifiées dans ton checkout local.

---

# 19. CE QU'IL FAUT VÉRIFIER LOCALEMENT AVANT DE CODER

Pour éviter toute invention, fais une recherche locale dans ton kit pour ces thèmes :

```text
NkSurfaceDesc
NkDisplayInfo
PollEventCopy
NkMouse...
NkKeyboard...
NkGamepad...
NkDrop...
NkDialog...
NkAction...
```

Cette recherche locale est particulièrement importante pour C3-EXO4, C3-EXO9, C3-EXO11 et plusieurs exercices du chapitre 4 où les noms détaillés des structures d'événements ne sont pas tous visibles dans les extraits consultés.

---

# 20. NIVEAU DE QUALITÉ ATTENDU

Un rendu solide du Sprint ne doit pas ressembler à :

```text
ça compile
voilà mon code
```

Il doit ressembler à :

```text
j'ai compris la demande
↓
j'ai identifié l'objet technique
↓
j'ai trouvé l'API réelle
↓
j'ai réalisé l'expérience
↓
j'ai observé un résultat
↓
j'ai relié le résultat à la notion
↓
j'ai rédigé ma conclusion
```

C'est cette chaîne qui transforme un exercice exécuté en exercice **compris**.

---

# 21. SOURCES ET NIVEAU DE CONFIANCE

## Source A — RIHEN Academy Sprint 3.1

**Confiance : très élevée pour les consignes, les noms de dépôts, les noms de fichiers et les objectifs pédagogiques**, car le PDF fourni a été directement lu.

## Source B — dépôt public Nkentseu actuel

**Confiance : élevée pour les éléments directement observés dans le dépôt actuel**, notamment son architecture générale, Jenga, les modules, la nature active du projet et les informations visibles sur `NKWindow`. Le README lui-même avertit que certains documents d'architecture peuvent diverger du dépôt réel ; cette réserve a donc été appliquée. citeturn962687view0

## Source C — dépôts de camarades

**Confiance : non établie dans cette session**. Leur code n'a pas été récupéré de façon fiable. Aucune recommandation de code n'est attribuée à ces dépôts dans ce guide.

---

# 22. CONCLUSION DE TRAVAIL

La vraie difficulté du Sprint 3 n'est pas seulement de connaître `NkWindow`, `PollEvent()` ou quelques noms de classes.

Le cœur du Sprint est de comprendre trois changements de perspective :

```text
1. gérer une fenêtre
2. comprendre ce qu'elle reçoit
3. découpler ce que reçoit le programme de ce que le jeu veut faire
```

C'est pour cela que les exercices vont volontairement du très simple au plus abstrait :

```text
fenêtre
→ capacités
→ géométrie
→ DPI
→ titre
→ curseur
→ capture
→ presse-papiers
→ dialogues
→ décoration
→ multi-fenêtres
→ multi-écrans

puis

événements
→ états
→ consommation
→ durée de vie mémoire
→ trois hauteurs
→ front montant
→ manette
→ zone morte
→ reconfiguration
→ drop
→ rejeu
```

La meilleure manière de réussir est donc de **ne jamais traiter un exercice comme une phrase à recopier**, mais comme une petite expérience scientifique :

```text
hypothèse
→ implémentation minimale
→ test
→ observation
→ explication
→ conclusion
```

---

# 23. DERNIÈRE LISTE — AVANT DE DIRE « EXERCICE TERMINÉ »

```text
[ ] Je peux expliquer l'énoncé sans le relire.
[ ] Je peux expliquer chaque mot important de l'énoncé.
[ ] Je sais pourquoi chaque partie du code existe.
[ ] Je connais l'API exacte utilisée.
[ ] J'ai testé le comportement réel.
[ ] J'ai noté les mesures réellement obtenues.
[ ] Mon rapport distingue observation et interprétation.
[ ] Mon dépôt utilise exactement les noms demandés.
[ ] Mon code final compile encore après nettoyage.
[ ] Je peux expliquer l'exercice à quelqu'un sans montrer le code.
```

---

## FIN — VERSION ULTRA DE TRAVAIL

Ce document constitue une base de travail approfondie. Pour les API dont la signature complète n'a pas été confirmée dans les sources accessibles, il préfère volontairement une zone « à vérifier dans le kit » plutôt qu'un faux code présenté comme certain.
