#include <iostream>

#include "../Gardien.h"
#include "../../../Labyrinthe.h"

using namespace std;

const double is = 1. / (double)Environnement::scale;

/*
 *  Fait bouger la boule de feu
 */
bool Gardien::process_fireball (float dx, float dy)
{
  float x = ( _fb->get_x() + dx ) * is;
  float y = ( _fb->get_y() + dy ) * is;

  return lab->hit(x, y, *this);
}

/*
 *  Tire sur un ennemi.
 */
void Gardien::fire (int angle_vertical)
{
  _fb->init(_x, _y, 10., angle_vertical, _angle);
}
