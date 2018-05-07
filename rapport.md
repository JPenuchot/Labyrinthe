# POA - Rapport

Binôme :

- PENUCHOT Jules
- BIARD David

## Requirements

- CMake 2.8 ou plus récent
- Clang 5.0 ou plus récent

**Attention :** Le projet repose sur des fonctionnalités présentes à partir de C++ 17, veillez à compiler le programme avec un compilateur qui les supporte.

## Tour des features

### Ce qui marche

- Chargement des niveaux
- Affiches
- Gestion de la vie
- Détection de l'entité précise sur laquelle on tire
- Suppression d'entités quelconques
- Pathfinding optimal (A\* avec heuristique euclidienne)
- Collisions
- Distance au trésor (pour ajustement de la difficulté)
- Fin du jeu (trésor atteint -> appel d'`exit(0)`)

### Ce qui ne marche pas

- Déplacements buggés (collisions avec les coins, sûrement à cause de l'angle de déplacement)
- Niveaux de difficultés
- Tirs automatiques sur le chasseur
- Réseau

## Précisions sur le code

### Structure du projet, compilation...

La compilation du projet est prise en charge par le script `build.sh` grâce à CMake. Le script `CMakeLists.txt` effectue une recherche récurcive dans `src/` pour récupérer l'intégralité des .cpp et faire de la compilation modulaire. Les objets externes sont spécifiés et linkés dans le `CMakeLists.txt` également.

Les scripts (bash/cmake) sont faits maison (voir https://github.com/JPenuchot/cpp-template).

### Utilisation de C++ moderne

Nous avons utilisé intensivement la STL dans tout le programme : lambdas, fonctions templates, `std::regex`. L'accent a donc été mis sur la qualité et la lisibilité du code.

L'algorithme de pathfinding illustre cet exemple : l'algorithme repose sur la structure `std::priority_queue` qui implémente un tas paramétrable par le type contenu et la fonction de comparaison. La fonction de comparaison, elle, compare de manière dynamique non pas le coût d'un chemin (comme dans Dijkstra) mais directement la somme du coût du chemin et de l'heuristique (minimisante).

Dans mapgen également, les lambdas sont utilisées de manière intensive pour nommer des actions répétées à travers l'algorithme au début de la fonction, pour avoir un "coeur algorithmique" plus clair et concis par la suite.

Les lambdas permettent donc de décrire des actions locales de manière plus légère et contextuelle que des fonctions externes, permettant de rendre les algorithmes plus clairs, d'éviter des bugs (en factorisant) et optimisés (les lambdas sont très bien optimisées par le compilateur, le plus souvent inlinées).

### Types & Abstractions

De nombreuses abstractions ont été faites sur la structure fournie, notamment les pointeurs de gardiens et chasseurs sont stockés dans des `std::vector` pour une meilleure gestion de la mémoire et surtout une distinction des types.

Deux types ont été créés pour représenter les coordonnées (`pos_int` et `pos_float`, créés à partir de `std::pair`) et les abstraire notamment dans les algorithmes de pathfinding.

### Autres

Nous nous sommes rendus compte que Environnement::data(i, j) n'était jamais linkée... Nous nous en sommes donc passés.

La fonction partie_terminee n'étant pas présente dans les headers, elle a été remplacée par `exit(0)`.
