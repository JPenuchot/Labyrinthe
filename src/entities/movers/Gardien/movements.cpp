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
    _x = nx;
    _y = ny;

    cout << "(" << _x << "," << _y << ")" << endl;

    float val = atan2(this->get_pos_int().first, this->lab->getPlayerPos().first);
    float val2 = atan2(this->get_pos_int().second, this->lab->getPlayerPos().second);
    val2 += val;
    int val3 = val2*180/M_PI;
    cout << val3 << endl;
    this->_angle = val3;
    
    // this->_angle = 180;

    return true;
  }
  return false;
}

bool Gardien::move (double dx, double dy)
  { return move_aux (dx, dy) || move_aux (dx, 0.0) || move_aux (0.0, dy); }
