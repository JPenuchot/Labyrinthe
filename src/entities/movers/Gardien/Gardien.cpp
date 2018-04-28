#include <iostream>

#include "../Gardien.h"
#include "../../../Labyrinthe.h"

using namespace std;

Gardien::Gardien(int x, int y, Labyrinthe* l):
Mover(x, y, l, modmarv), lab(l) {}

/**
 * @brief      Update du gardien et point d'entrée pour la partie AI du projet
 */
void Gardien::update (void)
{
  if (this->health <= 0.f) this->die();
}

/**
 * @brief      On verra bien...
 *
 * @param[in]  shift    Vrai si SHIFT pressée
 * @param[in]  control  Vrai si CONTROL pressée
 */
void Gardien::right_click (bool shift, bool control){ message("Right click"); }
