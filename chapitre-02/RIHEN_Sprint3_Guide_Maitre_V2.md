# RIHEN ACADEMY — SPRINT 3
## Guide maître V2 — comprendre l’énoncé, retrouver l’API, coder, tester, rédiger

> **But de ce document**
>
> Transformer les énoncés volontairement courts du Sprint 3 en consignes concrètes, compréhensibles et exécutables, puis fournir des **modèles de code pédagogiques commentés** et des méthodes de vérification.
>
> Le document suit deux sources de vérité :
>
> 1. le sujet RIHEN Academy du Sprint 3 ;
> 2. le **code réel actuel** de `Nkentseu` quand celui-ci a pu être vérifié.
>
> Il ne faut jamais remplacer une définition actuelle du code mère par une ancienne documentation.
>
> **Important :** les valeurs expérimentales (DPI, tailles réelles, nombre d’événements, bruit d’un axe, etc.) doivent venir de la machine et des essais de l’étudiant. Les exemples numériques de ce guide sont pédagogiques et ne constituent pas les résultats à déposer.

---

# 1. VISION D’ENSEMBLE DU SPRINT

Le Sprint 3 rassemble deux thèmes :

```text
CHAPITRE 3
Fenêtre
    ↓
configuration
    ↓
géométrie
    ↓
curseur / presse-papiers / dialogues
    ↓
fenêtres multiples / écrans
```

puis :

```text
CHAPITRE 4
Événements
    ↓
file d'événements
    ↓
état courant
    ↓
intentions / actions
    ↓
clavier / souris / manette / drop
    ↓
reconfiguration / rejeu
```

L’idée pédagogique globale est simple :

> **une fenêtre est la frontière entre ton programme et le système ; les événements sont ce qui traverse cette frontière.**

---

# 2. RÈGLE ABSOLUE : LE CODE MÈRE PRIME SUR LA DOC

La version actuelle de `NkWindow.h` expose notamment :

```cpp
NkWindow();
explicit NkWindow(const NkWindowConfig& config);

bool Create(const NkWindowConfig& config);
void Close();
bool IsOpen() const;
bool IsValid() const;

NkWindowId GetId() const;

NkString GetTitle() const;
void SetTitle(const NkString& title);

math::NkVec2u GetSize() const;
math::NkVec2u GetPosition() const;

float32 GetDpiScale() const;

math::NkVec2u GetDisplaySize() const;
math::NkVec2u GetDisplayPosition() const;

NkError GetLastError() const;
NkWindowConfig GetConfig() const;

NkVector<NkDisplayInfo> EnumerateMonitors() const;
NkDisplayInfo GetCurrentMonitor() const;
uint32 GetMonitorCount() const;
```

Le header actuel précise aussi que :

- `GetSize()` est la **taille de la zone client**, sans barre de titre ni bordure ;
- la position renvoyée par `GetPosition()` désigne le coin haut-gauche de la **fenêtre complète** ;
- `GetSize()` interroge le système et ne relit pas simplement la configuration ;
- `Create()` demande explicitement une `NkWindowConfig`.

Ne pas réutiliser mentalement une ancienne API du type :

```cpp
window.Create();
```

lorsque le kit courant impose :

```cpp
window.Create(config);
```

---

# 3. LE CONTRAT DE TAILLE : LE POINT QUI FAISAIT CONFONDRE `GetSize` / DISPLAY / RENDU

La version actuelle de `NkWindowConfig.h` est beaucoup plus explicite que les anciens supports.

Elle indique que :

```text
width / height
minWidth / minHeight
maxWidth / maxHeight
NkWindow::GetSize()
NkWindow::SetSize()
```

parlent tous de la **ZONE CLIENT**.

Le header précise également que cette taille correspond à la surface sur laquelle le rendu est peint et à la taille de la swapchain dans le contrat actuel de `NkWindow`.

Donc, dans la version actuelle :

```text
GetSize()
    ↓
zone client
    ↓
surface dessinable
    ↓
dimension de rendu associée à la fenêtre
```

À côté :

```text
GetDisplaySize()
    ↓
taille du moniteur / display courant
```

Et :

```text
GetDpiScale()
    ↓
facteur d’échelle lié au display courant
```

### Conclusion pour `c3-exo4`

Le code de référence donné par un camarade :

```cpp
auto size = window.GetSize();
auto displaySize = window.GetDisplaySize();
float32 scale = window.GetDpiScale();

logger.Info(
    "Window: {}x{} | Display: {}x{} | DPI Scale: {}",
    size.x, size.y,
    displaySize.x, displaySize.y,
    scale
);
```

est cohérent avec les trois informations publiques actuellement exposées.

Il ne faut cependant pas appeler `displaySize` « render target » : dans l’API courante, **Display = moniteur**.

Le vrai enseignement de `c3-exo4` devient donc :

```text
TAILLE DE MA ZONE CLIENT
        ≠
TAILLE DU MONITEUR
        +
FACTEUR DPI
```

---

# 4. SQUELETTE COMMUN À TOUS LES EXERCICES

Version de base :

```cpp
#include "NKWindow/NKWindow.h"
#include "NKWindow/NKMain.h"

using namespace nkentseu;

int nkmain(const NkEntryState& state)
{
    // Cette variable peut ne pas être utilisée dans certains exercices.
    (void)state;

    NkWindowConfig config;

    config.title = "Sprint 3";
    config.width = 900;
    config.height = 600;

    NkWindow window(config);

    if (!window.IsOpen())
    {
        logger.Error("[app] Impossible de creer la fenetre");
        return -1;
    }

    while (window.IsOpen())
    {
        // Les événements seront traités ici dans les exercices du chapitre 4.
    }

    return 0;
}
```

## Pourquoi cette structure ?

```text
NkWindowConfig
       ↓
NkWindow
       ↓
IsOpen()
       ↓
boucle
       ↓
fermeture
       ↓
return
```

---

# 5. SÉRIE 1 — QCM NKWINDOW

## Réponses de référence

1. `nkmain`
2. point d’entrée manquant / en-tête oublié
3. empêcher une réduction excessive de la fenêtre
4. synchroniser le rendu avec le balayage / réduire le tearing
5. dessiner soi-même la barre et ses boutons
6. la cible de rendu connaît les pixels réels
7. à chaque image
8. continuer à recevoir les mouvements pendant le glisser hors fenêtre
9. pixels bruts
10. éviter de bloquer le rendu
11. backend `Noop` : exécution sans affichage
12. sur plateforme sans curseur, ne rien faire pour garder le même code applicatif

---

# 6. C3-EXO1 — LA FENÊTRE NUE

## Énoncé traduit en langage simple

> Crée une fenêtre. Vérifie qu’elle a réellement été créée. Laisse-la ouverte tant que l’utilisateur ne la ferme pas. Lorsque la fenêtre disparaît, le programme doit terminer proprement.

## Ce que l'enseignant veut vérifier

Tu dois savoir faire seulement quatre choses :

```text
1. configurer
2. créer
3. vérifier
4. maintenir la vie de la fenêtre
```

## Code de référence

```cpp
#include "NKWindow/NKWindow.h"
#include "NKWindow/NKMain.h"

using namespace nkentseu;

int nkmain(const NkEntryState& state)
{
    (void)state;

    // ------------------------------------------------------------
    // 1. Définition de la configuration initiale de la fenêtre.
    // ------------------------------------------------------------
    NkWindowConfig config;

    config.title = "C3 - Fenetre nue";
    config.width = 900;
    config.height = 600;

    // ------------------------------------------------------------
    // 2. La construction crée directement la fenêtre avec
    //    la configuration fournie.
    // ------------------------------------------------------------
    NkWindow window(config);

    // ------------------------------------------------------------
    // 3. Une création peut échouer.
    //    On ne doit pas continuer à travailler sur une fenêtre
    //    qui n'est pas correctement ouverte.
    // ------------------------------------------------------------
    if (!window.IsOpen())
    {
        logger.Error("[c3-exo1] Echec de creation de la fenetre");
        return -1;
    }

    // ------------------------------------------------------------
    // 4. La boucle représente la vie de l'application.
    //    Tant que la fenêtre est ouverte, on reste vivant.
    // ------------------------------------------------------------
    while (window.IsOpen())
    {
        // Aucun traitement particulier n'est nécessaire
        // pour la première expérience.
    }

    return 0;
}
```

## Ce qu'il faut observer

- la fenêtre est réellement visible ;
- le programme reste actif ;
- fermer la fenêtre permet au programme de quitter.

## Rapport `.md`

```md
# C3-EXO1 — La fenêtre nue

## Objectif
Créer la plus petite application qui ouvre une fenêtre et la maintient
ouverte jusqu'à sa fermeture.

## API utilisées
- NkWindowConfig
- NkWindow
- IsOpen()

## Expérience
...

## Résultat
...

## Ce que j'ai compris
...

## Difficulté rencontrée
...

## Correction
...
```

---

# 7. C3-EXO2 — LES SEPT DROITS

## Traduction simple

> Crée sept fenêtres de test. Pour chaque fenêtre, désactive un seul droit/comportement de la fenêtre. Essaie ensuite l’action correspondante avec la souris ou le gestionnaire de fenêtres et note ce que l’utilisateur n’est plus capable de faire.

## Méthode correcte

Ne devine pas les sept champs.

Ouvre :

```text
NkWindowConfig.h
```

et repère les propriétés de comportement.

La démonstration doit être expérimentale :

```text
config différent
    ↓
même action utilisateur
    ↓
observation différente
```

## Structure

```cpp
NkWindowConfig config;

config.title = "Test droit X";
config.width = 700;
config.height = 450;

// UN SEUL droit doit être modifié ici.
// Exemple :
// config.resizable = false;

NkWindow window(config);

if (!window.IsOpen())
{
    logger.Error("Creation impossible");
    return -1;
}

while (window.IsOpen())
{
}
```

## Tableau de rapport

```md
| Test | Champ modifié | Manipulation | Observation |
|------|---------------|--------------|-------------|
| 1    | ...           | ...          | ...         |
| 2    | ...           | ...          | ...         |
...
```

## Point important du code mère actuel

Le `NkWindowConfig.h` indique que tous les réglages ne sont pas nécessairement supportés de façon identique par tous les backends.

La version actuelle possède même une logique d'audit/refus nommé pour certains réglages non honorés par le backend.

Conclusion :

> **si une option ne produit rien, ne condamne pas immédiatement ton code : vérifie le contrat du backend et le journal.**

---

# 8. C3-EXO3 — LES BORNES

## Traduction simple

> Force une taille minimale. Essaie de rendre la fenêtre plus petite que cette limite. Note la plus petite taille réellement acceptée. Ensuite enlève les limites et recommence.

## Code de référence

```cpp
#include "NKWindow/NKWindow.h"
#include "NKWindow/NKMain.h"

using namespace nkentseu;

int nkmain(const NkEntryState& state)
{
    (void)state;

    NkWindowConfig config;

    config.title = "C3 - Bornes";
    config.width = 800;
    config.height = 600;

    config.resizable = true;

    // ------------------------------------------------------------
    // Taille minimale demandée.
    // Le cadre reste géré par le système ; on parle de la
    // zone client conformément au contrat actuel.
    // ------------------------------------------------------------
    config.minWidth = 400;
    config.minHeight = 300;

    NkWindow window(config);

    if (!window.IsOpen())
    {
        logger.Error("[c3-exo3] Echec creation");
        return -1;
    }

    while (window.IsOpen())
    {
        // Redimensionner manuellement pour l'expérimentation.
    }

    return 0;
}
```

## Ce que tu dois noter

Supposons que tu aies demandé :

```text
minWidth  = 400
minHeight = 300
```

Tu notes ce que le système accepte réellement.

Ne rédige pas :

> « La taille finale est 400x300 »

avant de l'avoir réellement mesurée.

---

# 9. C3-EXO4 — LE FACTEUR D'ÉCHELLE

## Traduction simple

> Affiche trois choses ensemble :
>
> 1. la taille de la zone client de ta fenêtre ;
> 2. la taille de l'écran/moniteur associé ;
> 3. le facteur DPI.
>
> Ensuite change la mise à l'échelle de Windows et observe ce qui suit la configuration d'affichage.

## Code de référence

```cpp
#include "NKWindow/NKWindow.h"
#include "NKWindow/NKMain.h"

using namespace nkentseu;

int nkmain(const NkEntryState& state)
{
    (void)state;

    NkWindowConfig config;

    config.title = "C3 - Facteur d'echelle";
    config.width = 900;
    config.height = 600;

    NkWindow window(config);

    if (!window.IsOpen())
    {
        logger.Error("[c3-exo4] Echec creation");
        return -1;
    }

    // ------------------------------------------------------------
    // GetSize() :
    // taille de la zone CLIENT de la fenêtre.
    // ------------------------------------------------------------
    auto size = window.GetSize();

    // ------------------------------------------------------------
    // GetDisplaySize() :
    // taille du DISPLAY / MONITEUR courant.
    // Ce n'est pas "la taille de la fenêtre".
    // ------------------------------------------------------------
    auto displaySize = window.GetDisplaySize();

    // ------------------------------------------------------------
    // GetDpiScale() :
    // facteur d'échelle utilisé dans le contexte d'affichage courant.
    // ------------------------------------------------------------
    float32 scale = window.GetDpiScale();

    logger.Info(
        "Window: {}x{} | Display: {}x{} | DPI Scale: {}",
        size.x,
        size.y,
        displaySize.x,
        displaySize.y,
        scale
    );

    while (window.IsOpen())
    {
        // Ici il n'est pas nécessaire de réafficher à chaque image
        // si l'objectif est une simple mesure de départ.
    }

    return 0;
}
```

## Expérience recommandée

### Mesure A

Relever le réglage Windows.

### Mesure B

Lancer l'application.

### Mesure C

Noter :

```text
Window
Display
DPI
```

### Mesure D

Modifier la mise à l'échelle Windows.

### Mesure E

Relancer.

### Tableau

```md
| Réglage système | Window | Display | DPI |
|-----------------|--------|---------|-----|
| ...             | ...    | ...     | ... |
| ...             | ...    | ...     | ... |
```

## Conclusion

Le point à expliquer est :

```text
une fenêtre possède une taille propre ;
un écran possède une taille propre ;
le facteur DPI relie le monde logique à l'affichage dense.
```

---

# 10. C3-EXO5 — LE TITRE QUI INFORME

## Traduction simple

> Le titre doit toujours raconter l'état courant du programme :
>
> `NomDuDocument * [largeur x hauteur]`
>
> L'astérisque apparaît lorsque le document est modifié. Le titre ne doit être recalculé que lorsqu'une donnée qui le compose change.

## États

```cpp
NkString documentName = "document.txt";
bool modified = false;
```

## Fonction de mise à jour du titre

On sépare la logique :

```cpp
auto updateTitle = [&]()
{
    auto size = window.GetSize();

    const char* mark = modified ? " *" : "";

    char buffer[256];

    std::snprintf(
        buffer,
        sizeof(buffer),
        "%s%s [%u x %u]",
        documentName.c_str(),
        mark,
        size.x,
        size.y
    );

    window.SetTitle(NkString(buffer));
};
```

> Si la conversion `NkString` / `c_str()` diffère dans ton kit, vérifie son header avant de modifier cette partie.

## Appels à faire seulement lorsque nécessaire

```text
au démarrage
resize
document modifié
document sauvegardé
```

## Erreur à éviter

```cpp
config.title = ...
```

après la création.

La configuration initiale n'est pas le mécanisme de modification runtime.

Il faut :

```cpp
window.SetTitle(...);
```

---

# 11. C3-EXO6 — LES SEPT CURSEURS

## Traduction simple

> Découpe la zone client en sept régions. À chaque image, regarde où se trouve la souris et impose le curseur associé à cette région. Fais ensuite une deuxième expérience où tu n'imposes le curseur qu'une fois au démarrage.

## API actuelle

Le code mère expose :

```cpp
enum class NkCursorType
{
    Arrow,
    TextInput,
    Hand,
    ResizeNS,
    ResizeWE,
    ResizeNWSE,
    ResizeNESW
};

void SetCursor(NkCursorType cursor);
```

La version actuelle précise que le curseur doit être **réimposé régulièrement**, et que le comportement est réellement implémenté sur Win32 actuellement.

## Modèle de découpage

```text
+----------------+----------------+----------------+
|       1        |       2        |       3        |
+----------------+----------------+----------------+
|       4        |       5        |       6        |
+----------------+----------------+----------------+
|                7                               |
+------------------------------------------------+
```

## Algorithme

```text
x, y = position souris
width, height = taille fenêtre

col = x / (width / 3)
ligne = ...

zone = ...
curseur = ...

window.SetCursor(curseur);
```

## Point pédagogique

La partie importante n'est pas le calcul exact de la grille.

C'est :

```text
position souris
    ↓
classification en zone
    ↓
choix d'un curseur
```

---

# 12. C3-EXO7 — LE GLISSER QUI SORT

## Traduction simple

> Fais un glisser depuis la fenêtre jusqu'à l'extérieur. Fais-le d'abord sans capture, puis avec capture. Observe les événements reçus dans les deux cas.

## API actuelle

```cpp
window.CaptureMouse(true);
window.CaptureMouse(false);
```

## Séquence

```text
mousedown
   ↓
capture = false
   ↓
déplacement hors fenêtre
   ↓
journal

capture = true
   ↓
déplacement hors fenêtre
   ↓
journal
```

## Important

Dans le code mère actuel, le champ d'état `captured` n'est pas alimenté partout de manière cohérente. Il ne faut donc pas supposer qu'un getter absent peut confirmer l'état.

L'expérimentation doit porter sur **les événements effectivement reçus**.

---

# 13. C3-EXO8 — LE PRESSE-PAPIERS DANS LES DEUX SENS

## Traduction simple

### Texte

```text
lire le texte système
    ↓
convertir en majuscules
    ↓
réécrire
```

### Image

```text
lire RGBA8
    ↓
R = 255-R
G = 255-G
B = 255-B
A = A
    ↓
réécrire
```

## API actuelle du code mère

```cpp
void SetClipboardText(const NkString& text);
NkString GetClipboardText() const;

bool SetClipboardImage(const NkClipboardImage& image);
bool GetClipboardImage(NkClipboardImage& out) const;
bool HasClipboardImage() const;
```

`NkClipboardImage` est actuellement décrit comme :

```cpp
struct NkClipboardImage
{
    uint32 width;
    uint32 height;
    NkVector<uint8> pixels; // RGBA8
};
```

## Code de référence — texte

```cpp
NkString text = window.GetClipboardText();

logger.Info("Texte recupere : {}", text);

// Ici, utiliser une conversion compatible avec NkString
// de la version de ton kit pour produire la chaîne en majuscules.

window.SetClipboardText(texteMajuscule);
```

## Code de référence — image

```cpp
NkClipboardImage image;

if (window.GetClipboardImage(image))
{
    for (uint32 y = 0; y < image.height; ++y)
    {
        for (uint32 x = 0; x < image.width; ++x)
        {
            const usize index =
                (static_cast<usize>(y) * image.width + x) * 4u;

            // RGBA8 :
            image.pixels[index + 0] =
                static_cast<uint8>(255u - image.pixels[index + 0]);

            image.pixels[index + 1] =
                static_cast<uint8>(255u - image.pixels[index + 1]);

            image.pixels[index + 2] =
                static_cast<uint8>(255u - image.pixels[index + 2]);

            // Alpha : volontairement inchangé.
        }
    }

    window.SetClipboardImage(image);
}
```

## Important

Sur Windows, le code mère actuel prend en charge des formats DIB du presse-papiers ; il précise également que du PNG seul peut ne pas être lu.

Donc si ton test avec une image fonctionne pour une capture ou une image de navigateur mais pas pour un autre logiciel :

> rapporte l'observation au lieu de cacher la limitation.

---

# 14. C3-EXO9 — LES QUATRE DIALOGUES

## Traduction simple

> Utilise les quatre dialogues fournis par NKWindow. Pour chacun, traite le résultat « l'utilisateur a annulé / fermé la boîte » comme un cas normal.

## Méthode

Avant d'écrire le programme :

```text
Ctrl+Shift+F

dialog
async
message
file
folder
```

Puis lire directement les déclarations du header.

## Règle générale

Ne jamais écrire :

```cpp
auto path = ...
// utiliser path directement
```

sans vérifier :

```text
succès ?
annulation ?
fermeture ?
```

Le rapport doit montrer les deux chemins.

---

# 15. C3-EXO10 — LA FENÊTRE SANS BORDURE

## Traduction simple

> Retire la décoration système. Ensuite recrée dans ton application la sensation d'une fenêtre normale :
>
> - titre ;
> - réduire ;
> - maximiser ;
> - fermer ;
> - déplacement ;
> - double-clic.

## API actuelles utiles

Le code mère expose notamment :

```cpp
SetVisible(bool);

Minimize();
Maximize();
Restore();

IsMaximized();
IsMinimized();

BeginDragMove();

SetFullscreen(bool);

SetTitle(...);
```

et un système de redimensionnement natif :

```cpp
BeginResize(NkResizeEdge edge);
```

## Attention

Ne pas implémenter immédiatement toute la logique native à la main si `BeginDragMove()` et `BeginResize()` existent.

Le but est justement d'utiliser la façade NKWindow.

## Architecture

```text
zone titre
 ├── texte
 ├── bouton minimize
 ├── bouton maximize / restore
 └── bouton close
```

### Clic

```text
si bouton fermer
    Close()

sinon si bouton réduire
    Minimize()

sinon si bouton maximiser
    Maximize()

sinon si zone titre
    BeginDragMove()
```

### Double-clic

```text
si double clic dans la zone titre
    si IsMaximized()
        Restore()
    sinon
        Maximize()
```

---

# 16. C3-EXO11 — DEUX FENÊTRES

## Traduction simple

> Crée deux fenêtres. Lorsqu'un clic arrive, indique laquelle des deux est concernée. Ensuite explique pourquoi recevoir l'événement ne signifie pas encore que ton programme sait automatiquement dessiner dans les deux.

## API actuellement utile

Chaque fenêtre possède :

```cpp
NkWindowId GetId() const;
```

Donc un identifiant permet de distinguer les instances.

## Architecture

```text
windowA.GetId()
windowB.GetId()

événement
   ↓
ID fenêtre concernée
   ↓
A ou B
```

Le détail des événements qui portent l'ID dépend du header événementiel actuel.

Avant d'écrire le test final :

```text
rechercher :
NkWindowId
GetWindowId
window id
MouseButton
```

---

# 17. C3-EXO12 — L'INVENTAIRE DES ÉCRANS

## Traduction simple

> Pour chaque écran branché, affiche :
>
> - taille ;
> - position ;
> - échelle ;
> - information permettant de savoir s'il est primaire ou courant.
>
> Déplace ensuite la fenêtre et vérifie que le moniteur courant change.

## API actuelle

```cpp
window.EnumerateMonitors();
window.GetCurrentMonitor();
window.GetMonitorCount();
```

Le code mère précise que `EnumerateMonitors()` recalcule la liste et que le premier moniteur n'est pas nécessairement le primaire.

## Algorithme

```cpp
auto displays = window.EnumerateMonitors();

for (const auto& display : displays)
{
    // Lire ici les champs réels de NkDisplayInfo
    // après avoir ouvert son header.
}
```

Ne jamais inventer les champs de `NkDisplayInfo`.

Faire :

```text
Ctrl+Shift+F
struct NkDisplayInfo
```

puis adapter le code.

---

# 18. DÉMONSTRATIONS C3

## DEMO 1 — TRENTE MILLE LIGNES POUR UNE FENÊTRE

### Traduction

> Montre que quelques appels de haut niveau cachent une grande quantité de code spécifique aux plateformes.

### Démo

```text
NkWindow
   ↓
Core
   ↓
Platform/Win32
Platform/X11
Platform/macOS
...
```

Choisir une opération simple :

```cpp
window.SetTitle(...);
```

puis montrer son chemin vers deux backends.

### Conclusion orale

> Le programme utilisateur parle une API commune ; le module absorbe les différences du système.

---

## DEMO 2 — LE DÉFAUT INVISIBLE

### Traduction

> Construis une interface qui paraît correcte à 100 % de mise à l'échelle et qui devient incorrecte à 125/150 %, puis montre la correction.

### Méthode

Comparer une valeur de taille obtenue au mauvais endroit avec :

```text
la taille client réelle
+
le DPI réel
```

---

## DEMO 3 — LA BARRE DE TITRE À SOI

### Traduction

> Montre une fenêtre sans bordure fonctionnelle et explique ce que tu as dû reconstruire.

Liste :

```text
déplacement
maximisation
réduction
fermeture
double-clic
redimensionnement
```

---

## DEMO 4 — LE MÊME PROGRAMME SUR DEUX SYSTÈMES

### Traduction

> Fais tourner le même code et relève ce que le programme ne gère pas directement : la différence de plateforme est absorbée par NKWindow.

---

# 19. CHAPITRE 4 — RÉFLEXE CENTRAL

Avant de coder un événement, demande-toi :

```text
EST-CE QUE JE VEUX...
```

### savoir qu'une chose vient d'arriver ?

```text
EVENT
```

### savoir si elle est actuellement vraie ?

```text
STATE
```

### exprimer ce que veut faire le joueur ?

```text
ACTION / INTENTION
```

Cette grille permet de résoudre la majorité des exercices du chapitre 4.

---

# 20. C4-EXO1 — LE JOURNAL DES ÉVÉNEMENTS

## Traduction simple

> Chaque fois que NKWindow reçoit un événement, affiche son type et sa famille. Fais ensuite une mesure pendant une seconde d'utilisation normale.

## Code de départ

```cpp
NkEvent* event = nullptr;

while ((event = NkEvents().PollEvent()) != nullptr)
{
    logger.Info(
        "Event type = {}",
        event->GetType()
    );
}
```

Pour la famille :

```text
chercher dans l'énumération actuelle des événements
ou les méthodes de classification du header.
```

Le header maître actuel inclut :

```text
WINDOW
KEYBOARD
MOUSE
TOUCH
GAMEPAD
DROP
GRAPHICS
SYSTEM
APPLICATION
TRANSFER
GENERIC_HID
CUSTOM
```

---

# 21. C4-EXO2 — LA LETTRE ET LA POSITION

## Traduction

> Pour chaque touche, montre sa signification logique et sa position physique. Change ensuite AZERTY/QWERTY et compare.

### À retenir

```text
NkKey
    =
signification / touche logique

NkScancode
    =
position physique
```

### Expérience

```text
AZERTY
appuyer sur une touche

QWERTY
même position physique

comparer les deux valeurs
```

---

# 22. C4-EXO3 — FERMER PROPREMENT

## Traduction

> Une seule cause doit conduire à l'arrêt normal : l'événement de fermeture de fenêtre.

## Pattern

```cpp
if (event->Is<NkWindowCloseEvent>())
{
    window.Close();
}
```

Puis :

```cpp
while (window.IsOpen())
{
    ...
}
```

## Objectif architectural

```text
événement
   ↓
commande Close
   ↓
IsOpen = false
   ↓
sortie
```

---

# 23. C4-EXO4 — LE POINTEUR QUI MEURT

## Traduction

> Sauvegarde volontairement un `NkEvent*` d'une trame à l'autre. Observe ce qui se passe lorsque `PollEvent()` est rappelé. Ensuite utilise la fonction de copie prévue par le système.

Le support demande explicitement l'expérience avec `PollEventCopy`.

### Version expérimentale

```cpp
NkEvent* saved = nullptr;

while (window.IsOpen())
{
    NkEvent* event = NkEvents().PollEvent();

    if (event)
    {
        saved = event;
    }

    // Utiliser saved ici est volontairement l'expérience.
}
```

### Correction conceptuelle

Utiliser l'API de copie réellement présente dans ton kit.

Avant d'écrire le nom final :

```text
Ctrl+Shift+F
PollEventCopy
```

Si elle existe :

```text
copie
=
propriété de ton code

pointeur
=
durée de vie limitée par le système d'événements
```

---

# 24. C4-EXO5 — LE CLIC CONSOMMÉ

## Traduction

> Deux gestionnaires veulent le même clic. Le premier possède un panneau dans un coin. Si le clic tombe dans le panneau, le premier gestionnaire doit retourner `true` et empêcher la propagation.

### Modèle

```cpp
bool OnPanelClick(const NkEvent& event)
{
    if (/* clic dans le panneau */)
    {
        logger.Info("Panneau : clic consomme");
        return true;
    }

    return false;
}
```

Puis un deuxième handler journalise les clics restants.

### Test

```text
clic dans panneau
→ A
→ pas B

clic hors panneau
→ A renvoie false
→ B
```

---

# 25. C4-EXO6 — LES TROIS HAUTEURS

## Traduction

> Fais avancer le même carré à droite selon trois méthodes totalement différentes, puis compare ce que chaque méthode sait du clavier.

### A — événement

```text
KeyPress RIGHT
   ↓
square.x += speed
```

### B — état

```text
if (state.right)
    square.x += speed;
```

### C — action

```text
action "droite"
   ↓
square.x += speed;
```

## Tableau de comparaison

```md
| Technique | Connait la touche ? | Compatible manette naturellement ? | Testable sans clavier ? |
|-----------|---------------------|-------------------------------------|--------------------------|
| événement | oui | pas automatiquement | difficile |
| état | oui | possible mais logique couplée | moyen |
| action | non | oui | oui |
```

---

# 26. C4-EXO7 — LE FRONT MONTANT

## Traduction

> Avec l'état courant, une touche peut rester vraie plusieurs frames. Il faut donc détecter uniquement le passage de `false` à `true`.

## Formule

```cpp
bool justPressed = pressedNow && !pressedBefore;
pressedBefore = pressedNow;
```

### Démonstration

```text
frame 1 : false
frame 2 : true   -> saut
frame 3 : true   -> aucun nouveau saut
frame 4 : true   -> aucun nouveau saut
frame 5 : false
```

Puis comparer à un événement `KeyPress` qui représente directement l'occurrence.

---

# 27. C4-EXO8 — LA MANETTE

## Traduction

> Le même déplacement doit fonctionner avec clavier et manette. La logique qui déplace le carré ne doit exister qu'une seule fois. Si la manette disparaît, le jeu doit se mettre en pause.

## Architecture

```text
          clavier
             │
             ▼
       ┌───────────┐
       │  action   │
       │ "gauche"  │
       └─────┬─────┘
             │
             ▼
       logique carré
             ▲
             │
       ┌─────┴─────┐
       │ manette   │
       └───────────┘
```

### Débranchement

```text
Gamepad removed
    ↓
manetteActive = false
    ↓
paused = true
```

---

# 28. C4-EXO9 — LA ZONE MORTE

## Traduction

> Une manette au repos ne donne pas toujours exactement zéro. Mesure le bruit réel pendant dix secondes, puis choisis un seuil légèrement supérieur.

## Algorithme

```cpp
float maxAbs = 0.0f;

while (elapsed < 10.0)
{
    float raw = /* lire axe */;
    maxAbs = std::max(maxAbs, std::abs(raw));
}
```

Puis choisir une zone morte justifiée.

## Rapport

```md
Valeur maximale absolue observée :
...

Zone morte choisie :
...

Pourquoi :
...
```

---

# 29. C4-EXO10 — LES TOUCHES RECONFIGURABLES

## Traduction

> Les touches choisies par l'utilisateur doivent être écrites dans un fichier. Le programme charge ces mappings. L'utilisateur peut ensuite modifier un mapping sans modifier la logique du jeu.

## Architecture

```text
config.ini / json / format choisi
            ↓
        loader
            ↓
     action mapping
            ↓
        gameplay
```

### Le gameplay ne doit pas écrire :

```cpp
if (key == NkKey::NK_SPACE)
```

pour la logique métier.

Il doit écrire quelque chose comme :

```cpp
if (actions.IsPressed("sauter"))
{
    joueur.Sauter();
}
```

---

# 30. C4-EXO11 — GLISSER-DÉPOSER

## Traduction

> Fais reconnaître six situations :
>
> - entrée dans la zone ;
> - déplacement au-dessus de la zone ;
> - sortie ;
> - texte ;
> - fichier ;
> - image.
>
> Affiche un état visuel pendant le survol.

## Machine d'état

```text
OUTSIDE
   |
   | ENTER
   v
HOVER
   |
   | LEAVE
   v
OUTSIDE
```

À chaque `OVER` :

```text
highlight = true
```

À `LEAVE` :

```text
highlight = false
```

À l'arrivée :

```text
identifier la nature du contenu
```

---

# 31. C4-EXO12 — LE REJEU

## Traduction

> Pendant une minute, enregistre les actions que le joueur déclenche avec leurs timestamps. Ensuite désactive les entrées humaines et rejoue exactement ces actions.

## Structure minimale

```cpp
struct RecordedAction
{
    double timeSeconds;
    std::string name;
};
```

## Enregistrement

```text
action déclenchée
   ↓
timestamp depuis début
   ↓
push_back
```

## Rejeu

```text
timestamp courant
   ↓
actions dont le temps est atteint
   ↓
même fonction de gameplay
```

## Le vrai but

Prouver :

```text
gameplay
   ≠
clavier
```

Puisque le gameplay accepte :

```text
clavier
manette
rejeu
```

sans modification.

---

# 32. SÉRIE 6 — DÉMONSTRATIONS

## C4-DEMO1 — LE CHEMIN D'UNE TOUCHE

Présenter :

```text
matériel
 ↓
système d'exploitation
 ↓
backend plateforme
 ↓
NKEvent
 ↓
file d'événements
 ↓
PollEvent
 ↓
application
```

---

## C4-DEMO2 — LES TROIS HAUTEURS

Faire démontrer le même geste :

```text
EVENT
STATE
ACTION
```

Puis demander :

```text
menu ?
déplacement ?
saut ?
raccourci ?
visée ?
```

---

## C4-DEMO3 — RECONFIGURATION EN DIRECT

Pendant que le programme tourne :

```text
"gauche" = touche A
```

puis :

```text
"gauche" = touche D
```

sans recompiler le gameplay.

---

## C4-DEMO4 — LE JEU QUI SE JOUE TOUT SEUL

```text
enregistrer
  ↓
une minute
  ↓
stop
  ↓
rejouer
```

Puis expliquer :

```text
test automatique
reproduction de bug
régression
```

---

# 33. GUIDE DES FICHIERS `.MD`

Chaque exercice doit avoir un compte-rendu qui ressemble à un vrai journal de travail.

## Exemple robuste

```md
# C3-EXO4 — Le facteur d'échelle

## 1. Reformulation de l'énoncé

Le but est de distinguer la taille de la zone cliente de la fenêtre,
la taille du moniteur courant et le facteur DPI.

## 2. Ce que je cherche à observer

...

## 3. API utilisées

...

## 4. Première mesure

...

## 5. Changement de mise à l'échelle

...

## 6. Deuxième mesure

...

## 7. Comparaison

...

## 8. Interprétation

...

## 9. Difficultés

...

## 10. Conclusion

...
```

---

# 34. COMMENT COMMENTER CORRECTEMENT LE CODE

### Mauvais commentaire

```cpp
i++;
// on incrémente i
```

### Meilleur commentaire

```cpp
// Le compteur représente ici le nombre de redimensionnements
// observés depuis le lancement de l'expérience.
++resizeCount;
```

Le commentaire doit expliquer :

```text
pourquoi le code existe
```

et pas répéter littéralement :

```text
ce que fait chaque symbole.
```

---

# 35. ERREURS DE VERSION DÉJÀ OBSERVÉES

## `undefined reference to nkmain(...)`

Cause :

```text
Le runtime cherche :
nkmain(const NkEntryState&)
```

mais le programme fournissait :

```text
nkmain()
```

Correction :

```cpp
int nkmain(const nkentseu::NkEntryState& state)
```

---

## `Create()` sans argument

Le kit actuel déclare :

```cpp
bool Create(const NkWindowConfig& config);
```

Donc :

```cpp
window.Create();
```

est faux dans cette version.

---

## mauvais chemin en casse

Mauvais :

```cpp
#include "NkWindow/NKWindow.h"
```

Correct :

```cpp
#include "NKWindow/NKWindow.h"
```

selon l'arborescence actuelle du kit.

---

## `i = i++`

À éviter.

Utiliser :

```cpp
++i;
```

---

## `NkString nom = std::cout << ...`

Incorrect.

`std::cout` est un flux.

Construire d'abord le texte puis :

```text
SetTitle
```

---

# 36. PROCÉDURE VS CODE POUR RETROUVER UNE API

```text
Ctrl + Shift + F
```

Rechercher :

```text
SetTitle
```

puis :

```text
GetSize
```

puis :

```text
SetCursor
```

puis :

```text
CaptureMouse
```

puis :

```text
GetClipboardImage
```

puis :

```text
NkWindowCloseEvent
```

puis :

```text
NkKeyPressEvent
```

puis :

```text
NkDropEvent
```

puis :

```text
NkActionCommand
```

### Principe

Tu ne cherches pas seulement le nom de la fonction.

Tu dois ouvrir la **déclaration** et, lorsque le comportement est important, l’**implémentation**.

---

# 37. MÉTHODE POUR LIRE LE CODE MÈRE

Pour une méthode :

```cpp
bool Create(const NkWindowConfig& config);
```

il faut retrouver :

```text
1. déclaration
2. définition
3. implémentation Windows
4. implémentation Linux/macOS si pertinent
5. événements générés
```

Cela permet de répondre à :

> « Que promet exactement l'API ? »

au lieu de :

> « Que semble faire son nom ? »

---

# 38. VÉRIFICATION AVANT DE COPIER UN EXEMPLE D'UN CAMARADE

Avant d'utiliser un exemple :

```text
1. le même kit est-il utilisé ?
2. même date de code ?
3. mêmes includes ?
4. même signature de nkmain ?
5. même API ?
6. exemple compilé aujourd'hui ?
```

Un exemple peut être pédagogiquement excellent mais ne plus compiler dans ton kit.

---

# 39. TESTS SYSTÉMATIQUES

## Fenêtre

- création ;
- taille ;
- position ;
- resize ;
- minimize ;
- maximize ;
- restore ;
- close.

## Souris

- move ;
- button ;
- capture ;
- cursor ;
- leave.

## Clavier

- press ;
- release ;
- repeat ;
- text.

## Display

- écran unique ;
- deux écrans ;
- changement de DPI ;
- déplacement de fenêtre.

## Clipboard

- texte ;
- image ;
- vide ;
- format non supporté.

## Gamepad

- connexion ;
- bouton ;
- axe ;
- débranchement.

---

# 40. MODÈLE DE TABLEAU DE TEST

```md
| Test | Entrée | Résultat attendu | Résultat obtenu | Statut |
|------|--------|------------------|-----------------|--------|
| 1 | ... | ... | ... | OK |
| 2 | ... | ... | ... | OK |
| 3 | ... | ... | ... | À corriger |
```

---

# 41. CE QUI EST À MESURER ET CE QUI EST À EXPLIQUER

## Mesurer

```text
DPI
dimensions
positions
nombre d'événements
valeur max axe
temps
```

## Expliquer

```text
architecture
différence Event / State / Action
durée de vie d'un pointeur
découplage plateforme
raisons d'une zone morte
```

Ne pas inventer une mesure.

Ne pas présenter une hypothèse comme un résultat.

---

# 42. ORDRE DE TRAVAIL RECOMMANDÉ

```text
C3-EXO4
   ↓
C3-EXO5
   ↓
C3-EXO6
   ↓
C3-EXO7
   ↓
C3-EXO8
   ↓
C3-EXO9
   ↓
C3-EXO10
   ↓
C3-EXO11
   ↓
C3-EXO12
   ↓
DEMOS C3
   ↓
C4-EXO1
   ↓
C4-EXO2
   ↓
C4-EXO3
   ↓
C4-EXO4
   ↓
C4-EXO5
   ↓
C4-EXO6
   ↓
C4-EXO7
   ↓
C4-EXO8
   ↓
C4-EXO9
   ↓
C4-EXO10
   ↓
C4-EXO11
   ↓
C4-EXO12
   ↓
DEMOS C4
```

Pourquoi ?

Parce que cette progression respecte la dépendance des concepts :

```text
fenêtre
 ↓
événement
 ↓
état
 ↓
action
 ↓
reconfiguration
 ↓
rejeu
```

---

# 43. CHECKLIST DE LIVRAISON

## Chaque `.cpp`

```text
[ ] nom exact
[ ] includes corrects
[ ] signature nkmain correcte
[ ] build réussi
[ ] comportement testé
[ ] pas d'API inventée
[ ] pas de chemin incorrect
```

## Chaque `.md`

```text
[ ] objectif reformulé
[ ] méthode
[ ] API
[ ] expérience
[ ] observation réelle
[ ] interprétation
[ ] difficulté
[ ] correction
[ ] conclusion
```

## Dépôt

```text
[ ] dossier exact
[ ] fichiers exacts
[ ] commit
[ ] arbre propre
```

---

# 44. FICHE ULTRA-RAPIDE À GARDER À CÔTÉ

```text
NKWINDOW
────────────────────────────
Create(config)
Close()
IsOpen()

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
BeginResize()

SetFullscreen()

SetClipboardText()
GetClipboardText()

SetClipboardImage()
GetClipboardImage()
HasClipboardImage()

CaptureMouse()
SetCursor()
ClipMouseToClient()
```

---

# 45. FICHE ÉVÉNEMENTS

```text
WINDOW
KEYBOARD
MOUSE
TOUCH
GAMEPAD
DROP
GRAPHICS
SYSTEM
APPLICATION
TRANSFER
GENERIC_HID
CUSTOM
```

Et surtout :

```text
EVENT
    "qu'est-ce qui vient d'arriver ?"

STATE
    "qu'est-ce qui est vrai maintenant ?"

ACTION
    "qu'est-ce que le joueur veut faire ?"
```

---

# 46. CE QUE L'ENSEIGNANT CHERCHE À VOIR

Un bon rendu n'est pas seulement un programme qui compile.

Il doit laisser comprendre que tu sais :

```text
lire une API
    ↓
choisir la bonne abstraction
    ↓
écrire une petite expérience
    ↓
observer le système
    ↓
expliquer le résultat
```

La phrase la plus importante de ce guide est donc :

> **Ne code jamais le nom de l'exercice ; code le mécanisme qu'il cherche à faire comprendre.**

---

# 47. SOURCES DE VÉRIFICATION

## Support RIHEN Academy

Le Sprint 3 fourni dans cette conversation.

## Code mère Nkentseu

Fichiers particulièrement importants :

```text
Kernel/Runtime/NKWindow/src/NKWindow/Core/NkWindow.h
Kernel/Runtime/NKWindow/src/NKWindow/Core/NkWindowConfig.h
Kernel/Runtime/NKWindow/src/NKWindow/Core/NkEvent.h
```

Repository :

```text
https://github.com/Rihen-Universe/Nkentseu
```

---

# 48. NOTE SUR LES DÉPÔTS DE CAMARADES

Les deux dépôts suivants ont été ciblés pour comparaison :

```text
https://github.com/dikoume-stephane/ani-2053/tree/main/chapitre-03
https://github.com/Nyeck-Abondo/ani-2053/tree/main/chapitre-03
```

Dans cette session, leur arborescence et leurs fichiers individuels n'ont pas pu être récupérés de façon fiable par le navigateur GitHub. Le guide **ne prétend donc pas avoir utilisé leur code**.

Pour une comparaison fiable, la bonne méthode reste :

```text
repo camarade
   ↓
fichier exact
   ↓
code
   ↓
version du kit
   ↓
test local
```

et non une supposition à partir de captures ou de noms de fichiers.

---

# 49. AVERTISSEMENT FINAL SUR LES EXEMPLES

Les blocs de code de ce document sont des **propositions pédagogiques**.

Avant de les intégrer à un exercice :

1. ouvre le header actuel ;
2. vérifie le type ;
3. vérifie le prototype ;
4. compile ;
5. teste le comportement ;
6. adapte les résultats au comportement réellement observé.

C'est particulièrement important pour :

```text
NkString
NkVec2u
NkDisplayInfo
NkEvent
NkActionCommand
```

car ton kit a évolué récemment.

---

# 50. FIN

Le Sprint 3 paraît très grand parce que les énoncés sont courts et supposent que les notions sont déjà comprises.

Une fois qu'ils sont reformulés :

```text
fenêtre
→ propriétés
→ affichage
→ souris
→ presse-papiers
→ dialogues
→ fenêtres multiples
→ écrans
→ événements
→ état
→ actions
→ périphériques
→ configuration
→ rejeu
```

il devient possible de traiter les tâches une par une sans apprendre 56 concepts indépendants.

**Le bon objectif n'est pas seulement de terminer les exercices.  
Le bon objectif est de pouvoir expliquer pourquoi chaque ligne est là.**
