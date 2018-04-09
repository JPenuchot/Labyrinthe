#include <iostream>

#include "../Chasseur.h"
#include "../../../Labyrinthe.h"

using namespace std;

static const double is = 1. / (double)Environnement::scale;

/*
 *  Tente un deplacement.
 */
bool Chasseur::move_aux (double dx, double dy)
{
  if(Element::empty == (*lab) ( (int)((_y + dy)  * is)
                              , (int)((_x + dx)  * is) ) )
  {
    auto self = (*lab)(_y, _x);
    (*lab)(_y, _x) = Element::empty;

    _x += dx;
    _y += dy;

    (*lab)(_y, _x) = self;

    return true;
  }
  return false;
}
