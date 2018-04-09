#include <iostream>

#include "../Gardien.h"
#include "../../../Labyrinthe.h"

using namespace std;

static const double is = 1. / (double)Environnement::scale;

//  DESC
bool Gardien::process_fireball (float dx, float dy)
{
  message("...");

  float x = ( _fb->get_x() + dx ) * is;
  float y = ( _fb->get_y() + dy ) * is;

  // on bouge que dans le vide!
  if ( Element::empty == (*lab)( (int)y , (int)x ) )
    { return true; }

  lab->hit(x, y, *this);

  return false;
}

//  DESC
void Gardien::fire (int angle_vertical)
  { _fb->init(_x, _y, 10., angle_vertical, _angle); }
