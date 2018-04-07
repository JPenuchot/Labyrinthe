#pragma once

#include <vector>
#include <iostream>

#include "Environnement.h"

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
  vector<char> table;

  size_t w;
  size_t h;

public:
  Labyrinthe (char*);
  
  int width  ()                     { return w; }
  int height ()                     { return h; }

  char data         (int x, int y)  { return table[y * w + x]; }
  char& operator()  (int i, int j)  { return table[i * w + j]; }

  ~Labyrinthe() { }

  static bool isWall(char e)
  {
    return e == Element::wall_corner
        || e == Element::wall_horizontal
        || e == Element::wall_vertical
      ;
  }
};
