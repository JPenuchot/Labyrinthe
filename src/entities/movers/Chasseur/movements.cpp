#include "../Chasseur.h"
#include "../../../Labyrinthe.h"

using namespace std;

inline bool Chasseur::move_aux (double dx, double dy)
{
  double nx = _x + dx;
  double ny = _y + dy;

  int ni = ny / Environnement::scale;
  int nj = nx / Environnement::scale;

  if(lab->walkable(ni, nj))
  {
    _x = nx;
    _y = ny;

    if(this->lab->getPlayerPos() == this->lab->getTreasurePos())
      exit(0);

    return true;
  }
  return false;
}

bool Chasseur::move (double dx, double dy)
  { return move_aux (dx, dy) || move_aux (dx, 0.0) || move_aux (0.0, dy); }
