#include "../Chasseur.h"
#include "../../../Labyrinthe.h"

using namespace std;

bool Chasseur::move_aux (double dx, double dy)
{
  auto i = _y / (double)Environnement::scale;
  auto j = _x / (double)Environnement::scale;

  auto nx = _x + dx;
  auto ny = _y + dy;

  auto ni = ny / (double)Environnement::scale;
  auto nj = nx / (double)Environnement::scale;

  if(lab->walkable(ni, nj))
  {
    //  Update de la position
    _x = nx;
    _y = ny;

    return true;
  }
  return false;
}

bool Chasseur::move (double dx, double dy)
  { return move_aux (dx, dy) || move_aux (dx, 0.0) || move_aux (0.0, dy); }
