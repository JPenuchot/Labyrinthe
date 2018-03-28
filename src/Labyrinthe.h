#pragma once

#include <vector>

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
  empty           = ' '
};

class Labyrinthe : public Environnement {
private:
  vector<char> table;

  size_t w;
  size_t h;

public:
  Labyrinthe (char*);
  int width  ()                   { return w; }
  int height ()                   { return h; }
  char data (int i, int j)        { return table[i * w + j]; }
  char& operator() (int i, int j) { return table[i * w + j]; }

  ~Labyrinthe() { }
};
