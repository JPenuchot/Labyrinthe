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
- Textures
- Gestion de la vie
- Détection de l'entité précise sur laquelle on tire
- Suppression d'entités quelconques
- Pathfinding optimisé (A\*)
- Collisions

### Ce qui ne marche pas

- Déplacements buggés (collisions avec les coins, sûrement à cause de l'angle de déplacement)
- Niveaux de difficultés
- Tirs automatiques sur le chasseur
- Réseau

## Précisions sur le code

### Utilisation de C++ moderne

Nous avons utilisé intensivement la STL dans tout le programme : lambdas, fonctions templates, std::regex. L'accent a donc été mis sur la qualité et la lisibilité du code.

L'algorithme de pathfinding illustre cet exemple : l'algorithme repose sur la structure std::priority_queue qui implémente un tas paramétrable par le type contenu et la fonction de comparaison. La fonction de comparaison, elle, compare de manière dynamique non pas le coût d'un chemin (comme dans Dijkstra) mais directement la somme du coût du chemin et de l'heuristique (minimisante).

Dans mapgen également, les lambdas sont utilisées de manière intensive pour nommer des actions répétées à travers l'algorithme au début de la fonction, pour avoir un "coeur algorithmique" plus clair et concis par la suite.

Les lambdas permettent donc de décrire des actions locales de manière plus légère et contextuelle que des fonctions externes, permettant de rendre les algorithmes plus clairs, d'éviter des bugs (en factorisant) et optimisés (les lambdas sont très bien optimisées par le compilateur, le plus souvent inlinées).

### Autres

Nous nous sommes rendus compte que Environnement::data(i, j) n'était jamais linkée... Nous nous sommes donc passés.
