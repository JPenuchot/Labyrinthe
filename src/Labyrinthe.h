#ifndef LABYRINTHE_H
#define LABYRINTHE_H

#include <array>

#include "Environnement.h"

using namespace std;

constexpr size_t LAB_WIDTH  = 80;
constexpr size_t LAB_HEIGHT = 25;

class Labyrinthe : public Environnement {
private:
	array<array<char, LAB_HEIGHT>, LAB_WIDTH>	_data;

public:
	Labyrinthe (char*);
	int width ()   { return LAB_WIDTH;}	// retourne la largeur du labyrinthe.
	int height ()  { return LAB_HEIGHT;}	// retourne la longueur du labyrinthe.
	char data (int i, int j)
	{
		return _data [i][j];
	}	// retourne la case (i, j).
};

#endif
