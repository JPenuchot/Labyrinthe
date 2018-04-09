#include <iostream>

#include "../Gardien.h"
#include "../../../Labyrinthe.h"

using namespace std;

static const double is = 1. / (double)Environnement::scale;

inline bool Gardien::move_aux (double dx, double dy)
{
  if(Element::empty == (*lab) ( (int)( (_y + dy) * is )
                              , (int)( (_x + dx) * is ) ) )
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

//  DESC
bool Gardien::move (double dx, double dy)
  { return move_aux (dx, dy) || move_aux (dx, 0.0) || move_aux (0.0, dy); }
