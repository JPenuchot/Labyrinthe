#pragma once

#include <set>
#include <vector>
#include <iostream>

#include "Environnement.h"

#include "entities/movers.hpp"

using namespace std;

enum Element {
  //  Labyrinth walls
  wall_corner     = '+',
  wall_vertical   = '|',
  wall_horizontal = '-',

  //  NPCs
  hunter          = 'C',
  guardian        = 'G',

  //  Map elements
  box             = 'x',
  treasure        = 'T',

  //  Emptiness...
  empty           = ' '
};

using hit_info_t = Element;

class Labyrinthe : public Environnement {
private:
  vector<char>  table;
  vector<int>   distmap;

  set<char> text_ids;

  vector<Gardien*>   guardians;
  vector<Chasseur*>  hunters;

  size_t w;
  size_t h;

public:
  Labyrinthe (char*);

  int width  () { return w; }
  int height () { return h; }

  inline char& operator()      (int i, int j)  { return table[i * w + j]; }
  inline int dist_to_treasure  (int i, int j)  { return distmap[i * w + j]; }

  void dump();

  /**
   * @brief      Dans le cas d'une collision, permet de trouver
   * l'objet touche a la case (i,j) (type renseigne par la map)
   *
   * @param[in]  i     Hauteur
   * @param[in]  j     Largeur
   *
   * @tparam     T     Type de l'objet recherche
   *
   * @return     Pointeur vers l'objet recherche,
   * nullptr si rien trouve.
   */
  template <typename T>
  friend T* findInLab (Labyrinthe& lab, double x, double y);

  ~Labyrinthe() { }

  inline bool isWall(char e)
  {
    return e == Element::wall_corner
        || e == Element::wall_horizontal
        || e == Element::wall_vertical
        || e == Element::box
        || e == Element::treasure
        || text_ids.find(e) != text_ids.end()
        ;
  }
};

template <typename T>
T* findInLab (Labyrinthe& lab, double x, double y) { return nullptr; }

template <> Chasseur* findInLab<Chasseur> (Labyrinthe& lab, double x, double y);
template <> Gardien*  findInLab<Gardien>  (Labyrinthe& lab, double x, double y);
template <> Wall*     findInLab<Wall>     (Labyrinthe& lab, double x, double y);
template <> Box*      findInLab<Box>      (Labyrinthe& lab, double x, double y);
