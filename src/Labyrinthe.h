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

  //  Other
  empty           = ' '
};

class Labyrinthe : public Environnement {
private:
	vector<char> table;

  vector<Wall>  wall_vec;
  vector<Wall>  picts_vec;
  vector<Box>   boxes_vec;
  vector<Mover> guardians_vec;
  Box   treasure;

  size_t w;
  size_t h;

public:
	Labyrinthe (char*);
	int width  ()            { return w; }
	int height ()            { return h; }
	char data (int i, int j) { return table[i * w + j]; }
  char& operator() (int i, int j) { return table[i * w + j]; }
};
