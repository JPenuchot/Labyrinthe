#include <iostream>

#include "../Gardien.h"
#include "../../../Labyrinthe.h"

using namespace std;

inline bool Gardien::move_aux (double dx, double dy)
{
  auto i = _y / (double)Environnement::scale;
  auto j = _x / (double)Environnement::scale;

  auto nx = (_x + dx);
  auto ny = (_y + dy);

  auto ni = ny / (double)Environnement::scale;
  auto nj = nx / (double)Environnement::scale;

  if((*lab)(ni, nj) == Element::empty)
  {
    auto self = (*lab)(i, j);
    (*lab)(i, j) = Element::empty;

    _x = nx;
    _y = ny;

    (*lab)(ni, nj) = self;

    return true;
  }
  return false;
}

//  DESC
bool Gardien::move (double dx, double dy)
  { return move_aux (dx, dy) || move_aux (dx, 0.0) || move_aux (0.0, dy); }
