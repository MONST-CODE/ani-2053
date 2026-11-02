# Fiche de révision complète — Sprint 8 / Chapitre 13

**Thème :** motifs de conception observés dans le moteur Canvas-kit de Nkentseu  
**Kit de référence :** Canvas-kit Windows du 22 octobre 2026  
**Travail :** 10 exercices, de `chapitre-08/exo1-le_motif_et_son_fichier` à `chapitre-08/exo10-le_motif_absent`  
**Échéance indiquée dans l'énoncé :** 2 novembre 2026 à 23 h 59.

---

## Comment utiliser cette fiche pendant une journée de travail hors ligne

Cette fiche est conçue pour être suivie dans l'ordre. Elle ne remplace pas les observations et les essais demandés : elle t'explique **quoi chercher, comment le vérifier, pourquoi le faire, ce que les résultats signifient et ce qu'il ne faut pas conclure trop vite**.

Le Sprint ne demande pas seulement de connaître neuf définitions. Il te demande de lire un moteur réel, de repérer des motifs dans ses en-têtes, de mesurer les conséquences d'une architecture, de construire des programmes de vérification et de reconnaître un défaut qui pourrait rester caché longtemps.

### Règle de rigueur utilisée dans toute la fiche

Les affirmations sont classées de cette manière :

- **[ÉNONCÉ]** : information explicitement donnée dans la consigne du professeur.
- **[EN-TÊTE OBSERVÉ]** : information vérifiée dans un fichier du kit du 22 octobre 2026.
- **[DÉDUCTION]** : conclusion logique tirée des éléments visibles, mais qui n'est pas une mesure d'exécution.
- **[À MESURER]** : résultat qui exige de compiler, lancer le programme ou relever une valeur sur ta machine.
- **[COMMENTAIRE SEUL]** : information présente dans un commentaire ou un exemple commenté ; elle ne prouve pas que le code exécute cette action.

Cette distinction est capitale. Le kit contient des en-têtes et des bibliothèques compilées, mais pas toutes les implémentations C++ sous forme de fichiers source. Un en-tête peut déclarer une fonction sans montrer son corps. Dans ce cas, tu peux décrire le contrat déclaré, mais tu ne dois pas inventer le détail de l'implémentation.

### Matériel à préparer avant de te déconnecter

1. Le dossier du kit extrait depuis `Canvas-kit-Windows.zip` du 22 octobre 2026.
2. Ton dépôt `MONST-CODE` accessible localement, avec le dossier `ani-2053`.
3. Un éditeur capable d'afficher les numéros de lignes, par exemple VS Code.
4. Un terminal PowerShell dans le dossier `Canvas` du kit.
5. Ton compilateur et l'environnement de construction Windows déjà fonctionnels pour le kit.
6. Un dossier de travail pour les journaux d'exécution, captures d'écran et résultats Debug/Release.

**Attention :** les exercices 4, 6 et 8 exigent des constructions et des exécutions réelles. Je ne fournis aucun faux journal, aucune fausse capture et aucun résultat Debug/Release inventé. Les calculs mathématiques et constats statiques sont fournis lorsqu'ils peuvent être établis sans exécuter ton programme. Les résultats de ton exécutable restent à relever sur ta machine.

---

# 1. Les bases nécessaires pour comprendre les dix exercices

## 1.1 Programme, module, classe, objet

Un programme est un ensemble d'instructions qui coopèrent pour produire un résultat. Un moteur de jeu, par exemple, peut contenir des systèmes de fenêtre, d'événements, d'entrée, de rendu, de ressources et d'interface graphique.

Un **module** regroupe une responsabilité ou une famille de fonctionnalités. Un **fichier d'en-tête** `.h` expose des déclarations : classes, fonctions, types, constantes et parfois des implémentations définies directement dans l'en-tête.

Une **classe** est une description d'un type d'objet. Un **objet** est une instance de cette classe.

```cpp
class Player {
public:
    int health = 100;

    void TakeDamage(int amount) {
        health -= amount;
    }
};

int main() {
    Player first;
    Player second;
    first.TakeDamage(20);
}
```

Ici :

- `Player` est une classe ;
- `first` et `second` sont deux objets ;
- `health` est une donnée membre ;
- `TakeDamage` est une méthode ;
- l'**état** de chaque objet est l'ensemble des données qu'il conserve à cet instant. Après l'appel, `first.health` vaut 80 et `second.health` vaut 100.

Cette notion d'état est essentielle pour l'exercice 6 sur le Singleton.

## 1.2 Fonction, paramètre, valeur de retour

Une fonction reçoit éventuellement des informations par ses paramètres, effectue un travail et peut renvoyer une valeur.

```cpp
bool CanJump(bool onGround, bool spaceDown) {
    return onGround && spaceDown;
}
```

- `onGround` et `spaceDown` sont des paramètres ;
- `&&` signifie « ET logique » ;
- la fonction renvoie `true` seulement si les deux paramètres valent `true`.

Une valeur de retour peut aussi servir de signal de contrôle. Dans le répartiteur d'événements du kit, `true` signifie que l'événement a été consommé ; ce n'est pas un signal d'erreur.

## 1.3 Interface et implémentation

Une **interface** décrit ce qu'un composant promet de savoir faire. Une **implémentation** est le code qui réalise réellement ces opérations.

En C++, une interface peut être représentée par une classe abstraite comportant des fonctions virtuelles pures :

```cpp
class Renderer {
public:
    virtual void Draw() = 0;
    virtual ~Renderer() = default;
};
```

`= 0` indique ici une fonction virtuelle pure. Une classe concrète qui hérite de `Renderer` doit fournir une implémentation de `Draw()` pour pouvoir être instanciée.

```cpp
class VulkanRenderer : public Renderer {
public:
    void Draw() override {
        // Implémentation de Draw pour Vulkan.
    }
};
```

`override` indique que cette méthode redéfinit une méthode virtuelle héritée. Le compilateur vérifie que la signature correspond bien à une méthode virtuelle de la classe de base.

**Ne confonds pas :**

- `virtual` : permet le dispatch dynamique, c'est-à-dire l'appel de l'implémentation correspondant au type réel de l'objet ;
- `= 0` : rend la fonction virtuelle pure ;
- `override` : indique qu'une méthode dérivée redéfinit une méthode héritée ;
- une méthode virtuelle avec un corps : elle peut avoir un comportement par défaut, que les classes dérivées peuvent éventuellement redéfinir.

## 1.4 Héritage, classe de base et classe dérivée

```cpp
class Base {
public:
    virtual void Update() = 0;
};

class GameObject : public Base {
public:
    void Update() override {
        // Mise à jour de cet objet.
    }
};
```

`Base` est la classe de base ; `GameObject` est une classe dérivée. L'héritage réutilise le contrat de la base et permet le polymorphisme.

Une classe dérivée peut hériter d'une autre classe intermédiaire. Dans Canvas, les backends graphiques héritent de `NkBatchRenderer2D`, qui hérite lui-même de `NkIRenderer2D`. Il faut donc regarder la **classe mère directe** d'un backend, pas supposer qu'il hérite immédiatement de l'interface principale.

## 1.5 Polymorphisme : travailler avec un contrat commun

Si plusieurs classes dérivent d'une même interface, une fonction peut recevoir une référence vers cette interface et utiliser l'implémentation réelle fournie à l'exécution.

```cpp
void RenderScene(Renderer& renderer) {
    renderer.Draw();
}
```

Cette fonction ne connaît pas directement `VulkanRenderer` ou `OpenGLRenderer`. Elle connaît seulement le contrat `Renderer`.

C'est une idée fondamentale de la stratégie : **le code client dépend d'une abstraction plutôt que d'une classe concrète**.

## 1.6 Dépendance et couplage

Un composant A dépend de B lorsque A a besoin de connaître B ou d'utiliser ses services. Plus A connaît les détails internes de B, plus ils sont couplés.

Un motif de conception cherche souvent à modifier la forme de ces dépendances :

- une fabrique centralise la connaissance des classes concrètes à construire ;
- un adaptateur évite que deux interfaces incompatibles se connaissent directement ;
- un observateur permet à l'émetteur d'un événement de prévenir des abonnés sans connaître leur logique métier ;
- une façade évite au programme client de coordonner tous les détails d'un sous-système.

## 1.7 Allocation, durée de vie et allocateur

Créer un objet, c'est obtenir un espace mémoire et y construire cet objet. Le détruire correctement exige de respecter les règles d'allocation utilisées.

Un allocateur personnalisé peut imposer des règles qui diffèrent de `new`/`delete`. Le kit le rappelle explicitement dans `NkRenderer2DFactory.h` : le renderer créé doit être libéré par `Destroy()` ou confié à un `NkUniquePtr`, et il ne faut pas faire `delete` directement sur le pointeur brut.

Un pointeur intelligent comme `std::unique_ptr<T>` ou le type propriétaire du moteur `NkUniquePtr<T>` représente une stratégie de propriété : il aide à gérer automatiquement la durée de vie. Cela ne définit toutefois pas, à lui seul, le motif Fabrique.

## 1.8 Const, global, inline, pointeur et référence

- `const` signifie qu'une méthode ne modifie pas l'état visible de l'objet à travers cette méthode (cela ne garantit pas que tout l'environnement soit immuable).
- Une variable globale est accessible depuis de nombreux endroits ; cela peut créer des dépendances difficiles à voir.
- `inline` permet notamment des définitions dans les en-têtes sans violer la règle de définition unique dans le cas prévu par le langage. Ce mot-clé ne rend pas automatiquement un objet « sûr » ou bien conçu.
- Une référence `T&` désigne un objet existant et ne peut pas être nulle.
- Un pointeur `T*` peut représenter une absence (`nullptr`) et peut être réaffecté.

Ces distinctions interviennent dans le Singleton, le test, le Composite et le second pont.

## 1.9 État ponctuel et événement

Un **événement** indique qu'une chose vient de se produire : un clic, un appui de touche, un dépôt de fichier, une demande de fermeture. Un **état** indique ce qui est vrai à un instant : touche maintenue, position actuelle de la souris, bouton encore enfoncé.

Cette différence conduit à Push et Pull :

- **Push** : le système te prévient quand l'événement arrive ;
- **Pull** : ton programme interroge l'état lorsqu'il en a besoin.

## 1.10 Transformations en graphisme 2D

Une transformation permet de déplacer, faire tourner ou redimensionner un objet.

Dans le kit, `NkTransformable.h` documente la transformation locale ainsi :

`T = Translate(position) * Rotate(rotation) * Scale(scale) * Translate(-origin)`.

`NkTransform.h` précise la convention de composition : `A * B` applique B puis A. Pour un parent qui contient un enfant :

`world = parent * local`.

Autrement dit, on commence par appliquer la transformation locale de l'enfant, puis celle du parent, puis celle du parent supérieur, etc. C'est la base de l'exercice 8.

---

# 2. Les neuf motifs : explication approfondie

## 2.1 Stratégie — plusieurs façons de faire une même chose

**Problème :** un composant doit pouvoir exécuter un comportement qui varie selon le contexte ou le choix de l'utilisateur.

**Idée :** isoler le comportement variable derrière un contrat commun. Le client sélectionne ou reçoit une stratégie, puis l'utilise sans avoir besoin de connaître tous ses détails.

Exemple classique : plusieurs algorithmes de déplacement, plusieurs méthodes de compression ou plusieurs backends de rendu partageant une interface.

Une stratégie peut être une classe, mais en C++ moderne elle peut aussi être une fonction, un lambda, un objet appelable ou un paramètre template. Il ne faut donc pas conclure « pas de stratégie » simplement parce qu'on ne trouve pas une classe nommée `Strategy`.

**Avantage :** ajouter ou remplacer un comportement sans propager des conditions dans tout le code client.

**Coût :** une abstraction à maintenir, des implémentations à écrire et parfois de l'indirection.

**Quand l'éviter :** lorsqu'il n'existe qu'un seul comportement stable et aucune variation réelle à gérer.

## 2.2 Fabrique — créer sans exposer le type concret

**Problème :** le code client doit obtenir un objet, mais ne devrait pas devoir choisir ou connaître directement sa classe concrète.

**Idée :** centraliser la construction dans une fonction ou un objet chargé de choisir, créer et éventuellement initialiser l'instance.

**Avantage :** le choix de l'implémentation est rassemblé en un endroit ; le client utilise le type abstrait.

**Coût :** couche supplémentaire ; la fabrique devient un lieu à maintenir ; gestion de la propriété et de la destruction à clarifier.

**Point particulier du moteur :** `NkRenderer2DFactory` utilise l'allocateur NKMemory. Le contrat visible impose `Destroy()` plutôt que `delete` direct. C'est une contrainte du moteur, pas une propriété universelle de toutes les fabriques.

## 2.3 Façade — une porte simple sur un sous-système complexe

**Problème :** un client devrait coordonner de nombreux objets et détails pour réaliser une opération courante.

**Idée :** présenter une API plus commode qui masque ou coordonne le contexte, les ressources, les objets internes et l'ordre des opérations.

**Exemple intuitif :** une façade de cinéma permet de réserver une séance sans que le client appelle séparément le système de sièges, de paiement et de billetterie.

**Avantage :** le client connaît moins de détails et le cas courant devient simple.

**Coût :** la façade peut grossir avec les demandes, accumuler les méthodes avancées et finir par exposer presque toute la complexité qu'elle devait cacher.

Une façade n'est pas nécessairement une interface minuscule. Il faut examiner les méthodes réellement proposées et celles réellement utilisées.

## 2.4 Patron de méthode (*Template Method*) — squelette fixe, étapes variables

**Problème :** plusieurs applications doivent suivre le même processus général, mais certaines étapes doivent être personnalisées.

**Idée :** la classe de base décide de l'ordre global et appelle des méthodes virtuelles que les classes dérivées redéfinissent.

Exemple simplifié : `Run()` appelle `OnInit()`, puis répète `OnUpdate()` et `OnRender()`, puis appelle `OnShutdown()`.

**Avantage :** l'application cliente ne réécrit pas le cycle de vie ; elle fournit seulement les étapes qui lui appartiennent.

**Coût :** l'ordre peut être moins évident pour l'utilisateur de la classe ; certaines méthodes sont appelées sous des conditions qu'il ne contrôle pas. Il faut lire la classe de base et observer les appels réels.

## 2.5 Observateur — prévenir des abonnés

**Problème :** un événement survient et plusieurs composants souhaitent être informés, sans que l'émetteur dépende directement de chacun.

**Idée :** les parties intéressées s'abonnent ; le système appelle leurs gestionnaires lorsque l'événement survient.

Le motif classique utilise un sujet et des observateurs. Une implémentation moderne peut utiliser des fonctions, des lambdas ou des callbacks, sans classe `Listener` abstraite.

**Push :** notification à l'arrivée de l'événement.  
**Pull :** interrogation d'un état courant, à la demande du programme.

Dans le moteur, `NkEventDispatcher` accepte des gestionnaires de type fonction et son `Dispatch` marque l'événement comme traité si le gestionnaire renvoie `true`.

**Coût / pièges :** ordre des abonnés, durée de vie des callbacks, désabonnement, réentrance et consommation de l'événement. Il faut savoir exactement ce que signifie la valeur de retour.

## 2.6 Singleton — instance unique avec point d'accès commun

**Problème :** plusieurs parties du programme doivent accéder au même service unique.

**Idée :** fournir un accès central à une instance plutôt que de créer partout de nouvelles instances indépendantes.

**Risque majeur :** si le Singleton conserve un état mutable global, différentes parties du programme peuvent le lire ou le modifier sans que leurs dépendances soient visibles. Les tests deviennent difficiles à contrôler et l'ordre d'exécution peut changer le résultat.

Un Singleton sans état partagé est parfois moins risqué ; il n'est pas automatiquement idéal. Une fonction libre, un objet explicite passé en paramètre ou une dépendance injectée peuvent être plus simples.

## 2.7 Adaptateur — faire collaborer deux interfaces incompatibles

**Problème :** deux systèmes ont des contrats différents ; l'un ne peut pas appeler directement l'autre.

**Idée :** un objet intermédiaire reçoit les opérations dans le format A et les traduit vers le format B.

Dans le moteur, `NkGuiCanvasBackend` reçoit des listes de dessin de NKGui et appelle les opérations de rendu de `NkIRenderer2D`.

**Avantage :** NKGui n'a pas besoin de connaître NKCanvas. Un second backend peut être envisagé sans modifier la logique qui produit les listes de dessin.

**Coût :** écrire et maintenir la traduction ; gérer correctement les ressources, les états et les différences de capacités entre les deux interfaces.

## 2.8 Composite — traiter un objet et un groupe de la même manière

**Problème :** représenter une hiérarchie où des objets peuvent contenir d'autres objets, tout en permettant de leur appliquer une opération de façon uniforme.

**Idée :** un parent reçoit une opération ou un état, puis la transmet à ses enfants. Les transformations d'un parent se composent avec celles de l'enfant.

Dans Canvas, un enfant doit composer son `GetTransform()` avec l'état reçu : `local.transform *= GetTransform()`.

**Avantage :** construire des scènes hiérarchiques : personnage, membres, arme, éléments attachés, etc.

**Coût / piège :** si un enfant jette l'état reçu au lieu de le composer, il fonctionne éventuellement seul mais cesse d'hériter de la transformation de son parent.

## 2.9 Commande — représenter une action comme un objet

**Problème :** on veut stocker, transmettre, planifier, rejouer ou éventuellement annuler une action.

**Idée :** encapsuler une opération dans une entité qui possède les informations nécessaires pour l'exécuter. Dans sa forme classique, une commande offre par exemple `Execute()` ; une commande annulable peut aussi prévoir `Undo()` ou conserver les informations qui permettront de revenir à l'état précédent.

**Exemple :** un éditeur peut représenter « supprimer ce caractère » comme une commande contenant la position et le caractère supprimé. La commande peut être exécutée, puis annulée en réinsérant le caractère.

**Attention :** un type dont le nom contient `Command` n'est pas automatiquement le motif Commande. Une structure de données qui décrit une commande graphique ou lie un nom d'action à une touche peut ne pas encapsuler une action métier exécutable et annulable.

---

# 3. Préparer la lecture du kit et la collecte des preuves

## 3.1 Répertoire et périmètre

Dans le dossier extrait du kit, place-toi dans `Canvas/`. Les sources d'interface se trouvent dans `include/`. Les bibliothèques compilées se trouvent dans `lib/`.

Le kit de cette version ne fournit pas les corps de toutes les fonctions dans des fichiers `.cpp`. Une déclaration comme :

```cpp
static NkIRenderer2D *Create(NkIGraphicsContext *ctx);
```

prouve qu'une fonction `Create` est déclarée et indique sa signature. Elle ne montre pas comment elle sélectionne et construit le backend. Il ne faut pas raconter son algorithme interne sans preuve.

## 3.2 Commandes utiles dans PowerShell

Depuis le répertoire `Canvas` :

```powershell
# Rechercher un symbole dans tous les en-têtes
rg -n --glob "*.h" "NkOpenGLRenderer2D" include

# Lister les fichiers qui contiennent au moins une occurrence
rg -l --glob "*.h" "NkOpenGLRenderer2D" include

# Trouver les déclarations de fonctions virtuelles pures
rg -n "= 0;" include/NKCanvas/Renderer/Core/NkIRenderer2D.h

# Chercher les redéfinitions dans un dossier
rg -n "override" include/NKCanvas/Backend

# Chercher un type dans tout include
rg -n --glob "*.h" "NkGuiDrawListRaster" include
```

`rg` (ripgrep) doit être installé pour ces commandes. Dans VS Code, l'équivalent est `Ctrl+Shift+F` pour une recherche globale.

## 3.3 Une occurrence trouvée n'est pas une preuve de comportement

Après chaque résultat de recherche :

1. ouvre le fichier exact ;
2. lis la ligne et plusieurs lignes autour ;
3. vérifie si elle est dans du code actif, un commentaire, un exemple de documentation ou une branche conditionnelle ;
4. identifie la fonction ou la classe qui l'entoure ;
5. vérifie que cette ligne réalise réellement le problème associé au motif.

Un commentaire est utile pour comprendre l'intention, mais ne prouve pas que le corps du code fait réellement ce qui est annoncé. Une classe située dans un bloc commenté n'existe pas pour le compilateur.

## 3.4 Journal de preuves recommandé

Pour chaque exercice, note dans un carnet local :

| Élément | Ce qu'il faut écrire |
|---|---|
| Question | Le problème précis à résoudre |
| Fichier | Chemin relatif depuis `include/` |
| Ligne(s) | Numéro(s) obtenu(s) dans cette version du kit |
| Preuve | Déclaration, corps inline, commentaire, exemple commenté ou résultat mesuré |
| Interprétation | Pourquoi la preuve correspond au motif ou à l'exercice |
| Limite | Ce que la preuve ne permet pas de conclure |

Conserve les sorties de recherche et les journaux réels. Ne remplis pas les paragraphes avec des numéros de ligne mémorisés si tu peux les vérifier à nouveau sur ton kit extrait.

---

# 4. Exercice 1 — Le motif et son fichier

**Fichier à rendre :** `ani-2053/chapitre-08/exo1-le_motif_et_son_fichier/motifs.txt`  
**Livrable :** neuf paragraphes étiquetés, exactement dans l'ordre imposé : `Stratégie :`, `Fabrique :`, `Façade :`, `Patron de méthode :`, `Observateur :`, `Singleton :`, `Adaptateur :`, `Composite :`, `Commande :`.

## 4.1 Ce que l'exercice teste

Il ne suffit pas de connaître la définition d'un motif. Tu dois montrer qu'il existe dans un fichier du moteur. Pour huit motifs, il faut une preuve de code, pas simplement un commentaire qui affirme que le motif existe. Pour le motif absent, il faut dire où il manque et montrer ce qui s'en approche le plus.

L'exercice vaut 20 points : fichier 2 ; huit motifs réellement illustrés 8 ; lignes recopiées exactement et numéros corrects 4 ; emplacement absent de Commande et meilleure approximation 3 ; signalement d'un motif montré uniquement par commentaire 3.

## 4.2 Carte des preuves repérées dans le kit du 22 octobre

Les chemins suivants sont relatifs à `Canvas/include/`.

| Motif | Fichier à ouvrir | Repère concret | Pourquoi ce repère est pertinent |
|---|---|---:|---|
| Stratégie | `NKCanvas/Renderer/Core/NkIRenderer2D.h` | ligne 46 | L'interface commune des renderers 2D. Les backends concrets héritent indirectement de cette interface par `NkBatchRenderer2D`. |
| Fabrique | `NKCanvas/Renderer/Core/NkRenderer2DFactory.h` | lignes 29–44 | Classe centralisant `Create`, `Destroy` et `CreateUnique`. |
| Façade | `NKCanvas/Renderer/Targets/NkRenderTarget.h` | lignes 48–60 et 107–153 | Une cible de rendu propose des opérations usuelles et des accès avancés à la machinerie interne. |
| Patron de méthode | `NKCanvas/App/NkCanvasApp.h` | lignes 202–205 et 249–324 | `Run<T>` appelle l'exécution de la classe de base ; les méthodes `On...` sont les crochets personnalisables. Le corps privé complet du cycle de vie n'est pas présent dans l'en-tête. |
| Observateur | `NKEvent/NkEventDispatcher.h` | lignes 113–140 ; aussi `NKEvent/NkEventSystem.h` lignes 314–355 | Dispatch typé vers un callback ; `true` marque l'événement comme traité. L'abonnement est exposé séparément par l'EventSystem. |
| Singleton | `NKEvent/NkEventDispatcher.h` | ligne 417 | Déclaration de l'instance globale `inline NkInputQuery NkInput;`. Les commentaires du bloc précédent expliquent son intention et ses pointeurs internes. |
| Adaptateur | `NKCanvas/UI/NkGuiCanvasBackend.h` | lignes 26, 38–41, 213, 295–297, 455 | Le backend reçoit les listes de NKGui puis appelle le renderer 2D de NKCanvas. |
| Composite | `NKCanvas/Renderer/Resources/NkSprite.h` | ligne 40 et ligne 98 | Le sprite combine `NkTransformable` et `NkDrawable`; son dessin doit composer l'état reçu avec sa transformation locale. |
| Commande | Aucun motif général complet confirmé dans le code actif sous cette forme | voir les approximations ci-dessous | Les structures proches ne prouvent pas qu'une action métier encapsulée, exécutable et éventuellement annulable existe. |

## 4.3 Explications détaillées par motif

### Stratégie

`NkIRenderer2D.h:46` :

```cpp
class NkIRenderer2D {
```

Cette classe représente le contrat commun que les renderers 2D doivent respecter. Le fichier `NkBatchRenderer2D.h:31` montre que `NkBatchRenderer2D` hérite de cette interface. Les backends, eux, héritent de `NkBatchRenderer2D`.

Pourquoi c'est une stratégie ? Le code qui consomme `NkIRenderer2D` peut utiliser un renderer concret différent sans changer le contrat côté appelant. Il s'agit de plusieurs manières de fournir le service de rendu.

La preuve doit être nuancée : le nom `NkIRenderer2D` ne suffit pas. Il faut aussi montrer qu'il existe plusieurs implémentations concrètes dans `NKCanvas/Backend/` et qu'elles respectent le contrat commun. L'exercice 2 approfondit cette preuve.

### Fabrique

`NkRenderer2DFactory.h:36` :

```cpp
static NkIRenderer2D *Create(NkIGraphicsContext *ctx);
```

`NkRenderer2DFactory.h:41` :

```cpp
static void Destroy(NkIRenderer2D *renderer);
```

La fonction crée et rend un pointeur d'interface, et non un pointeur typé `NkOpenGLRenderer2D` imposé au client. Le client peut donc utiliser le contrat abstrait. Les commentaires des lignes 31–40 précisent la propriété du pointeur et la règle de destruction.

**Limite :** le corps de `Create` n'est pas donné dans cet en-tête. Tu ne peux pas raconter la séquence interne de sélection du backend en prétendant l'avoir lue. Tu peux prouver le contrat déclaré et le fait que la fabrique centralise l'opération de création.

### Façade

`NkRenderTarget.h:48` :

```cpp
class NkRenderTarget {
```

`NkRenderTarget.h:55` :

```cpp
virtual void Clear(const NkColor2D &color = NkColor2D::Black) = 0;
```

`NkRenderTarget.h:59` :

```cpp
virtual void Display() = 0;
```

`NkRenderTarget` présente une manière d'utiliser une cible de rendu sans obliger l'application à gérer elle-même chaque détail du contexte et du renderer interne. Il propose notamment l'effacement, le dessin et la présentation de l'image.

**Nuance importante :** ce n'est pas une façade qui cache absolument tout. Les lignes 138–144 donnent aussi un accès direct au renderer bas niveau et à `NkRenderer2D`. C'est une façade qui simplifie le cas courant tout en offrant des portes de bas niveau pour les usages avancés. Cette nuance préparera l'exercice 9.

### Patron de méthode

`NkCanvasApp.h:202–205` :

```cpp
template <typename T> static int Run(const NkEntryState &state) {
    T app;
    return static_cast<NkCanvasApp &>(app).Execute(state);
}
```

L'application fournit une classe dérivée `T`. La classe de base possède le processus d'exécution via `Execute`, et les méthodes virtuelles `OnInit`, `OnUpdate`, `OnRender`, `OnShutdown`, etc. sont les étapes que l'application peut personnaliser.

**Limite documentaire :** `Execute` est déclaré dans la section privée, mais son corps n'est pas donné dans cet en-tête. L'ordre exact du cycle de vie est donc à prendre dans l'extrait de boucle fourni par l'exercice 4 et à vérifier par le journal d'exécution. Il faut distinguer le squelette visible des hooks et le corps réel de la boucle.

### Observateur

Dans `NkEventDispatcher.h:121–140`, on trouve un `Dispatch` typé qui vérifie le type de l'événement, appelle le gestionnaire, puis marque l'événement comme traité si le gestionnaire renvoie `true`.

```cpp
bool consumed = handler(static_cast<T &>(*mEvent));
if (consumed) {
    mEvent->MarkHandled();
}
return consumed;
```

C'est du code actif dans l'en-tête, et pas seulement un exemple commenté. Les fonctions de rappel sont des objets appelables : le moteur n'a pas besoin de fournir une classe abstraite `Listener` pour chaque abonnement.

Pour la partie abonnement, `NkEventSystem.h:314–355` montre `AddEventCallback<T>`, qui prend un callback typé. Le motif complet se voit en considérant ensemble l'inscription et la notification.

### Singleton

`NkEventDispatcher.h:417` :

```cpp
inline NkInputQuery NkInput;
```

C'est une instance globale nommée, utilisable directement par le programme.

**Nuance à ne pas manquer :** le commentaire la qualifie de « stateless », mais `NkInputQuery` contient quand même des pointeurs vers `NkEventSystem` et `NkGamepadSystem` (`mEventSystem`, `mGamepadSystem`, lignes 397–400 environ). L'idée du cours n'est pas que l'objet ne contient littéralement aucun octet d'état. Il ne conserve pas lui-même le snapshot mutable des touches et de la souris ; il sert d'accès de requête vers les systèmes injectés. Les commentaires des lignes 407–415 exposent cette intention, le fallback quand les pointeurs ne sont pas initialisés et la disponibilité globale.

Cette distinction est très utile pour l'exercice 6 : même un Singleton conçu comme accès de lecture crée une dépendance globale qu'il faut rendre explicite dans les tests.

### Adaptateur

`NkGuiCanvasBackend.h:213` :

```cpp
void Submit(const nkentseu::nkgui::NkGuiDrawList &dl,
            nkentseu::uint32 fbW, nkentseu::uint32 fbH) {
```

Le backend reçoit une `NkGuiDrawList`. Dans le corps, il utilise des commandes de `mRenderer`, par exemple `SetClip` et `SetBlendMode`, puis soumet les sommets avec `DrawVertices` (autour de la ligne 455). Il traduit donc le format de dessin de NKGui en opérations de l'interface de renderer NKCanvas.

La preuve la plus convaincante est le code de traduction, pas uniquement le nom du fichier.

### Composite

`NkSprite.h:40` :

```cpp
class NkSprite : public NkTransformable, public NkDrawable {
```

Le sprite est à la fois transformable et dessinable. Le système de dessin reçoit un état de rendu ; le sprite doit composer cet état avec sa transformation. Les commentaires de `NkSprite.h:16–18` signalent explicitement un ancien défaut : le sprite jetait l'état reçu et ne pouvait donc pas devenir correctement l'enfant d'un objet transformé. Le comportement corrigé est un exemple très concret de propagation dans un composite.

Pour la preuve active, associe cette classe à `NkTransformable.h:27–31` (exemple d'appel et composition) et au contrat `NkDrawable.h`.

### Commande — le motif absent ou seulement approché

Le kit contient des noms proches, mais ils ne suffisent pas à établir un motif Commande général complet :

- `NkEventDispatcher.h:642` définit `NkActionCommand`. La structure conserve un nom, un code d'entrée et des propriétés de répétition. Le `NkActionManager` enregistre séparément les handlers (`CreateAction`) et les liaisons physiques (`AddCommand`, lignes 919–927). C'est un système d'actions pilotées par les entrées, mais le code visible ne montre pas chaque action comme un objet autonome possédant son propre `Execute` et une opération `Undo`.
- `NKGui/Doc/NkGuiCommandes.h:82–88` définit `NkGuiCommandeDite`, qui contient un identifiant, un libellé, un raccourci, un pointeur de fonction `NkActionFn` et un pointeur utilisateur. C'est une représentation plus proche d'une commande callback, mais l'énumérateur de commandes décrit les commandes du document et laisse l'appelant les transformer en commandes de son hôte (lignes 233–242). Cette structure ne fournit pas à elle seule un cycle commun `Execute`/`Undo`.
- `NkGui/Core/NkGuiDrawList.h:49–56` définit `NkGuiDrawCmd`. Il décrit une commande de dessin dans une liste (type, plage d'indices, texture, zone de découpe, mode de fusion). C'est une donnée de rendu que le backend interprète ; ce n'est pas nécessairement une action métier autonome à exécuter, stocker et annuler.
- `NkThreading/NkFuture.h:889–923` contient un exemple `AsyncTask` avec `Execute()`, mais la grande section d'exemple est à l'intérieur d'un commentaire qui se termine à la ligne 929. Il faut donc écrire **COMMENTAIRE SEUL**, jamais présenter cette classe comme du code compilé du kit.

Conclusion rigoureuse : les en-têtes contiennent plusieurs représentations proches du mot « commande », dont certaines portent un callback, mais cela ne prouve pas l'existence d'un motif Commande général où une action est encapsulée avec un cycle d'exécution, de stockage/rejeu et éventuellement d'annulation. Les meilleurs rapprochements sont `NkActionCommand` + `NkActionManager`, `NkGuiCommandeDite`, `NkGuiDrawCmd` et l'exemple commenté `AsyncTask`. Décris exactement ce que chaque type fait et ce qui lui manque au regard de la définition donnée dans le Sprint.

## 4.4 Modèle de rédaction pour `motifs.txt`

Ce modèle sert de squelette. Vérifie à nouveau tes lignes dans ton propre exemplaire du kit avant de remettre le fichier.

```text
Stratégie :
NKCanvas/Renderer/Core/NkIRenderer2D.h:46
class NkIRenderer2D {
Cette interface donne un contrat commun à plusieurs backends concrets.

Fabrique :
NKCanvas/Renderer/Core/NkRenderer2DFactory.h:36
static NkIRenderer2D *Create(NkIGraphicsContext *ctx);
La fabrique expose le type abstrait et centralise la création. Le corps de Create est dans la bibliothèque compilée, pas dans cet en-tête.

Façade :
NKCanvas/Renderer/Targets/NkRenderTarget.h:48
class NkRenderTarget {
La cible simplifie l'accès au rendu courant par Clear, Draw et Display, tout en exposant aussi des accès avancés.

Patron de méthode :
NKCanvas/App/NkCanvasApp.h:202
[Recopier la ligne exacte de Run après vérification.]
La classe de base possède Execute et expose des crochets On... redéfinissables.

Observateur :
NKEvent/NkEventDispatcher.h:121
[Recopier la ligne exacte de la déclaration Dispatch après vérification.]
Les callbacks sont appelés par le répartiteur typé ; true consomme l'événement.

Singleton :
NKEvent/NkEventDispatcher.h:417
inline NkInputQuery NkInput;
L'instance globale donne un point d'accès commun à l'interrogation des entrées.

Adaptateur :
NKCanvas/UI/NkGuiCanvasBackend.h:213
[Recopier la ligne exacte de Submit après vérification.]
Le backend traduit une NkGuiDrawList en appels NkIRenderer2D.

Composite :
NKCanvas/Renderer/Resources/NkSprite.h:40
class NkSprite : public NkTransformable, public NkDrawable {
Le sprite combine le drawable et le transformable et doit composer l'état reçu.

Commande :
NKThreading/NkFuture.h:889–929 — COMMENTAIRE SEUL ; approximations actives : NkActionCommand et NkGuiDrawCmd.
Le kit ne montre pas ici une commande métier complète, exécutable et annulable. AsyncTask::Execute est un exemple commenté, non une implémentation active.
```

Le professeur demande neuf paragraphes et, sous chaque étiquette, fichier et ligne. Pour `Commande :`, indique explicitement l'absence, l'endroit où tu as cherché et l'approximation la plus proche. Ne laisse pas croire qu'une ligne commentée prouve une implémentation.

---

# 5. Exercice 2 — L'interface de la stratégie

**Fichier à rendre :** `ani-2053/chapitre-08/exo2-l_interface_de_la_strategie/strategie.txt`  
**Étiquettes exactes :** `Virtuelles pures :`, `Dorsaux :`, `Ce que chacun écrit :`, `Le coût :`.

## 5.1 Ce qu'on cherche à mesurer

Une interface de stratégie est un contrat commun. Chaque backend concret doit réaliser les opérations qui restent abstraites dans l'interface ou dans sa classe de base.

L'exercice te demande deux mesures différentes :

1. combien de méthodes virtuelles pures `NkIRenderer2D` impose ;
2. combien de méthodes chacun des backends redéfinit réellement dans son propre en-tête.

Pourquoi deux mesures ? Parce que le coût d'un backend n'est pas forcément égal au nombre de méthodes pures de l'interface : une classe intermédiaire peut déjà en implémenter beaucoup. C'est exactement ce qui se produit ici avec `NkBatchRenderer2D`.

## 5.2 Résultat statique vérifié : `NkIRenderer2D`

Fichier : `NKCanvas/Renderer/Core/NkIRenderer2D.h`, classe ouverte à la ligne 46.

**Compte des méthodes virtuelles pures : 30.**

Liste pour contrôler ton propre comptage :

1. `Initialize`
2. `Shutdown`
3. `IsValid`
4. `Begin`
5. `End`
6. `IsInFrame`
7. `Flush`
8. `Clear`
9. `SetView`
10. `GetView`
11. `GetDefaultView`
12. `SetViewport`
13. `GetViewport`
14. `SetBlendMode`
15. `GetBlendMode`
16. `Draw(const NkSprite&)`
17. `Draw(const NkText&)`
18. `DrawPoint`
19. `DrawLine`
20. `DrawRect`
21. `DrawFilledRect`
22. `DrawCircle`
23. `DrawFilledCircle`
24. `DrawTriangle`
25. `DrawFilledTriangle`
26. `DrawVertices`
27. `GetStats`
28. `ResetStats`
29. `MapPixelToCoords`
30. `MapCoordsToPixel`.

Tu peux vérifier avec `rg -n "= 0;" include/NKCanvas/Renderer/Core/NkIRenderer2D.h`, mais ne compte pas aveuglément toute sortie de recherche : il faut vérifier que chaque ligne appartient bien à la classe `NkIRenderer2D`. Dans les premières lignes du fichier, une méthode pure peut appartenir à une autre classe, par exemple `NkIDrawable2D`, et ne doit pas entrer dans le total de l'interface.

## 5.3 Méthodes virtuelles qui ont un corps

L'interface fournit aussi des comportements par défaut. Parmi les méthodes virtuelles non pures avec un corps, on observe notamment :

- `ResetView`
- `IsViewCustom`
- `SetResizePolicy`
- `GetResizePolicy`
- `GetDesignSize`
- `OnResize`
- `SetClip`
- `PopClip`
- `ResetClip`
- `HasClip`
- `GetClip`
- `Draw(const NkIDrawable2D&)`
- `DrawRectOutline`
- `DrawCircleOutline`
- `DrawTexturedRect`.

Cela donne **15 méthodes virtuelles opérationnelles avec corps**. Le destructeur virtuel `~NkIRenderer2D()` a lui aussi une définition (`= default`) ; si tu comptes absolument toute déclaration virtuelle possédant un corps, annonce **15 méthodes de service, plus le destructeur virtuel**. Énonce ta convention de comptage pour que le correcteur sache ce que tu as inclus.

Une méthode virtuelle avec corps n'est pas automatiquement une méthode que chaque backend doit réécrire. Elle fournit déjà un comportement hérité.

## 5.4 Les six dorsaux présents dans le kit

Les en-têtes présents sous `NKCanvas/Backend/` sont :

- `Software/NkSoftwareRenderer2D.h`
- `OpenGL/NkOpenGLRenderer2D.h`
- `Vulkan/NkVulkanRenderer2D.h`
- `DirectX/NkDX11Renderer2D.h`
- `DirectX/NkDX12Renderer2D.h`
- `Metal/NkMetalRenderer2D.h`.

**Pourquoi ne pas recopier simplement le commentaire de `NkIRenderer2D.h` ?** Parce qu'un commentaire peut ne pas avoir été mis à jour. Le dossier contient six fichiers, même si certains ne sont utilisables que sur certaines plateformes ou sous certaines macros.

Nuances :

- `NkMetalRenderer2D` est sous condition de compilation MacOS/iOS ; sa présence dans le dossier ne signifie pas qu'il est actif sous Windows.
- `NkVulkanRenderer2D.h` possède deux branches conditionnelles : une vraie déclaration lorsque les en-têtes Vulkan sont disponibles, et une variante de repli sinon. Tu ne dois compter qu'une seule branche active à la fois.
- Les classes concrètes héritent toutes directement de `NkBatchRenderer2D`, qui hérite de `NkIRenderer2D` (`NkBatchRenderer2D.h:31`).

## 5.5 Nombre de redéfinitions visibles dans chaque en-tête

En comptant les méthodes déclarées avec `override` dans la classe de chaque backend, sans compter son destructeur et sans compter deux fois les deux branches conditionnelles de Vulkan :

| Backend | Classe mère directe | Redéfinitions de méthodes dans l'en-tête |
|---|---|---:|
| Software | `NkBatchRenderer2D` | 9 |
| OpenGL | `NkBatchRenderer2D` | 9 |
| Vulkan (branche avec en-têtes Vulkan) | `NkBatchRenderer2D` | 8 |
| DirectX 11 | `NkBatchRenderer2D` | 8 |
| DirectX 12 | `NkBatchRenderer2D` | 8 |
| Metal | `NkBatchRenderer2D` | 9 |

Pourquoi ces comptes ne sont-ils pas 30 ? `NkBatchRenderer2D` prend déjà en charge une partie du contrat commun : gestion des frames, batching, vues et opérations communes. Les backends concrets écrivent surtout ce qui dépend du backend : initialisation, effacement, début/fin spécifiques, soumission des lots, projection et éventuellement scissor. Software expose aussi un `Draw(const NkSprite&)` supplémentaire dans son en-tête.

**Convention déclarée :** ces nombres comptent les fonctions redéfinies déclarées directement dans chaque en-tête de backend, sans destructeur. Pour ton rendu, refais le compte avec `rg -n "override"`, ouvre chaque classe et vérifie chaque ligne. N'inclus ni les fonctions héritées de `NkBatchRenderer2D`, ni les fonctions d'une branche Vulkan inactive.

## 5.6 Deuxième manière de vérifier le compte

Le correcteur demande explicitement une deuxième vérification. Deux méthodes possibles :

- Première méthode : lire chaque ligne `= 0;` à l'intérieur de `NkIRenderer2D` et dresser la liste des trente fonctions.
- Deuxième méthode : refaire le parcours visuel depuis le début de la classe, en regroupant par sections (cycle de vie, frame, view, viewport, blend, primitives, stats, coordonnées), puis comparer le nombre de fonctions de chaque section à la liste précédente.

Pour les dorsaux : compte `override` avec la recherche, puis relis la déclaration complète dans le fichier et vérifie la classe mère. La recherche seule ne suffit pas si une signature se poursuit sur la ligne suivante ou si plusieurs branches `#if` définissent la classe.

## 5.7 Comment calculer le coût d'un backend supplémentaire

Ne réponds pas simplement : « un dorsal de plus coûte 30 méthodes ». Ce serait confondre l'interface initiale et le travail restant après la classe intermédiaire.

D'après les en-têtes observés, un nouveau backend doit au minimum fournir les points de variation propres à son backend, et respecter les opérations abstraites qui ne sont pas encore implémentées dans la classe intermédiaire. Le nombre réel de déclarations de chaque backend donne une estimation concrète du travail de redéfinition, mais ce nombre dépend du backend et de ses capacités.

Le coût inclut aussi :

- implémenter correctement les méthodes, pas seulement écrire leurs signatures ;
- respecter la gestion des ressources et le cycle de vie du contexte ;
- gérer les états graphiques (blend, clip/scissor, projection) ;
- construire et soumettre les lots de sommets/indices ;
- vérifier que les méthodes par défaut de la classe de base conviennent au nouveau backend ;
- tester sur le système et le pilote ciblés.

La conclusion pertinente est : l'interface de stratégie garantit un contrat commun, tandis que `NkBatchRenderer2D` mutualise du travail ; le coût d'un dorsal se mesure sur ce qui reste spécifique, et non en recopiant simplement le nombre de virtuelles pures.

## 5.8 Modèle de `strategie.txt`

```text
Virtuelles pures :
30 méthodes. J'ai compté uniquement les fonctions `= 0` appartenant à NkIRenderer2D, et non celles d'une autre classe ou d'un exemple commenté. J'ai vérifié le compte en relisant les sections de l'interface. Les méthodes virtuelles avec corps sont comptées à part : 15 méthodes de service, plus le destructeur virtuel si on inclut ce dernier.

Dorsaux :
Software : include/NKCanvas/Backend/Software/NkSoftwareRenderer2D.h
OpenGL : include/NKCanvas/Backend/OpenGL/NkOpenGLRenderer2D.h
Vulkan : include/NKCanvas/Backend/Vulkan/NkVulkanRenderer2D.h
DirectX 11 : include/NKCanvas/Backend/DirectX/NkDX11Renderer2D.h
DirectX 12 : include/NKCanvas/Backend/DirectX/NkDX12Renderer2D.h
Metal : include/NKCanvas/Backend/Metal/NkMetalRenderer2D.h
J'ai listé les fichiers présents dans le dossier, au lieu de reprendre seulement le commentaire de l'interface. J'ai tenu compte des macros de plateforme et de la branche Vulkan active.

Ce que chacun écrit :
NkSoftwareRenderer2D hérite de NkBatchRenderer2D et redéfinit 9 méthodes (sans le destructeur).
NkOpenGLRenderer2D hérite de NkBatchRenderer2D et redéfinit 9 méthodes.
NkVulkanRenderer2D hérite de NkBatchRenderer2D et redéfinit 8 méthodes dans la branche avec en-têtes Vulkan.
NkDX11Renderer2D hérite de NkBatchRenderer2D et redéfinit 8 méthodes.
NkDX12Renderer2D hérite de NkBatchRenderer2D et redéfinit 8 méthodes.
NkMetalRenderer2D hérite de NkBatchRenderer2D et redéfinit 9 méthodes.

Le coût :
Un nouveau dorsal ne réécrit pas les 30 opérations abstraites une par une : NkBatchRenderer2D en implémente déjà une partie. Le travail restant est propre au backend et se voit dans les méthodes `override` de chaque en-tête. Il faut aussi implémenter le comportement réel, gérer le contexte/les ressources et tester le backend sur sa plateforme. J'ai exclu les destructeurs de mes comptes et je n'ai pas compté les méthodes héritées.
```

**À faire avant dépôt :** vérifie les six nombres de `override` sur ton installation. Si ta méthode de comptage est différente (par exemple inclure les destructeurs), annonce-la et applique-la uniformément.

---

# 6. Exercice 3 — La fabrique en un coup d'œil

**Fichier à rendre :** `ani-2053/chapitre-08/exo3-la_fabrique_en_un_coup_d_oeil/fabrique.txt`  
**Étiquettes exactes :** `Recherche :`, `Hors de son dossier :`, `Conclusion :`.

## 6.1 Question centrale

Une fabrique est-elle réellement le seul endroit qui connaît les classes concrètes ? Le test demandé prend une classe précise, `NkOpenGLRenderer2D`, et compte ses mentions en dehors de son dossier.

Ce n'est pas un exercice de simple recherche de texte. Il faut classer chaque occurrence :

- code actif : déclaration, construction, appel, type réellement utilisé ;
- commentaire : explication, exemple ou documentation ;
- fichier propriétaire : le dossier où la classe concrète est censée être définie.

Une occurrence dans un commentaire ne signifie pas que le code dépend réellement de la classe.

## 6.2 Commande de recherche

Depuis `Canvas/` :

```powershell
rg -n --glob "*.h" "NkOpenGLRenderer2D" include
```

Pour compter les fichiers uniques :

```powershell
rg -l --glob "*.h" "NkOpenGLRenderer2D" include
```

Garde les deux sorties dans ton carnet. La première donne les lignes, la seconde les chemins uniques. Ne compte pas les occurrences comme si elles étaient toutes des fichiers différents.

## 6.3 Occurrences repérées dans la version inspectée

Le nom apparaît dans le fichier propriétaire `NKCanvas/Backend/OpenGL/NkOpenGLRenderer2D.h`, et dans plusieurs autres fichiers. Les mentions extérieures principales observées sont :

| Fichier hors du dossier OpenGL | Lignes repérées | Nature de la mention |
|---|---:|---|
| `NKGui/Core/NkGuiDrawListRaster.h` | 35 | commentaire expliquant les facteurs de mélange utilisés pour s'aligner sur le comportement OpenGL |
| `NKCanvas/Renderer/Core/NkRenderer2D.h` | 19 | commentaire / documentation |
| `NKCanvas/Renderer/Core/NkIRenderer2D.h` | 15 | commentaire / documentation |
| `NKCanvas/Renderer/Resources/NkTextureBackend.h` | 22, 24–28 | commentaires / exemples de backend |

Dans la recherche complète, le fichier propriétaire contient aussi le nom dans son en-tête, sa déclaration de classe, son constructeur et son destructeur. Le comptage des **fichiers uniques** est différent du nombre d'occurrences.

**Contrôle crucial :** réexécute les deux commandes sur ton kit et classe chaque résultat ligne par ligne. Les occurrences listées ci-dessus hors du dossier du backend sont des commentaires ; elles ne sont pas des appels ni des constructions d'objets.

## 6.4 Pourquoi ouvrir `NkRenderer2DFactory.h` ?

Le fichier `NKCanvas/Renderer/Core/NkRenderer2DFactory.h` expose `Create(NkIGraphicsContext*)` et retourne `NkIRenderer2D*`. Dans cet en-tête, la fabrique expose l'interface abstraite, pas le nom `NkOpenGLRenderer2D`.

C'est cohérent avec l'objectif de la fabrique : le client demande un renderer sans connaître la classe concrète. Mais l'en-tête ne contient pas le corps de `Create`. La sélection concrète et le mécanisme d'allocation sont dans la bibliothèque compilée.

## 6.5 Quelle conclusion écrire ?

La conclusion correcte n'est ni « le nom n'apparaît nulle part ailleurs » si la recherche montre des commentaires, ni « le code client dépend du backend » simplement parce que le nom est mentionné dans la documentation.

Tu dois plutôt dire :

- le nom de la classe concrète apparaît dans plusieurs fichiers en dehors de son dossier ;
- les lignes repérées sont des commentaires, donc elles n'établissent pas une dépendance du code actif ;
- l'en-tête de la fabrique expose l'interface `NkIRenderer2D` et ne nomme pas les dorsaux ;
- les corps de la fabrique ne sont pas visibles ici, donc la conclusion porte sur les en-têtes inspectés.

L'exercice vérifie si tu sais distinguer une **mention textuelle** d'une **dépendance réelle**.

## 6.6 Modèle de `fabrique.txt`

```text
Recherche :
Commande exécutée depuis Canvas : rg -n --glob "*.h" "NkOpenGLRenderer2D" include
La liste des fichiers uniques a été vérifiée séparément avec rg -l. Le nom apparaît dans cinq fichiers uniques : le fichier de son backend et quatre fichiers extérieurs que j'ai classés ci-dessous.

Hors de son dossier :
NKGui/Core/NkGuiDrawListRaster.h:35 — commentaire qui documente les facteurs de mélange du backend OpenGL.
NKCanvas/Renderer/Core/NkRenderer2D.h:19 — commentaire.
NKCanvas/Renderer/Core/NkIRenderer2D.h:15 — commentaire.
NKCanvas/Renderer/Resources/NkTextureBackend.h:22 et 24–28 — commentaires / exemples.
J'ai ouvert chaque ligne pour vérifier qu'il ne s'agissait pas d'une construction ou d'un appel actif.

Conclusion :
NkRenderer2DFactory.h expose Create comme une fonction renvoyant NkIRenderer2D*, et ne nomme pas NkOpenGLRenderer2D dans son interface publique. Les mentions extérieures que j'ai trouvées sont des commentaires, pas des appels actifs. Cela soutient l'idée que la fabrique centralise le choix concret dans son implémentation compilée. Je ne peux pas décrire le corps de Create à partir de cet en-tête seul.
```

**Important :** le nombre exact de fichiers et les lignes doivent provenir de ta sortie `rg` locale. Ne copie pas un compte si ton kit ou ta commande ne donnent pas le même résultat.

# 7. Exercice 4 — Les crochets du patron

**Fichiers à rendre :**

- `ani-2053/chapitre-08/exo4-les_crochets_du_patron/crochets.cpp`
- `ani-2053/chapitre-08/exo4-les_crochets_du_patron/crochets.txt`

**Étiquettes exactes du fichier texte :** `Les crochets :`, `L'ordre mesuré :`, `Les surprises :`, `Debug et Release :`.

## 7.1 Que signifie « crochet » ?

Un crochet (en anglais *hook*) est une méthode de la classe de base que la classe dérivée peut redéfinir. La classe de base décide quand elle l'appelle. Le programmeur de l'application fournit le comportement personnalisé, mais ne réécrit pas l'intégralité du cycle de vie.

Dans `NkCanvasApp`, les hooks commencent par `On...`. La classe de base possède une méthode privée `Execute`, et la méthode statique `Run<T>` construit ton application avant de déléguer à cette exécution.

L'exercice te demande de faire deux travaux complémentaires :

1. lire et lister toutes les méthodes virtuelles proposées comme hooks, avec leurs lignes et les promesses de leurs commentaires ;
2. écrire une application qui redéfinit chacun des hooks et journalise quand chacun est appelé.

Le journal est nécessaire parce que le corps privé du cycle de vie n'est pas fourni dans le kit source sous forme de `.cpp`.

## 7.2 Liste des douze hooks dans `NkCanvasApp.h`

Fichier : `NKCanvas/App/NkCanvasApp.h`.

| Ligne | Crochet | Rôle / promesse visible dans l'en-tête |
|---:|---|---|
| 249 | `OnCommandLine(args)` | Appelé avant la création de la fenêtre ; une valeur retournée arrête le programme avec ce code. |
| 255 | `OnInit()` | Appelé lorsque la fenêtre et la cible de rendu existent ; `false` abandonne l'initialisation. |
| 259 | `OnUpdate(deltaTime)` | Étape de mise à jour de l'application. |
| 262 | `OnRender(target)` | Étape de dessin de l'application. |
| 265 | `OnShutdown()` | Étape de nettoyage / arrêt de l'application. |
| 270 | `OnEvent(event)` | Flux brut des événements ; `true` consomme et arrête la chaîne à ce niveau, `false` laisse la coquille faire son traitement typé. |
| 277 | `OnPointer(pointer)` | Geste unifié souris + doigt ; le commentaire dit qu'il dérive de `OnEvent`, et non d'un second abonnement. |
| 282 | `OnKeyPress(event)` | Crochet typé pour une touche pressée. |
| 291 | `OnLayout(layout)` | Appelé lorsque taille, zone sûre ou densité changent ; le commentaire promet au moins un appel avant la première frame. |
| 314 | `OnCloseRequested()` | Demande de fermeture ; `false` refuse la fermeture, le défaut `true` accepte. |
| 321 | `OnPause()` | Appelé lorsque l'application part en arrière-plan ou perd le focus. |
| 323 | `OnResume()` | Appelé au retour après pause. |

Le destructeur virtuel de `NkCanvasApp` n'est pas un crochet métier de ce cycle de vie : ne le compte pas parmi ces douze hooks.

## 7.3 L'ordre de boucle fourni par l'énoncé

L'exercice fournit cet extrait comme cœur de la boucle :

```cpp
OnUpdate(deltaTime);
mTarget->Clear(mConfig.clearColor);
OnRender(*mTarget);
mTarget->Display();
```

Il faut bien comprendre chaque ligne :

1. `OnUpdate` met à jour l'état du jeu ;
2. `Clear` efface la cible avec la couleur configurée ;
3. `OnRender` dessine la scène ;
4. `Display` présente le résultat à l'écran / finalise la cible.

Ce passage est donné dans la consigne pédagogique. Ce n'est pas une preuve que tu as ouvert le corps de `Execute` dans le kit. Le corps complet de `Execute` est déclaré dans l'en-tête mais son implémentation est fournie par la bibliothèque compilée.

## 7.4 Comment construire le journal

Une application fenêtre n'a pas forcément de console attachée. La consigne précise donc d'écrire dans un fichier.

Pour chaque crochet, journalise au minimum :

- un numéro d'ordre global qui augmente à chaque appel ;
- le nom du crochet ;
- l'indice de frame suivi par ton programme ;
- `Time()`.

Exemple de format de journal (format illustratif, pas un résultat réel) :

```text
001 | OnCommandLine | frame=0 | time=0.000
002 | OnInit        | frame=0 | time=0.000
003 | OnLayout      | frame=0 | time=0.000
004 | OnUpdate      | frame=1 | time=0.016
005 | OnRender      | frame=1 | time=0.016
006 | OnUpdate      | frame=2 | time=0.032
007 | OnRender      | frame=2 | time=0.032
```

Ces nombres sont fictifs et montrent uniquement la forme du journal. Ne les recopie pas dans ton compte rendu.

Le compteur de frames doit être un compteur que ton programme contrôle. Il ne faut pas supposer que l'indice privé `mFrameIndex` est accessible depuis la classe dérivée.

### Squelette conceptuel

```cpp
class MonJeu : public nkentseu::renderer::NkCanvasApp {
public:
    // Ouvre le journal ici ou dans OnInit selon le comportement souhaité.
    // Chaque override appelle une méthode Log("NomDuHook").

protected:
    NkOptional<int> OnCommandLine(const NkVector<NkString>& args) override;
    bool OnInit() override;
    void OnUpdate(float32 deltaTime) override;
    void OnRender(NkRenderWindow& target) override;
    void OnShutdown() override;
    bool OnEvent(const NkEvent& event) override;
    bool OnPointer(const NkPointer& pointer) override;
    bool OnKeyPress(const NkKeyPressEvent& event) override;
    void OnLayout(const NkLayoutInfo& layout) override;
    bool OnCloseRequested() override;
    void OnPause() override;
    void OnResume() override;
};
```

Ce squelette décrit les signatures ; pour compiler, utilise exactement les types qualifiés et les includes du kit. Le point d'entrée fourni par la consigne est :

```cpp
int nkmain(const NkEntryState &state) {
    return renderer::NkCanvasApp::Run<MonJeu>(state);
}
```

Pour arrêter le programme seul, appelle `Quit()` après quelques images. La documentation visible du kit précise que `Quit()` demande un arrêt propre à la fin de la frame courante.

## 7.5 Pourquoi certains hooks peuvent ne pas apparaître

Un crochet qui n'apparaît pas dans ton journal n'est pas automatiquement cassé. Il peut simplement ne pas avoir été déclenché.

- `OnUpdate` et `OnRender` sont attendus à chaque frame normale.
- `OnLayout` est attendu au moins une fois avant la première frame selon le commentaire de l'en-tête.
- `OnKeyPress` exige un appui de touche.
- `OnPointer` exige un geste souris/doigt.
- `OnCloseRequested` exige une demande de fermeture : croix, Alt+F4 ou autre geste système.
- `OnPause` et `OnResume` exigent le changement de focus / arrière-plan correspondant.
- `OnEvent` dépend de la livraison d'événements au programme.
- `OnCommandLine` doit être examiné séparément du cycle de fenêtre, puisqu'il est décrit comme appelé avant celle-ci.

La consigne te demande de lancer sans toucher à la fenêtre : cela limite les événements manuels et permet d'observer le cycle normal. Si un crochet événementiel n'apparaît pas, explique quel événement aurait dû le déclencher et pourquoi tu ne l'as pas provoqué.

## 7.6 Debug et Release : que comparer ?

Construis et lance séparément les deux configurations. Ne suppose pas que leurs temps seront identiques.

À comparer :

- ordre relatif des hooks du cycle normal ;
- nombre de frames avant `Quit()` ;
- présence ou absence des hooks conditionnels ;
- durée `Time()` de chaque frame ;
- éventuel effet des optimisations ou du rythme de boucle.

Une divergence de durée entre Debug et Release n'est pas automatiquement un bug. Une divergence d'ordre ou un crochet attendu manquant demande une enquête.

La consigne précise de limiter la journalisation de `OnUpdate` et `OnRender` aux premières frames, sinon le journal peut devenir énorme. Tu peux conserver l'appel à `Log` seulement si ton compteur de frame est inférieur à une petite limite.

## 7.7 Les trois surprises : comment les choisir ?

Ne fabrique pas trois surprises. Choisis trois choses réellement inattendues dans ton journal, par exemple :

- `OnLayout` arrive avant le premier `OnUpdate` alors que tu ne l'avais pas prévu ;
- un hook événementiel n'apparaît pas parce que tu n'as déclenché aucun événement utilisateur ;
- l'heure de `OnInit` ou la façon dont `OnCommandLine` précède la fenêtre ne correspond pas à ton hypothèse ;
- les temps mesurés diffèrent entre Debug et Release.

Pour chaque surprise, écris :

1. ce que tu pensais voir ;
2. ce que le journal montre réellement ;
3. quelle condition ou quel ordre peut expliquer l'écart.

## 7.8 Modèle de `crochets.txt`

```text
Les crochets :
OnCommandLine — NkCanvas/App/NkCanvasApp.h:249 — appelé avant la création de fenêtre.
OnInit — NkCanvas/App/NkCanvasApp.h:255 — fenêtre et cible de rendu existent.
OnUpdate — NkCanvas/App/NkCanvasApp.h:259 — mise à jour.
OnRender — NkCanvas/App/NkCanvasApp.h:262 — rendu.
OnShutdown — NkCanvas/App/NkCanvasApp.h:265 — arrêt.
OnEvent — NkCanvas/App/NkCanvasApp.h:270 — flux brut, true consomme.
OnPointer — NkCanvas/App/NkCanvasApp.h:277 — geste souris/doigt dérivé du flux événementiel.
OnKeyPress — NkCanvas/App/NkCanvasApp.h:282 — appui typé.
OnLayout — NkCanvas/App/NkCanvasApp.h:291 — taille / zone sûre / densité.
OnCloseRequested — NkCanvas/App/NkCanvasApp.h:314 — demande de fermeture, false refuse.
OnPause — NkCanvas/App/NkCanvasApp.h:321 — passage en arrière-plan / perte de focus.
OnResume — NkCanvas/App/NkCanvasApp.h:323 — retour.

L'ordre mesuré :
[Recopier le journal réel du lancement, pas un ordre supposé.]

Les surprises :
[Décrire trois écarts réels entre tes attentes et le journal.]

Debug et Release :
[Comparer tes deux journaux réels, leurs ordres, nombres d'appels et temps.]
```

---

# 8. Exercice 5 — Push ou Pull

**Fichier à rendre :** `ani-2053/chapitre-08/exo5-push_ou_pull/push_pull.txt`  
**Étiquettes exactes :** `Situations :`, `Les deux bogues :`.

## 8.1 La règle de décision

Pose-toi cette question : « Est-ce que je veux être averti qu'une action vient d'arriver, ou est-ce que je veux connaître un état qui peut rester vrai pendant plusieurs frames ? »

- Action ponctuelle : généralement Push.
- État durable à interroger : généralement Pull.

Une même situation peut être décrite par les deux mécanismes. Exemple : on peut recevoir un événement quand la souris bouge (Push) ou demander sa position actuelle (Pull). Il faut choisir en fonction du besoin exact, pas simplement du nom de l'objet.

## 8.2 Les six situations de l'exercice

| Situation | Modèle recommandé | Pourquoi ? | Outil concret du kit |
|---|---|---|---|
| Le joueur maintient la flèche droite | Pull | Le déplacement doit rester actif tant que la touche est maintenue, pas seulement à l'instant du premier appui. | `NkInput.IsKeyDown(NkKey::NK_RIGHT)` dans `NKEvent/NkEventDispatcher.h` (méthode `IsKeyDown`, autour de la ligne 273 ; global `NkInput`, ligne 417). |
| Le joueur appuie sur Échap | Push | C'est une action ponctuelle : on réagit à l'appui initial, par exemple ouvrir le menu pause une seule fois. | Hook `OnKeyPress` dans `NKCanvas/App/NkCanvasApp.h:282`, événement `NkKeyPressEvent` dans `NKEvent/NkKeyboardEvent.h:972`. |
| On veut la position actuelle de la souris | Pull | On veut un état courant (x et y), même sans mouvement récent. | `NkInput.MouseX()` / `MouseY()` dans `NKEvent/NkEventDispatcher.h` (autour des lignes 308–310). |
| Un fichier est déposé sur la fenêtre | Push | Le dépôt est un événement qui arrive à un instant précis. | `NkDropFileEvent` dans `NKEvent/NkDropEvent.h:373`. |
| La fenêtre est redimensionnée | Push | On réagit au changement de dimensions lorsqu'il survient. | `NkWindowResizeEvent` dans `NKEvent/NkWindowEvent.h:453`. Pour le layout calculé côté application, le crochet `OnLayout` de `NkCanvasApp.h:291` est aussi pertinent, mais ce n'est pas le même niveau d'information. |
| Le joueur double-clique | Push | Le double-clic est une action ponctuelle détectée comme événement. | `NkMouseDoubleClickEvent` dans `NKEvent/NkMouseEvent.h:684`. |

Vérifie les numéros de lignes et les noms dans ton propre dossier avec `rg -n` avant de les déposer. Les repères ci-dessus correspondent au kit inspecté.

## 8.3 Pourquoi les situations ne se traitent pas toutes de la même façon ?

### Touche maintenue : Pull

Si tu te contentes du premier événement `KeyPress`, tu sais que le joueur a commencé à appuyer, mais tu ne disposes pas automatiquement d'une action continue pour chaque frame. Le code peut donc déplacer le personnage une seule fois ou arrêter le déplacement alors que la touche est toujours tenue.

### Échap : Push

Si tu interroges `IsKeyDown(Escape)` à chaque frame et que tu exécutes « basculer la pause » tant que la touche est enfoncée, tu peux basculer plusieurs fois : pause, reprise, pause, reprise. L'action doit être déclenchée à la transition d'appui, ou être protégée par une logique de front.

### Position souris : Pull

Un événement de mouvement te dit qu'un mouvement a eu lieu. Mais si tu veux simplement lire la position courante, il vaut mieux interroger `MouseX()` et `MouseY()`. Tu obtiens l'état présent plutôt que de reconstruire la position à partir d'une série d'événements.

### Dépôt de fichier : Push

Le fichier déposé est un événement. Le programme doit être prévenu pour traiter le chemin/les données reçus. Une interrogation permanente n'a pas de sens sans une API d'état explicitement conçue pour cela.

### Redimensionnement : Push

Le changement de taille est notifié. Il existe cependant deux niveaux :

- `NkWindowResizeEvent` décrit le changement de fenêtre et ses dimensions ;
- `OnLayout` reçoit l'information de layout résultante : taille, zone sûre et densité.

Choisis l'outil qui correspond à la question du programme : dimensions natives ou layout déjà calculé.

### Double-clic : Push

Le double-clic est un événement spécifique. Le commentaire du type indique qu'il est détecté par l'OS. Il ne faut pas le reconstruire naïvement en interrogeant un bouton maintenu : ce ne serait pas la même sémantique.

## 8.4 Les deux bogues classiques

Le professeur te demande de décrire deux bogues produits par un mauvais choix. Deux exemples forts :

**Bogue A — utiliser Push pour une touche maintenue :** le système reçoit l'appui initial, déplace le personnage une fois, puis n'a plus d'information continue dans la logique de déplacement. Le personnage s'arrête trop tôt alors que la touche reste appuyée. Attention à ne pas confondre ceci avec l'auto-répétition du clavier, qui n'est pas une bonne manière de gérer un déplacement continu.

**Bogue B — utiliser Pull pour Échap :** chaque frame où Échap reste enfoncé exécute l'action « toggle pause ». Le menu s'ouvre, se ferme, puis se rouvre très rapidement ; l'action part plusieurs fois.

Autre exemple valable : ne compter que sur les événements de déplacement de souris pour avoir sa position courante peut laisser une valeur périmée lorsqu'aucun événement récent n'est arrivé.

## 8.5 Modèle de `push_pull.txt`

```text
Situations :
Flèche droite maintenue — Pull, car le déplacement dépend d'un état durable. Outil : NkInput.IsKeyDown(NkKey::NK_RIGHT), NKEvent/NkEventDispatcher.h, vérifier la ligne exacte de la méthode.
Échap pressé — Push, car le menu pause doit réagir à un appui ponctuel. Outil : OnKeyPress, NKCanvas/App/NkCanvasApp.h:282, et NkKeyPressEvent, NKEvent/NkKeyboardEvent.h:972.
Position de la souris — Pull, car je demande la position courante. Outil : NkInput.MouseX/MouseY, NKEvent/NkEventDispatcher.h.
Fichier déposé — Push, car le dépôt arrive comme événement. Outil : NkDropFileEvent, NKEvent/NkDropEvent.h:373.
Redimensionnement — Push, car le changement de dimensions survient à un instant donné. Outil : NkWindowResizeEvent, NKEvent/NkWindowEvent.h:453.
Double-clic — Push, car le double-clic est un événement ponctuel. Outil : NkMouseDoubleClickEvent, NKEvent/NkMouseEvent.h:684.

Les deux bogues :
Si j'utilise seulement l'événement d'appui pour la flèche droite, le déplacement peut ne se produire qu'une fois et s'arrêter alors que la touche est maintenue.
Si j'interroge Échap et bascule le menu à chaque frame, un appui maintenu déclenche plusieurs basculements. Le bon mécanisme est l'événement d'appui initial ou une détection explicite du front.
```

---

# 9. Exercice 6 — Le Singleton et le test

**Fichiers à rendre :** `ani-2053/chapitre-08/exo6-le_singleton_et_le_test/banc.cpp` et `banc.txt`  
**Étiquettes exactes :** `Tester la version directe :`, `La version testable :`, `Le banc :`, `Sans fenêtre :`.

## 9.1 Le problème à démontrer

L'énoncé donne une instance globale :

```cpp
inline NkInputQuery NkInput;
```

et un usage tel que :

```cpp
if (NkInput.IsKeyDown(NkKey::NK_SPACE)) {
    // ...
}
```

C'est pratique dans une application réelle. Mais si une fonction lit directement cette instance globale, elle dépend d'une ressource que le test ne choisit pas.

Imagine que la fonction décide si le personnage peut sauter :

```cpp
bool CanJumpDirect(bool onGround) {
    return onGround && NkInput.IsKeyDown(NkKey::NK_SPACE);
}
```

Cette fonction a une dépendance cachée : la valeur courante de `NkInput`. Pour contrôler le test, il faudrait maîtriser l'état du système d'entrée global, son initialisation, les événements et la fenêtre éventuelle.

## 9.2 Première version : ce qu'il faudrait pour la tester

Avant de la compiler, décris les scénarios que tu devrais pouvoir contrôler :

| Le personnage est au sol ? | Espace est pressée ? | Résultat attendu |
|---|---|---|
| oui | oui | `true` |
| oui | non | `false` |
| non | oui | `false` |
| non | non | `false` |

Pour tester la version directe, il faudrait pouvoir imposer l'état de `NkInput` pour chaque cas. Mais la fonction ne reçoit pas cet état en paramètre. Elle va le lire elle-même dans le singleton.

Le coût est donc de configurer l'environnement global du test : initialiser le système d'entrée, produire les événements appropriés, garantir l'état courant et gérer le cycle de vie. C'est beaucoup plus complexe qu'un simple test de logique.

## 9.3 Deuxième version : injecter l'information nécessaire

Sépare la règle métier de la manière de lire le clavier :

```cpp
bool CanJump(bool onGround, bool spaceDown) {
    return onGround && spaceDown;
}
```

La fonction ne lit plus `NkInput`. Elle reçoit les deux informations dont elle a besoin.

Pourquoi est-ce mieux ? Parce que le test peut choisir chaque combinaison sans créer de fenêtre, initialiser un périphérique ou modifier un état global.

La version directe peut rester dans le fichier comme demandé par l'énoncé. Il faut conserver les deux fonctions :

```cpp
bool CanJumpDirect(bool onGround) {
    return onGround && NkInput.IsKeyDown(NkKey::NK_SPACE);
}

bool CanJumpTestable(bool onGround, bool spaceDown) {
    return onGround && spaceDown;
}
```

La règle métier est la même : être au sol ET avoir espace enfoncée. La différence est que la seconde fonction reçoit la valeur externe plutôt que de la récupérer toute seule.

## 9.4 Pourquoi est-ce de l'injection de dépendance ?

La dépendance de la règle métier est « savoir si espace est pressée ». Dans la version directe, la fonction va elle-même chercher cette information dans un Singleton. Dans la version testable, l'appelant la lui fournit.

Cette technique est une forme simple d'injection de dépendance : on rend explicite ce dont la fonction a besoin.

Ce n'est pas obligatoire de passer toujours un booléen dans une vraie application. On pourrait injecter une interface `IInput`, un objet de contexte ou une fonction callable. Pour cet exercice, un booléen suffit et rend le test facile à comprendre.

## 9.5 Le banc de test : les quatre cas

Pseudocode indépendant du moteur :

```cpp
struct TestCase {
    bool onGround;
    bool spaceDown;
    bool expected;
};

TestCase cases[] = {
    { true,  true,  true  },
    { true,  false, false },
    { false, true,  false },
    { false, false, false }
};
```

Pour chaque cas :

1. appeler `CanJumpTestable(onGround, spaceDown)` ;
2. comparer au résultat attendu ;
3. écrire le résultat réel dans le journal ;
4. augmenter le compteur d'échecs si le résultat est différent.

Le nombre d'échecs est une mesure : il doit être calculé par le programme, pas décidé à l'avance.

Résultat logique attendu de la fonction pure pour ces quatre cas : `true, false, false, false`. Si la fonction est écrite comme ci-dessus, on peut démontrer par la table de vérité qu'elle devrait avoir zéro échec. Mais tu dois quand même faire tourner le banc demandé et recopier le résultat qu'il produit réellement.

## 9.6 Pourquoi `OnCommandLine` est central

La consigne précise que `OnCommandLine` est appelé avant toute fenêtre et qu'une valeur renvoyée arrête le programme avec ce code de sortie. `NkCanvasApp.h:244–249` donne cette promesse ; `Run<T>` délègue à `Execute` à la ligne 204.

Cela permet d'écrire un banc de test qui :

- démarre sans construire de fenêtre ;
- exécute ses quatre cas ;
- écrit un fichier de résultats ;
- rend un code de sortie correspondant au nombre d'échecs.

Ne confonds pas « sans fenêtre » et « aucun sous-système n'a été initialisé ». L'en-tête dit que `OnCommandLine` a lieu avant la fenêtre ; le commentaire de `NkInput` dit que les pointeurs système sont injectés par `NkSystem::Initialize()` et qu'un état factice est utilisé si le système n'est pas initialisé. Le corps de `Execute` n'étant pas visible dans l'en-tête, ne suppose pas sans test que les pointeurs sont forcément nuls à cet instant. **Le rendu de la version directe est précisément une chose à mesurer.**

Si `NkInput` n'a pas encore reçu ses systèmes, le commentaire annonce un fallback vers l'état factice et les valeurs par défaut ; pour `IsKeyDown`, cela devrait produire l'état non pressé. Mais note-le comme hypothèse dérivée du contrat, puis vérifie la sortie réelle.

## 9.7 Debug et Release

Construis et lance les deux configurations séparément. Le journal doit permettre de voir que les quatre cas sont exécutés. Le code de sortie du programme doit correspondre au nombre d'échecs calculé par le banc, selon la convention choisie par ton programme.

Ne fabrique pas un nombre d'échecs dans le texte. Copie :

- la sortie du journal ;
- le nombre d'échecs ;
- le code de sortie observé ;
- la différence entre Debug et Release, s'il y en a une.

## 9.8 Modèle de `banc.txt`

```text
Tester la version directe :
CanJumpDirect(bool onGround) lit NkInput directement. Pour tester tous les cas, il faudrait contrôler l'état du clavier visible par le singleton, initialiser/injecter le système d'entrée ou construire un environnement simulé. Cela rend le test dépendant de l'état global et de son cycle de vie.

La version testable :
CanJumpTestable(bool onGround, bool spaceDown) reçoit les deux informations dont elle a besoin et ne lit plus NkInput. La règle métier est inchangée : le personnage saute seulement s'il est au sol et si espace est pressée.

Le banc :
[Coller les résultats réels des quatre cas en Debug puis en Release, le nombre d'échecs et le code de sortie réellement retourné.]

Sans fenêtre :
[Décrire la valeur réellement observée par CanJumpDirect dans OnCommandLine. Expliquer le rôle de l'état courant de NkInput et de son fallback éventuel si les systèmes n'ont pas encore été injectés. Ne pas prétendre que c'est faux ou vrai sans avoir relevé le résultat.]
```

---
# 10. Exercice 7 — Un second pont

**Fichier à rendre :** `ani-2053/chapitre-08/exo7-un_second_pont/pont.txt`  
**Étiquettes exactes :** `Le premier pont :`, `Le second pont :`, `Combien de méthodes :`, `Les données :`, `Dans le kit :`.

## 10.1 Comprendre le problème

Le premier pont, `NkGuiCanvasBackend`, traduit les commandes de dessin de NKGui vers les appels de `NkIRenderer2D`. Il permet à NKGui de produire une liste de dessin sans connaître le backend concret de rendu.

Le nouvel objectif est différent : produire la même interface graphique, mais dans un **fichier image**, plutôt que de dessiner à l'écran.

Il ne s'agit pas de déplacer une fenêtre ou de capturer forcément un framebuffer GPU. Il s'agit de recevoir les mêmes données de dessin, de les transformer en pixels en mémoire, puis de sauvegarder ces pixels comme image.

## 10.2 Le premier pont : ce qu'il reçoit et ce qu'il appelle

Fichier : `NKCanvas/UI/NkGuiCanvasBackend.h`.

Repères utiles :

- ligne 26 : classe `NkGuiCanvasBackend` ;
- lignes 38–41 : `Init(NkIRenderer2D*)`, qui reçoit le renderer de NKCanvas ;
- ligne 45 : `UploadFontGray8` ;
- ligne 98 environ : `UploadImageRGBA` ;
- ligne 213 : `Submit(const NkGuiDrawList&, fbW, fbH)` ;
- lignes 295–297 : traduction des rectangles de clip en `mRenderer->SetClip(...)` ;
- lignes 305–323 : traduction du mode `NkGuiBlend` en `NkBlendMode` de NKCanvas ;
- ligne 455 : envoi des vertices au renderer avec `DrawVertices` ;
- ligne 468 : `PopClip` lorsque le clip doit être dépilé.

Le pont ne reçoit donc pas une fenêtre. Il reçoit une liste de dessin (`NkGuiDrawList`), un renderer et des ressources associées. Il transforme les commandes et les indices de la liste en appels de rendu NKCanvas.

## 10.3 Le second pont que tu pourrais concevoir

Pour écrire la même interface dans un fichier image :

1. créer une cible mémoire de largeur `w` et de hauteur `h` ;
2. représenter cette cible comme un tableau de pixels RGBA8 ;
3. enregistrer les textures que les commandes de dessin peuvent référencer ;
4. recevoir la `NkGuiDrawList` ;
5. rasteriser les triangles dans le tableau de pixels ;
6. transférer les pixels vers un encodeur d'image et sauvegarder le fichier.

Le pont reçoit donc toujours une `NkGuiDrawList`, mais au lieu d'appeler un renderer de fenêtre, il écrit les pixels dans un buffer mémoire.

### Combien de méthodes prévoir ?

Il n'existe pas un nombre mathématiquement obligatoire. Le nombre dépend de l'interface publique que tu décides d'exposer.

Une façade minimale pour le cas « rendre une liste et enregistrer une image » pourrait exposer quatre opérations :

1. `Init(width, height)` : créer la cible mémoire ;
2. `SetTexture(id, pixels, width, height, channels)` : associer une texture aux identifiants référencés par la liste ;
3. `Submit(drawList)` : rasteriser la liste dans la cible ;
4. `Save(path)` : encoder et enregistrer les pixels.

Ce nombre de quatre est **ta proposition d'interface**, pas le compte d'une classe déjà trouvée dans le kit. Tu peux proposer une autre API, à condition d'expliquer pourquoi elle suffit et quelles responsabilités sont cachées.

Tu pourrais aussi exposer des méthodes de diagnostic comme `Width()`, `Height()` ou `Pixels()`, mais elles ne sont pas toutes indispensables si l'interface fait directement `Save(path)`.

## 10.4 Quelles données sont nécessaires ?

| Donnée | Pourquoi elle est nécessaire |
|---|---|
| Largeur et hauteur de la cible | Déterminent le nombre de pixels et la zone de rendu. |
| Buffer RGBA8 | Stocke la couleur de chaque pixel calculé. |
| `NkGuiDrawList` | Contient les sommets, indices et commandes à rasteriser. |
| Table identifiant de texture → pixels | Permet de retrouver la texture référencée par `texId`. |
| Dimensions et nombre de canaux des textures | Permettent de lire correctement RGBA8 ou alpha8. |
| Mode de fusion (`NkGuiBlend`) et clip rect | Sont dans chaque commande et déterminent le résultat pixel par pixel. |
| Chemin de sortie ou image cible | Permet à l'encodeur de sauvegarder le résultat. |

Il faut aussi décider de la propriété mémoire : qui possède le buffer ? Qui garantit que les textures restent vivantes pendant la rasterisation ? Le commentaire de `NkGuiDrawListRaster.h` précise que les textures sont **référencées, pas copiées** ; l'appelant doit donc les garder vivantes jusqu'à l'appel `Rasteriser`.

## 10.5 Ce que le kit contient déjà : un vrai second chemin

Le kit contient réellement :

`NKGui/Core/NkGuiDrawListRaster.h`, classe `NkGuiDrawListRaster` à la ligne 62.

Son en-tête décrit une rasterisation logicielle de `NkGuiDrawList` en pixels RGBA8, sans fenêtre et sans GPU. Il explique pourquoi le rasteriseur est placé dans NKGui : la liste de dessin appartient à NKGui, et l'export doit pouvoir utiliser cette liste sans dépendre d'un contexte graphique de fenêtre.

Méthodes publiques visibles :

| Méthode | Ligne | Rôle |
|---|---:|---|
| `Init(w, h)` | 66 | Alloue la cible mémoire, vérifie les dimensions et l'efface. |
| `Effacer(rgba)` | 77 | Remplit la cible d'une couleur. |
| `PoserTexture(id, px, w, h, canaux)` | 91 | Enregistre ou remplace une texture référencée par son identifiant. |
| `Rasteriser(dl)` | 116 | Parcourt les commandes, indices et triangles de la liste. |
| `Largeur()` | 151 | Renvoie la largeur. |
| `Hauteur()` | 152 | Renvoie la hauteur. |
| `Pixels()` | 153 | Renvoie un pointeur constant vers le buffer de pixels. |
| `Pixel(x, y)` | 155 | Lit la couleur d'un pixel. |

Cette classe propose donc huit méthodes publiques de service (hors méthodes privées et destructeur implicite). Elle ne possède pas directement une méthode `Save(path)` dans les lignes de l'interface publique montrées ici.

Le kit contient également `NKImage/Core/NkImage.h`, qui expose notamment `Create`, `SaveToFile`, `Save` et `SavePNG`. `SaveToFile` apparaît à la ligne 336 et délègue à `Save` ; `Save` est déclaré à la ligne 358. Le second pont peut donc obtenir les pixels de `NkGuiDrawListRaster::Pixels()`, les placer dans un `NkImage`, puis appeler l'API de sauvegarde appropriée. La manière exacte de copier le buffer dans `NkImage` doit respecter les fonctions d'accès mémoire de `NkImage` et leur propriété ; vérifie-les avant d'écrire ton code.

## 10.6 Comparaison honnête avec ta proposition

Ta proposition à quatre méthodes expose un service haut niveau : initialiser, enregistrer les textures, soumettre la liste, sauvegarder.

La classe du kit à huit méthodes expose une couche de rasterisation plus bas niveau : elle permet aussi de récupérer les dimensions et de sonder un pixel individuel. Cette API est utile pour les tests, le diagnostic et les exports intégrés par une autre classe. Le fait qu'elle ait huit méthodes au lieu de quatre n'est pas un défaut : elle n'a pas exactement le même périmètre.

**Conclusion :** le second pont existe déjà sous la forme de `NkGuiDrawListRaster` pour produire des pixels. L'encodage du fichier image est une responsabilité complémentaire assurée par `NkImage`. Il n'est donc pas nécessaire de prétendre qu'une seule classe fait tout.

## 10.7 Modèle de `pont.txt`

```text
Le premier pont :
NKCanvas/UI/NkGuiCanvasBackend.h:213 — Submit reçoit une NkGuiDrawList et les dimensions du framebuffer. Il traduit les clips, modes de fusion et vertices en appels à NkIRenderer2D, notamment SetClip, SetBlendMode, DrawVertices et PopClip.

Le second pont :
Je proposerais une classe qui reçoit la même NkGuiDrawList, l'interprète en pixels RGBA8 dans une cible mémoire, puis utilise NkImage pour enregistrer le buffer dans un fichier image. Le dessin ne dépendrait ni d'une fenêtre ni d'un GPU.

Combien de méthodes :
Ma proposition expose quatre méthodes : Init, SetTexture, Submit et Save. Ce compte correspond à l'API publique minimale du service « exporter une liste vers un fichier », et non au nombre de méthodes de la classe déjà présente dans le kit.

Les données :
La cible requiert largeur, hauteur et buffer RGBA8 ; la liste fournit vertices, indices et commandes ; une table de textures associe chaque identifiant à un pointeur de pixels, ses dimensions et son nombre de canaux. Les textures doivent rester vivantes pendant la rasterisation.

Dans le kit :
NKGui/Core/NkGuiDrawListRaster.h définit NkGuiDrawListRaster. Elle possède Init, Effacer, PoserTexture, Rasteriser, Largeur, Hauteur, Pixels et Pixel. Elle réalise la rasterisation en mémoire sans fenêtre ni GPU. NKImage/Core/NkImage.h fournit les opérations de sauvegarde, notamment SaveToFile. La solution du kit sépare donc rasterisation des pixels et encodage du fichier, alors que ma façade à quatre méthodes les regroupe.
```

---

# 11. Exercice 8 — Le Composite à trois niveaux

**Fichiers à rendre :** `ani-2053/chapitre-08/exo8-le_composite_a_trois_niveaux/composite.cpp` et `composite.txt`  
**Étiquettes exactes :** `La hiérarchie :`, `Attendu :`, `Mesuré :`, `Le défaut :`.

## 11.1 L'objectif

Tu dois créer une hiérarchie de trois niveaux :

```text
Parent (niveau 1)
└── Parent (niveau 2)
    └── NkSprite (niveau 3)
```

Chaque niveau a sa propre transformation. Lorsqu'un parent dessine son enfant, il doit composer sa propre transformation avec l'état reçu du parent supérieur.

Tu vas ensuite comparer :

- le résultat calculé avant de lancer le programme ;
- le résultat mesuré par une sonde dans le programme ;
- le résultat de la version fautive qui jette l'état reçu.

## 11.2 Comprendre le contrat de `Draw`

`NkDrawable.h` expose le contrat de dessin avec un `NkRenderTarget` et un `NkRenderStates`. L'état contient notamment la transformation accumulée.

Un objet transformable possède `GetTransform()`. Quand il reçoit l'état de son parent, il doit faire une copie, y composer sa transformation locale puis transmettre cet état à son enfant :

```cpp
NkRenderStates local = states;
local.transform *= GetTransform();
```

Pourquoi copier `states` ? Parce que l'objet doit ajouter sa transformation à l'état courant sans modifier l'objet état reçu par le parent ou par d'autres branches de la hiérarchie.

Pourquoi `*=` ? La convention du moteur indique que la transformation déjà présente est combinée avec la transformation locale. L'ordre compte : `parent * local`, et `A * B` applique B puis A.

## 11.3 Classe de nœud composite

Un nœud pédagogique peut hériter de `NkTransformable` et `NkDrawable`, et contenir un pointeur vers son enfant.

```cpp
class TransformNode : public NkTransformable, public NkDrawable {
public:
    explicit TransformNode(NkDrawable* child) : mChild(child) {}

    void Draw(NkRenderTarget& target,
              const NkRenderStates& states) const override {
        NkRenderStates local = states;
        local.transform *= GetTransform();
        if (mChild != nullptr)
            target.Draw(*mChild, local);
    }

private:
    NkDrawable* mChild = nullptr;
};
```

C'est un modèle de conception de la logique, pas un fichier `composite.cpp` garanti compilable sans adapter les namespaces et includes exacts du kit.

Pourquoi un pointeur plutôt que recevoir l'enfant par valeur ou le construire par copie ? La consigne prévient qu'un nœud qui reçoit son enfant par référence et le construit à partir de cet objet peut invoquer un constructeur de copie. Pour cet exercice, le pointeur permet de référencer l'enfant déjà construit sans copier son état transformable ou ses ressources.

**Attention à la durée de vie :** le propriétaire des trois objets doit les garder vivants pendant que le parent les référence. Un pointeur non propriétaire ne détruit pas l'enfant automatiquement.

## 11.4 Exemple numérique calculé avant le lancement

Pour rendre la différence visible, choisis des translations non nulles et une rotation au niveau du milieu.

- Parent supérieur : position `(100, 50)`, rotation nulle, échelle `(1,1)`.
- Parent du milieu : position `(20, 10)`, rotation `+90°`, échelle `(1,1)`.
- Sprite : position `(5, 0)`, rotation nulle, échelle `(1,1)`.
- Origine locale du point mesuré : `(0,0)`.

Aucun niveau ne change son origine/pivot ; toutes les échelles restent unitaires.

La composition est :

`T_monde = T_parent * T_milieu * T_sprite`.

Rappelle-toi que `A * B` applique B puis A.

Étape 1 — transformation du sprite :

`(0,0) + (5,0) = (5,0)`.

Étape 2 — rotation de +90° au niveau du milieu :

`(5,0)` tourne en `(0,5)`, puis on ajoute la translation du milieu `(20,10)` :

`(20,10) + (0,5) = (20,15)`.

Étape 3 — translation du parent supérieur :

`(100,50) + (20,15) = (120,65)`.

> **Position attendue par le calcul pour cet exemple : `(120, 65)`.** Ce nombre est un résultat mathématique calculé à partir des valeurs choisies, pas une mesure de l'exécutable. Le journal de ta sonde doit confirmer ou expliquer un écart.

Dans `NkTransformable.h`, le setter de rotation reçoit `math::NkAngle`, pas un flottant nu. `NkAngle(90.f)` représente 90 degrés selon le commentaire du kit ; `NkAngle::FromRad(...)` exprime les radians. Ne passe pas `90.f` directement à une méthode qui attend `NkAngle`.

## 11.5 Mesurer la position réellement transmise

Ajoute une petite sonde qui implémente `NkDrawable` et qui reçoit l'état final. Dans son `Draw`, elle copie l'état, compose éventuellement sa transformation locale, puis calcule :

```cpp
NkVec2f worldOrigin = local.transform.TransformPoint({0.f, 0.f});
```

`TransformPoint` se trouve dans `NKCanvas/Renderer/Core/NkTransform.h:157–160`.

Écris `worldOrigin.x` et `worldOrigin.y` dans un fichier avec suffisamment de décimales. Une petite différence flottante peut exister ; compare avec une tolérance raisonnable au lieu d'exiger une égalité binaire parfaite.

Tu peux également utiliser la capture demandée :

```text
--capture=capture.png --capture-frame=10
```

Mais la consigne avertit que la relecture de capture n'est promise que par le dorsal DirectX 11. Si le fichier n'est pas produit sur ton backend, tes sondes restent le moyen de mesure ; mentionne la limite dans ton compte rendu.

## 11.6 Vérifier que le sprite est réellement dessinable

La consigne précise qu'un sprite a besoin d'une texture. Elle donne cet exemple dans `OnInit` :

```cpp
mTexture.Create(*Target().GetRenderer(), 32, 32,
                NkColor2D{255, 200, 0, 255});
sprite.SetTexture(mTexture);
```

Garde l'objet texture vivant aussi longtemps que le sprite l'utilise. Une texture détruite trop tôt entraîne un problème de durée de vie de ressource, même si le calcul de transformation est correct.

## 11.7 Reproduire volontairement le défaut

Le commentaire de `NkSprite.h:16–18` raconte l'ancien bug : son `Draw` jetait l'état reçu. Pour montrer que ton test attrape ce bug, crée une deuxième sonde fautive qui n'utilise pas `states` et qui repart d'un état par défaut avant de composer seulement son propre transform.

```cpp
// Version volontairement fautive pour le test :
NkRenderStates local = NkRenderStates::Default();
local.transform *= GetTransform();
```

Pour le point d'origine du sprite, avec la hiérarchie numérique choisie, si c'est bien la sonde du niveau sprite qui jette l'état reçu et conserve uniquement sa translation locale, elle mesurera `(5,0)` au lieu de `(120,65)`.

Pourquoi ? Parce que la transformation du milieu et celle du parent supérieur ont été perdues. Le résultat n'est donc pas une petite erreur visuelle aléatoire : il révèle exactement l'état parent que le sprite a jeté.

Ne confonds pas les différentes positions possibles d'une sonde fautive : si tu places le défaut dans le parent du milieu, le parent supérieur peut être perdu mais le milieu et le sprite peuvent encore composer leurs propres transforms. Le résultat dépend du niveau où tu introduis volontairement la faute. Dis clairement où tu as placé le défaut.

## 11.8 Debug, Release et capture

Construis en Debug et Release. Pour chaque exécution, consigne :

- les transformations utilisées ;
- la position calculée avant exécution ;
- la position issue de la sonde correcte ;
- la position issue de la sonde fautive ;
- si `capture.png` a été produit ;
- le backend utilisé.

Ne présente pas une capture absente comme une preuve de panne du Composite : l'énoncé signale une limite de capture selon le backend. Inversement, une image visuellement plausible n'est pas une mesure numérique suffisante : garde les sondes.

## 11.9 Modèle de `composite.txt`

```text
La hiérarchie :
Parent supérieur position (100,50) -> parent du milieu position (20,10), rotation +90 degrés -> NkSprite position (5,0). Chaque parent compose l'état reçu avec son propre GetTransform(), puis le transmet à l'enfant par target.Draw(*child, local). L'enfant est conservé par pointeur pour éviter une copie ; sa durée de vie couvre celle de la hiérarchie.

Attendu :
Pour l'origine locale (0,0), T_monde = T_parent * T_milieu * T_sprite. Le sprite donne (5,0), la rotation du milieu transforme ce vecteur en (0,5), puis la translation du milieu donne (20,15), puis celle du parent supérieur donne (120,65). Position attendue : (120,65).

Mesuré :
[Insérer les positions réelles mesurées par la sonde correcte en Debug et Release et le résultat de capture si disponible. Ne pas remplacer les mesures par le calcul attendu.]

Le défaut :
[Insérer le résultat de la sonde fautive qui repart d'un état par défaut. Pour le défaut placé au niveau du sprite avec cette configuration, la position attendue du modèle fautif est (5,0). Expliquer que le parent/milieu n'est plus transmis et montrer que le test distingue la version correcte de la version qui jette l'état.]
```

---

# 12. Exercice 9 — La façade qui grossit

**Fichier à rendre :** `ani-2053/chapitre-08/exo9-la_facade_qui_grossit/facade.txt`  
**Étiquettes exactes :** `Publiques :`, `Utiles :`, `Les autres :`, `Le rapport :`.

## 12.1 Ce que l'exercice veut démontrer

Une façade vise à simplifier un sous-système. Mais au fil du temps, on peut y ajouter une méthode pour chaque besoin particulier. Elle finit par devenir un catalogue de toutes les opérations internes.

L'exercice choisit `NkRenderTarget.h` et demande :

1. compter toutes ses méthodes publiques ;
2. distinguer celles utilisées par les programmes du Sprint (directement ou par la boucle de `NkCanvasApp`) ;
3. expliquer le besoin auquel répond chaque autre méthode ;
4. repérer celles que leur propre commentaire déclare provisoires ;
5. calculer un rapport et juger si la façade tient encore sa promesse.

## 12.2 Règle de comptage

Le piège indique :

- compte chaque surcharge séparément, ou compte-les ensemble, mais annonce ta règle ;
- une méthode non virtuelle compte aussi ;
- ne compte pas uniquement les lignes `virtual`.

Dans `NkRenderTarget.h`, si l'on compte chaque déclaration de méthode de service séparément, en excluant le destructeur : **24 déclarations**.

Si l'on compte uniquement les noms distincts de méthodes, en regroupant les surcharges de `Draw`, `GetRenderer` et `GetRenderer2D` : **19 noms**.

Le destructeur virtuel de la ligne 50 est une fonction membre publique, mais je le sépare des opérations de service pour rendre l'analyse utile. Tu peux également l'indiquer comme `+ 1 destructeur` si le professeur veut une définition exhaustive de toutes les fonctions membres publiques. L'essentiel est de dire précisément ce que tu comptes.

## 12.3 Liste des 24 déclarations de service

Fichier : `NKCanvas/Renderer/Targets/NkRenderTarget.h`, classe de la ligne 48.

| # | Méthode / surcharge | Ligne(s) | Besoin auquel elle répond |
|---:|---|---:|---|
| 1 | `Clear(color)` | 55 | Effacer le framebuffer. |
| 2 | `Display()` | 59 | Présenter / finaliser le rendu. |
| 3 | `SetView(view)` | 63 | Définir la caméra ou vue. |
| 4 | `GetView()` | 64 | Lire la vue courante. |
| 5 | `GetDefaultView()` | 65 | Lire la vue par défaut. |
| 6 | `ResetView()` | 69 | Revenir à la vue par défaut et reprendre le suivi automatique. |
| 7 | `IsViewCustom()` | 74 | Savoir si une vue personnalisée a été fixée. |
| 8 | `SetViewport(viewport)` | 80 | Définir la sous-région de rendu. |
| 9 | `GetViewport()` | 81 | Lire le viewport. |
| 10 | `SetResizePolicy(policy, designSize)` | 90 | Définir comment le contenu s'ajuste au redimensionnement. |
| 11 | `GetResizePolicy()` | 95 | Lire la politique. |
| 12 | `GetDesignSize()` | 99 | Lire la taille de conception de référence. |
| 13 | `GetSize()` | 105 | Lire les dimensions en pixels de la cible. |
| 14 | `Draw(NkDrawable, states)` | 111 | Dessiner un objet moderne qui reçoit un état composé. |
| 15 | `Draw(NkVertexArray, states)` | 116 | Dessiner un tableau de sommets. |
| 16 | `Draw(vertices, count, primitive, states)` | 121 | Soumettre directement des vertices au backend. |
| 17 | `Draw(NkIDrawable2D)` | 129 | Compatibilité avec l'ancienne interface drawable. |
| 18 | `MapPixelToCoords(pixel)` | 133 | Convertir des coordonnées écran en coordonnées du monde. |
| 19 | `MapCoordsToPixel(point)` | 134 | Convertir des coordonnées monde en pixels. |
| 20 | `GetRenderer()` non const | 138 | Accéder au renderer bas niveau. |
| 21 | `GetRenderer()` const | 139 | Accès const au renderer bas niveau. |
| 22 | `GetRenderer2D()` non const | 143 | Accès à la façade utilisateur `NkRenderer2D`. |
| 23 | `GetRenderer2D()` const | 144 | Accès const à cette façade utilisateur. |
| 24 | `Capture(path)` | 152 | Lire le contenu présenté et l'enregistrer comme image si le backend le permet. |

La liste ci-dessus est un repère de lecture. Vérifie les lignes et signatures dans ton fichier exact, en particulier les déclarations qui s'étendent sur deux lignes.

## 12.4 Quelles méthodes sont utiles aux programmes du Sprint ?

La bonne méthode consiste à ouvrir tes programmes des exercices précédents et chercher les appels réellement écrits. Pour une classification cohérente, tu peux retenir les opérations suivantes :

- `Clear` et `Display` : appelées par le squelette de la boucle de `NkCanvasApp`, selon l'extrait fourni à l'exercice 4 ;
- les formes de `Draw` que ton `OnRender` ou ton `NkDrawable` utilise ;
- `GetRenderer` : nécessaire dans l'exercice 8 pour créer la texture via le renderer ;
- `Capture` : si tu comptes le mécanisme `--capture` demandé à l'exercice 8 et pris en charge par la coquille, explique que tu le comptes comme usage indirect, pas comme un appel écrit dans ton `composite.cpp`.

Ne dis pas que les quatre surcharges de `Draw` sont toutes utilisées si tes programmes n'en utilisent qu'une ou deux. Cherche les appels concrets. Le nombre de méthodes utiles dépend aussi de ce que tu as vraiment écrit.

## 12.5 Que font les autres méthodes ?

Elles ne sont pas nécessairement inutiles. Elles répondent à des cas d'usage plus avancés :

- caméra et vue : `SetView`, `GetView`, `GetDefaultView`, `ResetView`, `IsViewCustom` ;
- découpage de l'écran : `SetViewport`, `GetViewport` ;
- adaptation aux tailles et formats d'écran : `SetResizePolicy`, `GetResizePolicy`, `GetDesignSize`, `GetSize` ;
- conversion entre pixels et coordonnées du monde : `MapPixelToCoords`, `MapCoordsToPixel` ;
- interopération ou personnalisation avancée : `GetRenderer`, `GetRenderer2D` ;
- capture et export : `Capture`.

Une API peut être large tout en restant utile si elle répond à plusieurs besoins réels. Il faut donc juger la promesse au regard de l'utilisation du moteur, pas seulement dire « 24, c'est trop ».

## 12.6 La méthode provisoire à repérer

`NkRenderTarget.h:124–129` documente l'ancienne interface :

```cpp
// Compat : un drawable ancien style (NkIDrawable2D::Draw(NkIRenderer2D&)).
// Delegue au renderer interne. Sera retire quand NkSprite/NkText
// auront migre vers NkDrawable (etape A.8).
void Draw(const NkIDrawable2D &drawable);
```

C'est un cas important : le commentaire annonce explicitement une méthode de compatibilité temporaire qui sera retirée après migration. Il ne faut pas confondre « méthode publique » et « méthode qui a vocation à rester dans l'API ».

Une autre subtilité : `Draw(const NkDrawable&, states)` est défini dans l'en-tête sans mot-clé `virtual`, mais il reste une méthode publique qui compte pour l'exercice. Il délègue à `drawable.Draw(*this, states)`.

## 12.7 Calculer le rapport

Le rapport dépend du choix de comptage. L'énoncé exige de le calculer et de dire comment tu comptes.

Exemple de convention défendable :

- total : 24 déclarations de service (surcharges séparées, destructeur exclu) ;
- utiles : tu comptes uniquement les déclarations que tes programmes du Sprint ou le squelette de `NkCanvasApp` utilisent réellement ;
- autres : 24 − utiles.

Si tu identifies 6 déclarations utiles avec ta convention et que tu les justifies dans tes programmes, le rapport utile/total serait `6 / 24 = 0,25`, soit 25 %. **Ce 6 est un exemple de classement à valider sur tes propres appels et sur le mécanisme de capture ; ne le présente pas comme une mesure faite par ton projet sans vérifier.**

Tu peux aussi choisir de compter les noms distincts (19) ; dans ce cas, toutes les catégories et le calcul doivent être basés sur 19. Ne divise jamais un compte de noms uniques par un total qui compte les surcharges séparément.

## 12.8 Modèle de `facade.txt`

```text
Publiques :
24 déclarations de méthodes de service dans NkRenderTarget.h, destructeur exclu et surcharges comptées séparément. Si je compte par noms distincts, j'obtiens 19. Ma règle est de compter les déclarations séparément.

Utiles :
Clear et Display via la boucle de NkCanvasApp ; Draw pour les objets effectivement dessinés par mes programmes ; GetRenderer pour la création de la texture de l'exercice 8 ; Capture si l'on compte le mécanisme de capture demandé comme usage indirect de la coquille. [Adapter cette liste à tes appels réellement écrits.]

Les autres :
[Énumérer chaque méthode non utilisée dans les programmes du Sprint et expliquer son besoin : vue, viewport, resize, coordonnées, accès avancé au renderer, etc.]
Draw(const NkIDrawable2D&) est explicitement une compatibilité provisoire : son commentaire annonce son retrait après migration vers NkDrawable.

Le rapport :
[Calculer utiles / total avec la convention annoncée.] Le résultat montre quelle part de l'API est utilisée par ces programmes précis. Il ne prouve pas que les autres méthodes sont inutiles dans tous les projets. La façade simplifie le cas courant mais expose aussi de nombreuses opérations avancées ; la méthode de compatibilité montre qu'elle porte encore une dette de transition.
```

---

# 13. Exercice 10 — Le motif absent

**Fichier à rendre :** `ani-2053/chapitre-08/exo10-le_motif_absent/absent.txt`  
**Étiquettes exactes :** `L'endroit :`, `Le motif :`, `Le coût :`.

## 13.1 Pourquoi cet exercice est le plus délicat

Les neuf premiers motifs sont décrits dans le cours et plusieurs sont directement illustrés par des fichiers. L'exercice 10 te demande de repérer un endroit où un motif **n'est pas encore employé**, alors qu'un problème récurrent pourrait le justifier.

C'est une enquête de conception, pas une chasse aux mots-clés. Le professeur suggère trois indices :

- un `switch` sur le même type répété à plusieurs endroits ;
- du code de création dispersé ;
- une classe qui connaît inutilement une autre classe.

Mais les consignes avertissent aussi : deux fonctions qui se ressemblent peuvent avoir des responsabilités différentes. Il faut les comparer ligne par ligne.

## 13.2 Ce qu'il faut prouver

Avant de proposer un motif, il faut établir :

1. un premier cas concret, fichier et ligne ;
2. un deuxième cas concret, fichier et ligne ;
3. pourquoi les deux cas résolvent réellement le même problème ou font le même choix ;
4. pourquoi la conception actuelle crée une répétition ou une dépendance indésirable ;
5. quel motif supprimerait ou centraliserait ce problème ;
6. ce qu'il faudrait modifier et quel risque pourrait casser.

Deux lignes qui contiennent toutes les deux `switch` ne suffisent pas. Elles peuvent interpréter le même enum pour des objectifs très différents.

## 13.3 Recherches réelles utiles dans ce kit

### Piste A — les modes de fusion `NkGuiBlend`

Deux endroits intéressants :

- `NKCanvas/UI/NkGuiCanvasBackend.h:304–323` : `switch (dc.blend)` transforme un mode NKGui en état de blend de `NkIRenderer2D` via `SetBlendMode`.
- `NKGui/Core/NkGuiDrawListRaster.h:218` et autour des lignes 223–240 : `Melanger(..., NkGuiBlend mode)` applique les équations de mélange au buffer de pixels logiciel.

Ils portent sur le même type logique de mode de fusion. Cela peut suggérer deux stratégies de réalisation : GPU via le renderer et CPU via le rasteriseur.

**Mais attention :** les deux fonctions n'ont pas exactement la même tâche. L'une sélectionne un état GPU ; l'autre calcule la couleur de chaque pixel en mémoire. Un switch identique n'est pas automatiquement un morceau de code que l'on peut fusionner. Un mécanisme de stratégie pourrait être étudié si l'architecture a besoin de remplacer l'algorithme de fusion indépendamment, mais créer une classe par mode de fusion pourrait aussi être un surdesign.

Utilise cette piste pour apprendre à vérifier le problème, pas comme conclusion automatique.

### Piste B — conversion d'un enum API graphique en nom texte

Deux fonctions proches sont visibles :

- `NKEvent/NkGraphicsEvent.h:73` : `NkGraphicsApiToString(NkGraphicsApi)` ;
- `NKCanvas/Core/NkGraphicsApi.h:11` : `NkGraphicsApiName(NkGraphicsApi)`.

Les deux convertissent un `NkGraphicsApi` en chaîne lisible. Elles couvrent des valeurs proches, mais leurs chaînes ne sont pas strictement identiques : par exemple, `OpenGLES` versus `OpenGL ES`, `D3D11` versus `DirectX 11`, et `NkGraphicsApiToString` couvre `WEBGPU` dans la version inspectée alors que `NkGraphicsApiName` ne l'énumère pas dans le switch montré.

C'est une duplication réelle à examiner, mais **la bonne solution peut être une fonction utilitaire partagée**, sans motif GoF particulier. Il serait artificiel de déclarer qu'une stratégie ou une façade est nécessaire sans démontrer une variation de comportement plus large.

### Piste C — deux chemins pour rendre la même `NkGuiDrawList`

Deux classes reçoivent la même abstraction d'entrée :

- `NKCanvas/UI/NkGuiCanvasBackend.h:213` expose `Submit(const NkGuiDrawList&, fbW, fbH)` et transforme la liste en appels au renderer NKCanvas ;
- `NKGui/Core/NkGuiDrawListRaster.h:116` expose `Rasteriser(const NkGuiDrawList&)` et transforme cette liste en pixels RGBA8 en mémoire.

C'est la piste la plus intéressante si tu veux examiner une **Stratégie de rendu** : le même contenu de dessin peut être traité par deux chemins, l'un connecté au renderer, l'autre rasterisé en mémoire. Une interface commune pourrait représenter un service « rendre cette draw list », puis des implémentations distinctes réaliseraient le chemin écran/GPU et le chemin logiciel/pixels.

Mais ne conclus pas automatiquement que cette abstraction est nécessaire. Les destinations et les résultats ne sont pas identiques : le premier backend soumet au GPU, le second fournit un buffer de pixels, et ce dernier exige aussi l'enregistrement des textures. Pour que la stratégie soit justifiée, démontre qu'un appelant doit réellement pouvoir sélectionner ces deux modes derrière un contrat commun. Si les usages sont distincts (affichage normal contre export d'image), deux API séparées peuvent être plus claires.

Coût possible : définir un contrat commun de rendu de draw list ; adapter les deux classes ou créer des wrappers ; unifier l'initialisation et les dimensions ; préciser comment récupérer le résultat (cible de rendu ou pixels) ; tester les clips, textures, modes de fusion et ordre des commandes sur les deux chemins. Ce n'est donc pas juste « extraire le switch » : le contrat de sortie doit être soigneusement conçu.

### Piste D — les fonctions de création de `NkContextDesc`

`NKCanvas/Core/NkContextDesc.h` possède plusieurs méthodes statiques de type `MakeOpenGL`, `MakeOpenGLES`, `MakeVulkan`, `MakeDX11`, `MakeDX12`, `MakeMetal`, `MakeSoftware`.

Cela ressemble à un ensemble de fonctions de fabrique. Mais elles sont déjà centralisées dans `NkContextDesc` et construisent des variantes de configuration distinctes. Cette piste peut être un exemple d'endroit où la fabrique existe déjà plutôt qu'un motif absent.

## 13.4 Quel motif proposer ?

Choisis le motif en fonction du problème prouvé, pas du mot qui apparaît dans le code.

| Problème prouvé | Motif qui pourrait convenir | Pourquoi |
|---|---|---|
| Plusieurs comportements interchangeables sont codés par branches répétées et doivent évoluer indépendamment | Stratégie | Chaque comportement devient une implémentation d'un contrat commun. |
| Plusieurs clients construisent directement les mêmes classes concrètes ou dispersent la sélection | Fabrique | La création et le choix sont centralisés. |
| Un client coordonne plusieurs sous-systèmes pour faire une opération courante | Façade | Une entrée simple orchestre les détails. |
| Plusieurs abonnés reçoivent le même type de notification via des liens directs | Observateur | L'émetteur publie sans connaître chaque consommateur. |
| Une classe doit collaborer avec une interface incompatible | Adaptateur | Traduction entre contrats. |
| Les actions sont dispersées et doivent être stockées/rejouées/annulées | Commande | L'action devient une entité explicite. |

Une duplication de conversion texte peut simplement demander une fonction commune, ce qui n'est pas nécessairement un des neuf motifs. Dans ce cas, continue la recherche plutôt que de forcer le motif demandé.

## 13.5 Évaluer le coût d'introduction

Ton analyse doit compter les fichiers à changer et identifier ce qui peut casser.

Exemple de grille :

| Élément | Question à poser |
|---|---|
| Fichiers de l'interface | Faudra-t-il créer une nouvelle interface ou une classe abstraite ? |
| Implémentations | Combien de classes ou fonctions doivent être déplacées/redéfinies ? |
| Appels existants | Les utilisateurs appellent-ils aujourd'hui une fonction concrète ou un switch ? |
| Données | Les fonctions partagent-elles réellement les mêmes entrées et sorties ? |
| Tests | Quels résultats existants doivent rester identiques ? |
| Risques | Régression de plateforme, ordre d'appel, gestion mémoire, formats, état global, performance ? |

Ne donne pas un nombre de fichiers au hasard. Établis une liste : « je dois modifier A et B, ajouter C, et adapter D si les appels directs sont publics ». C'est ce plan qui justifie le coût.

## 13.6 Comment travailler cette question sans la bâcler

1. Recherche une famille de décisions ou de constructions dans tout `include/`.
2. Garde au moins deux occurrences en code actif.
3. Ouvre les deux fonctions et compare leurs paramètres, leur sortie, leurs effets de bord et leurs conditions.
4. Élimine les fausses répétitions : commentaires, exemples, branches conditionnelles, opérations de nature différente.
5. Formule le problème dans une phrase : « deux endroits décident indépendamment de … » ou « trois clients construisent directement … ».
6. Propose le motif qui répond à cette phrase.
7. Liste les fichiers à modifier et les risques.
8. Vérifie que le motif ne serait pas introduit pour un seul cas : montre bien le deuxième cas au minimum.

## 13.7 Exemple de conclusion prudente sur les pistes observées

Dans la version du kit inspectée, les deux switches `NkGuiBlend` constituent une piste d'enquête, mais leurs opérations sont différentes (état de blend GPU versus calcul CPU par pixel). Les deux fonctions `NkGraphicsApiToString` et `NkGraphicsApiName` répètent une conversion proche, mais une fonction partagée pourrait suffire sans motif de conception élaboré. Ces constats réels sont utiles, mais ils ne permettent pas de prétendre automatiquement qu'un motif GoF précis manque.

**La conclusion la plus rigoureuse est de poursuivre l'enquête jusqu'à trouver deux occurrences d'un problème identique et une solution de motif proportionnée.** Si tu décides de retenir l'une de ces pistes, explique précisément ce qui est commun et ce qui est différent, et ne cache pas les différences.

## 13.8 Modèle de `absent.txt`

```text
L'endroit :
[Fichier 1]:[ligne] — décrire la décision ou création réelle.
[Fichier 2]:[ligne] — montrer le deuxième cas et expliquer ce qui est identique au premier.
Comparer les entrées, conditions, sorties et effets. Dire si les lignes sont du code actif et non des commentaires.

Le motif :
[Nom du motif.] Expliquer comment il répond au problème commun et pourquoi il est préférable à une simple fonction commune ou à une autre abstraction. Indiquer ce qui resterait identique du point de vue du client.

Le coût :
[Fichiers à modifier, fichiers à ajouter, fonctions à adapter, tests à créer.] Risques : régression des appels existants, valeurs par défaut, comportement par plateforme, ordre d'exécution, allocation/durée de vie ou performance selon le cas.
```

La consigne donne 6 points à la preuve du deuxième cas, 5 au choix du motif, 5 à l'estimation du coût et 2 à la vérification que le motif n'est pas introduit pour un cas unique. C'est donc une analyse argumentée, pas une question à réponse unique.

---
# 14. Synthèse de tout le Sprint

## 14.1 Les dix exercices en une seule vue

| Exercice | Concept central | Action principale | Preuve ou résultat attendu |
|---:|---|---|---|
| 1 | Reconnaître les motifs dans un vrai moteur | Chercher 9 motifs dans `include/` | Huit preuves fichier/ligne ; un motif absent ou seulement approché, commentaire signalé. |
| 2 | Stratégie et coût d'une interface | Compter méthodes pures, virtuelles avec corps et overrides des backends | Compte justifié, 6 dorsaux, méthode de vérification indépendante, coût d'un dorsal de plus. |
| 3 | Fabrique | Rechercher `NkOpenGLRenderer2D` partout | Commande, fichiers, lignes, classification code/commentaire, conclusion. |
| 4 | Patron de méthode | Redéfinir les hooks `NkCanvasApp` et journaliser | Liste de 12 hooks, ordre réellement mesuré, surprises, comparaison Debug/Release. |
| 5 | Observer / Push / Pull | Classer six situations de jeu | Modèle et outil du kit pour chaque situation ; deux bogues dus au mauvais choix. |
| 6 | Singleton et testabilité | Garder une fonction directe et une fonction injectée | Quatre cas, journal, code de sortie, résultat réel sans fenêtre. |
| 7 | Adaptateur | Comprendre le backend NKGui→NKCanvas puis un rendu fichier | Premier pont, seconde solution, méthodes, données et comparaison avec le rasteriseur réel du kit. |
| 8 | Composite | Construire une hiérarchie de 3 niveaux | Calcul attendu, positions mesurées, version fautive qui jette l'état, Debug/Release. |
| 9 | Façade | Compter les méthodes de `NkRenderTarget` | Total, méthodes utilisées, autres méthodes et besoins, provisoires, rapport argumenté. |
| 10 | Motif absent | Trouver une répétition réelle et proposer une solution | Deux cas minimum, motif justifié, coût et risques de modification. |

## 14.2 Les relations entre les exercices

Le Sprint n'est pas une série de dix questions sans rapport. L'ordre construit une compréhension progressive :

1. Ex1 te donne les noms et les premiers emplacements des motifs.
2. Ex2 approfondit l'interface de stratégie en mesurant son coût réel.
3. Ex3 teste le critère de la fabrique dans les fichiers : les noms concrets sont-ils diffusés ?
4. Ex4 donne une mesure réelle du patron de méthode : les hooks sont appelés quand la classe de base le décide.
5. Ex5 relie l'observateur aux notions d'événement et d'état : Push et Pull ne sont pas interchangeables.
6. Ex6 montre un coût du Singleton : l'accès global rend une fonction difficile à tester.
7. Ex7 approfondit l'adaptateur et montre l'intérêt d'un second backend.
8. Ex8 rend le Composite concret par une hiérarchie et une erreur de propagation de l'état.
9. Ex9 revient à la façade et mesure son élargissement.
10. Ex10 t'oblige à ne pas appliquer les motifs mécaniquement : tu dois identifier un deuxième cas et chiffrer le coût d'une correction.

## 14.3 Les dix livrables et les étiquettes à ne pas oublier

| Exercice | Chemin exact sous `ani-2053/chapitre-08/` | Fichier(s) | Étiquettes dans l'ordre |
|---:|---|---|---|
| 1 | `exo1-le_motif_et_son_fichier/` | `motifs.txt` | Stratégie ; Fabrique ; Façade ; Patron de méthode ; Observateur ; Singleton ; Adaptateur ; Composite ; Commande |
| 2 | `exo2-l_interface_de_la_strategie/` | `strategie.txt` | Virtuelles pures ; Dorsaux ; Ce que chacun écrit ; Le coût |
| 3 | `exo3-la_fabrique_en_un_coup_d_oeil/` | `fabrique.txt` | Recherche ; Hors de son dossier ; Conclusion |
| 4 | `exo4-les_crochets_du_patron/` | `crochets.cpp`, `crochets.txt` | Les crochets ; L'ordre mesuré ; Les surprises ; Debug et Release |
| 5 | `exo5-push_ou_pull/` | `push_pull.txt` | Situations ; Les deux bogues |
| 6 | `exo6-le_singleton_et_le_test/` | `banc.cpp`, `banc.txt` | Tester la version directe ; La version testable ; Le banc ; Sans fenêtre |
| 7 | `exo7-un_second_pont/` | `pont.txt` | Le premier pont ; Le second pont ; Combien de méthodes ; Les données ; Dans le kit |
| 8 | `exo8-le_composite_a_trois_niveaux/` | `composite.cpp`, `composite.txt` | La hiérarchie ; Attendu ; Mesuré ; Le défaut |
| 9 | `exo9-la_facade_qui_grossit/` | `facade.txt` | Publiques ; Utiles ; Les autres ; Le rapport |
| 10 | `exo10-le_motif_absent/` | `absent.txt` | L'endroit ; Le motif ; Le coût |

Les étiquettes doivent être reproduites exactement, avec leur accent, leur espace et leur deux-points. Les noms de fichiers et les dossiers sont stricts.

## 14.4 Règles générales de dépôt

- Utilise le chemin exact fourni par l'exercice, sans inventer un dossier alternatif.
- N'ajoute ni ton nom ni ton matricule dans les fichiers.
- Le dépôt demandé est public.
- Vérifie la présence de tous les fichiers avant de soumettre.
- Le contrôle automatique regarde les chemins, noms et étiquettes ; il ne remplace pas la correction humaine du raisonnement.
- Le commit évalué est celui présent au moment de l'évaluation : assure-toi d'avoir poussé la version finale.

---

# 15. Organisation d'une journée de révision hors ligne

L'objectif est que tu comprennes les notions et avances sur tous les exercices sans te disperser. Prépare tout avant de couper Internet : le kit, le dépôt, les outils, les bibliothèques et ce document.

## Bloc 1 — Fondations et vocabulaire (45 à 60 min)

- Relis les sections 1 et 2.
- Réexplique sans regarder : classe, objet, état, interface, fonction virtuelle pure, héritage, polymorphisme, dépendance, allocateur.
- Écris un exemple de deux implémentations derrière une interface commune.
- Explique avec tes mots pourquoi une abstraction peut être inutile.

**Tu es prêt à continuer lorsque** tu peux expliquer la différence entre une interface et une implémentation sans réciter une définition.

## Bloc 2 — Les neuf motifs (60 à 90 min)

- Lis chaque motif de la section 2.
- Pour chaque motif, écris une phrase « problème → solution ».
- Compare les motifs qui se ressemblent : stratégie/fabrique, façade/adaptateur, stratégie/commande, Push/Pull.
- Essaie de créer un exemple de jeu pour chaque motif.

**Tu es prêt à continuer lorsque** tu peux nommer le problème avant de donner le nom du motif.

## Bloc 3 — Exercices 1, 2 et 3 : lecture statique (90 min)

- Refaire les recherches `NkOpenGLRenderer2D` et `= 0;`.
- Ouvrir les fichiers et vérifier les lignes ; ne pas faire confiance uniquement aux résultats de recherche.
- Compléter les paragraphes des exercices 1, 2 et 3.
- Refaire au moins une fois chaque compte par une deuxième méthode.

**Point de contrôle :** tes nombres, tes lignes et tes conclusions doivent être justifiables par une sortie de commande ou un fichier ouvert.

## Bloc 4 — Exercice 4 : patron de méthode mesuré (90 à 120 min)

- Lister les 12 hooks.
- Écrire les overrides et le journal.
- Limiter les lignes répétitives de `OnUpdate` / `OnRender` aux premières frames.
- Construire Debug et Release.
- Lancer sans toucher à la fenêtre et garder les journaux.
- Comparer et remplir `crochets.txt`.

## Bloc 5 — Exercice 5 : décisions Push/Pull (35 à 50 min)

- Pour les six situations, demande-toi si tu as besoin d'une notification ou d'un état présent.
- Vérifie chaque nom de type et fichier dans `include/`.
- Écris les deux bogues concrets du mauvais modèle.

## Bloc 6 — Exercice 6 : singleton et banc sans fenêtre (60 à 90 min)

- Écrire la version directe.
- Écrire la version testable.
- Faire la table de quatre cas.
- Construire un petit banc, écrire les résultats dans un fichier et retourner le nombre d'échecs via `OnCommandLine`.
- Lancer Debug et Release sans fenêtre.
- Noter ce que la version directe a vraiment vu dans `NkInput`.

## Bloc 7 — Exercices 7 et 8 : adaptateur et composite (90 à 120 min)

- Comprendre les inputs/outputs des deux ponts.
- Décrire la cible mémoire et le chemin vers `NkImage`.
- Calculer les trois transformations à la main.
- Construire les trois niveaux, la sonde correcte et la sonde fautive.
- Lancer Debug/Release, comparer les valeurs, essayer la capture et expliquer si elle manque.

## Bloc 8 — Exercices 9 et 10 : jugement de conception (60 à 90 min)

- Compter `NkRenderTarget` avec une convention claire.
- Classer chaque méthode et justifier celles que tes programmes utilisent.
- Calculer le rapport.
- Pour le motif absent, chercher deux cas réels et refuser les fausses répétitions.
- Écrire un coût de modification avec les fichiers à changer et les risques.

## Bloc 9 — vérification finale (30 min)

- Ouvre chaque fichier de sortie.
- Vérifie les étiquettes, l'ordre, les nombres et les preuves.
- Vérifie que les journaux proviennent bien de tes exécutables.
- Vérifie qu'aucune valeur d'exemple fictive n'a été copiée comme mesure réelle.
- Contrôle le chemin exact et pousse tous les fichiers.

---

# 16. Check-list de qualité avant de remettre chaque exercice

## Exercices de lecture statique (1, 2, 3, 7, 9, 10)

- [ ] J'ai utilisé le kit du 22 octobre 2026.
- [ ] Le chemin de fichier est complet et exact.
- [ ] J'ai ouvert les lignes trouvées, pas seulement lu le résultat de recherche.
- [ ] J'ai distingué code actif, commentaire, exemple commenté et condition de compilation.
- [ ] J'ai expliqué ce que la ligne prouve réellement.
- [ ] J'ai indiqué ce que je ne peux pas conclure parce que le corps de la méthode est absent.
- [ ] J'ai annoncé ma règle de comptage quand il y a des surcharges ou des branches `#if`.

## Exercices avec programme et mesure (4, 6, 8)

- [ ] Le programme compile en Debug.
- [ ] Le programme compile en Release.
- [ ] Les deux exécutables ont réellement été lancés.
- [ ] Les journaux ou fichiers de mesure ont été lus après l'exécution.
- [ ] Les résultats consignés sont copiés depuis ces journaux.
- [ ] Les calculs théoriques sont séparés des mesures.
- [ ] Les limites du backend ou de la capture sont expliquées.
- [ ] Aucun résultat n'a été inventé pour remplir un paragraphe.

## Exercices de raisonnement (5, 7, 9, 10)

- [ ] Chaque choix est lié au besoin précis.
- [ ] J'explique pourquoi l'alternative ne répond pas aussi bien au besoin.
- [ ] Je distingue ce qui est utile dans ce Sprint de ce qui est inutile dans tous les projets.
- [ ] Je chiffre les coûts et les risques lorsque l'énoncé le demande.

---

# 17. Erreurs fréquentes à éviter absolument

1. **Copier un nom de classe sans lire le code.** `NkActionCommand` contient le mot Command, mais son nom ne suffit pas à établir le motif Commande classique.
2. **Prendre un commentaire pour une implémentation.** L'exemple `AsyncTask` de `NkFuture.h` est dans un bloc commentaire ; il ne compile pas comme classe active.
3. **Compter des `= 0;` partout dans le fichier.** Il faut compter uniquement dans la classe ciblée, pas dans une interface voisine ou un exemple.
4. **Compter toutes les branches `#if` ensemble.** Elles sont des variantes conditionnelles, pas des méthodes simultanément actives.
5. **Confondre méthodes héritées et méthodes redéfinies.** Le backend hérite de `NkBatchRenderer2D`, qui a déjà une partie des implémentations.
6. **Dire qu'une occurrence de nom est un appel.** Une occurrence de commentaire ne crée aucune dépendance de code.
7. **Confondre état et événement.** Le premier appui d'une touche et la touche maintenue sont deux besoins différents.
8. **Tester directement une fonction qui dépend d'un Singleton sans contrôler le Singleton.** Tu testes alors aussi l'environnement et l'état global.
9. **Oublier l'état reçu dans un Composite.** Un enfant peut fonctionner seul tout en étant incorrect dans une hiérarchie.
10. **Utiliser un nombre de méthodes sans expliquer la convention.** Les surcharges et destructeurs peuvent modifier les comptes.
11. **Conclure qu'une façade est mauvaise parce qu'elle est longue.** Il faut examiner les responsabilités, usages et méthodes provisoires.
12. **Forcer un motif dans l'exercice 10.** Deux switches ne prouvent pas automatiquement une duplication qui mérite une abstraction.
13. **Inventer les mesures qui manquent.** Si la capture n'est pas produite, écris-le et utilise la sonde numérique ; si un hook ne survient pas, explique la condition qui aurait dû le déclencher.

---

# 18. Lexique français / anglais à connaître

| Français | Anglais | Sens dans ce Sprint |
|---|---|---|
| Motif de conception | Design pattern | Solution générale à un problème récurrent de conception. |
| Stratégie | Strategy | Comportement interchangeable. |
| Fabrique | Factory | Création centralisée d'objets. |
| Façade | Facade | Interface simplifiée sur un sous-système complexe. |
| Patron de méthode | Template Method | Squelette algorithmique fixe et étapes personnalisables. |
| Observateur | Observer | Abonnés notifiés d'un événement. |
| Singleton | Singleton | Instance unique et point d'accès commun. |
| Adaptateur | Adapter | Traduction entre deux interfaces. |
| Composite | Composite | Hiérarchie d'objets traités de manière uniforme. |
| Commande | Command | Action encapsulée comme un objet. |
| Backend / dorsal | Backend | Implémentation qui réalise le rendu sur une API ou une plateforme donnée. |
| Hook / crochet | Hook | Méthode redéfinissable appelée par la classe de base. |
| Pure virtual | Virtuelle pure | Méthode `virtual ... = 0`. |
| Override | Override | Redéfinition d'une méthode virtuelle héritée. |
| Draw list | Liste de dessin | Liste structurée de sommets, indices et commandes de dessin. |
| Framebuffer | Framebuffer | Cible mémoire dans laquelle le rendu produit des pixels. |
| Rasterisation | Rasterization | Conversion de primitives géométriques en pixels. |
| Transform | Transformation | Translation, rotation, échelle et composition associée. |
| Allocateur | Allocator | Mécanisme de gestion de la mémoire allouée. |
| Dispatch | Dispatch | Acheminement d'un événement vers le gestionnaire adapté. |
| Consommer un événement | Consume an event | Marquer l'événement traité pour arrêter sa propagation. |
| Injection de dépendance | Dependency injection | Fournir à un composant ce dont il dépend au lieu qu'il le récupère lui-même. |

---

# 19. Conclusions que tu dois être capable d'expliquer à voix haute

À la fin de ta journée, essaie de répondre sans regarder la fiche :

1. Pourquoi une interface commune peut permettre d'échanger plusieurs backends ?
2. Pourquoi 30 méthodes virtuelles pures ne signifient-elles pas que chaque backend écrit nécessairement 30 méthodes ?
3. Pourquoi `NkRenderer2DFactory::Destroy` est-il lié à la règle d'allocateur du moteur ?
4. Pourquoi les mentions de `NkOpenGLRenderer2D` dans des commentaires n'indiquent-elles pas que les clients en dépendent ?
5. Qui décide de l'ordre d'appel des hooks dans le patron de méthode ?
6. Pourquoi un journal de runtime est-il nécessaire si le corps de la boucle n'est pas dans l'en-tête ?
7. Pourquoi une touche maintenue est-elle un cas Pull alors que l'appui sur Échap est un cas Push ?
8. Pourquoi une fonction qui lit `NkInput` directement est plus difficile à tester qu'une fonction qui reçoit `spaceDown` ?
9. Comment `NkGuiCanvasBackend` traduit-il une `NkGuiDrawList` vers `NkIRenderer2D` ?
10. Pourquoi un rasteriseur logiciel peut-il produire des pixels sans fenêtre ni GPU ?
11. Pourquoi un enfant doit-il composer l'état reçu avec son transform local ?
12. Comment peux-tu calculer puis mesurer la position du sprite dans une hiérarchie ?
13. Pourquoi `NkRenderTarget` peut-il être une façade et néanmoins exposer des méthodes avancées ?
14. Pourquoi la méthode `Draw(NkIDrawable2D&)` est-elle explicitement provisoire ?
15. Comment prouver qu'un motif manque vraiment et qu'il vaut son coût ?

Si tu sais expliquer ces quinze points avec tes propres exemples, tu as compris le cœur conceptuel du Sprint.

---

# 20. Limites de cette fiche et ce qui doit venir de ta machine

Cette fiche a été construite à partir :

- des dix énoncés du Sprint 8 que tu as joints ;
- de l'inspection statique des en-têtes du Canvas-kit Windows daté du 22 octobre 2026 ;
- des comptes et recherches reproductibles dans ces en-têtes ;
- des calculs mathématiques explicités pour l'exercice 8.

Dans l'archive inspectée, le dossier du kit contient des en-têtes et des bibliothèques compilées, mais aucun fichier `.cpp` du moteur (42 fichiers présents dans `lib/` ; aucun `.cpp` trouvé dans l'archive extraite). Cela explique pourquoi la fiche peut vérifier les déclarations, les contrats et certaines implémentations inline, mais ne peut pas afficher le corps de toutes les méthodes du moteur.

Les éléments suivants ne sont pas prétendus comme mesurés ici :

- l'ordre exact et les temps réels de tes hooks Debug/Release ;
- le code de sortie réellement produit par ton `banc.cpp` ;
- la position effectivement écrite par tes sondes Composite ;
- l'existence de `capture.png` sur le backend de ta machine ;
- les sorties exactes de ton environnement Windows et de ton compilateur.

Ces résultats sont laissés à mesurer exprès. C'est ce que le professeur évalue : une observation traçable, pas une réponse qui semble plausible.

**Principe final :** un motif donne un nom à une forme de solution ; la lecture du fichier donne la preuve ; le programme et ses mesures montrent le comportement réel ; le jugement de conception explique si cette solution est adaptée et ce qu'elle coûte.
