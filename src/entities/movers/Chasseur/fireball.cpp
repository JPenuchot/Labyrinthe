#include <iostream>

#include "../Chasseur.h"
#include "../../../Labyrinthe.h"

using namespace std;

const double is = 1. / (double)Environnement::scale;

/*
 *  Fait bouger la boule de feu
 */
bool Chasseur::process_fireball(float dx, float dy)
{
  float x = ( _fb->get_x() + dx ) * is;
  float y = ( _fb->get_y() + dy ) * is;

  return lab->hit(x, y, *this);
}

/*
 *  Tire sur un ennemi.
 */
void Chasseur::fire(int angle_vertical)
{
  _hunter_fire->play();
  _fb->init(_x, _y, 10., angle_vertical, _angle);
}
