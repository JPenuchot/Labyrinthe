#include "../Gardien.h"
#include "../../../Labyrinthe.h"

using namespace std;

Gardien::Gardien(int x, int y, Labyrinthe* l):
Mover(x, y, l, modmarv), lab(l) {}

/**
 * @brief      On verra bien...
 *
 * @param[in]  shift    Vrai si SHIFT pressée
 * @param[in]  control  Vrai si CONTROL pressée
 */
void Gardien::right_click (bool shift, bool control){ message("Right click"); }

float Gardien::getHealth() {
	return this->health;
}

void Gardien::setHealth(float decrease) {
	this->health -= decrease;
}
