#pragma once

#include <vector>

#include "Environnement.h"

using namespace std;

class Labyrinthe : public Environnement {
private:
	vector<char> table;
  size_t w;
  size_t h;

public:
	Labyrinthe (char*);
	int width  ()            { return w; }
	int height ()            { return h; }
	char data (int i, int j) { return table[i * w + j]; }
};
