#pragma once

#include <vector>

#include "Environnement.h"

using namespace std;

class Labyrinthe : public Environnement {
private:
	vector<char> table;

  vector<Wall>  wall_vec;
  vector<Wall>  picts_vec;
  vector<Box>   boxes_vec;
  vector<Box>   treasures_vec;
  vector<Mover> guardians_vec;

  size_t w;
  size_t h;

public:
	Labyrinthe (char*);
	int width  ()            { return w; }
	int height ()            { return h; }
	char data (int i, int j) { return table[i * w + j]; }
  char& operator() (int i, int j) { return table[i * w + j]; }
};
