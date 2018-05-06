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

  if(lab->walkable(ni, nj))
  {
    _x = nx;
    _y = ny;

    return true;
  }
  return false;
}

bool Gardien::move (double dx, double dy)
  { return move_aux (dx, dy) || move_aux (dx, 0.0) || move_aux (0.0, dy); }
