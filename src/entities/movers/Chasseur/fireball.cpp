#include <iostream>

#include "../Chasseur.h"
#include "../../../Labyrinthe.h"

using namespace std;

static const double is = 1. / (double)Environnement::scale;

/*
 *  Fait bouger la boule de feu (ceci est une exemple, a vous de traiter
 *  les collisions specifiques...)
 */
bool Chasseur::process_fireball (float dx, float dy)
{
  message("...");

  //  Calculer la distance entre le chasseur et le lieu de l'explosion.
  float x = (_fb->get_x() + dx) * is;
  float y = (_fb->get_y() + dy) * is;
  
  //  On bouge que dans le vide!
  if ( Element::empty == (*lab)  ( (int)y, (int)x ) )
  { return true; }

  lab->hit(x, y, *this);

  return false;
}

/*
 *  Tire sur un ennemi.
 */
void Chasseur::fire (int angle_vertical)
{
  _hunter_fire->play();
  _fb->init(_x, _y, 10., angle_vertical, _angle);
}
