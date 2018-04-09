#pragma once

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
  empty           = EMPTY
};

class Labyrinthe : public Environnement {
private:
  vector<char>  table;
  vector<int>   distmap;

  vector<Gardien*>   guardians;
  vector<Chasseur*>  hunters;

  size_t w;
  size_t h;

public:
  Labyrinthe (char*);

  int width  ()                         { return w; }
  int height ()                         { return h; }

  char& operator()      (int i, int j)  { return table[i * w + j]; }
  int dist_to_treasure  (int i, int j)  { return distmap[i * w + j]; }

  ~Labyrinthe() { }

  static bool isWall(char e)
  {
    return e == Element::wall_corner
        || e == Element::wall_horizontal
        || e == Element::wall_vertical
        || e == Element::box
        || e == Element::treasure
      ;
  }
};
