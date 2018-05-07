#include <cmath>

#include "../Gardien.h"
#include "../../../Labyrinthe.h"

#ifndef M_PI
  #define M_PI  3.141592653589793238462643383279502884 /* pi */
#endif

using namespace std;

inline bool Gardien::move_aux (double dx, double dy)
{
  double nx = _x + dx;
  double ny = _y + dy;

  int ni = ny / (double)Environnement::scale;
  int nj = nx / (double)Environnement::scale;

  if(lab->walkable(ni, nj))
  {
    this->_x = nx;
    this->_y = ny;

    //  Update de l'angle
    this->_angle = ((atan2(dx, dy) * M_PI) / (2.f * M_PI)) * 360.f;

    return true;
  }
  return false;
}

bool Gardien::move (double dx, double dy)
  { return move_aux (dx, dy) || move_aux (dx, 0.0) || move_aux (0.0, dy); }
