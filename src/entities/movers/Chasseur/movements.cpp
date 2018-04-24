#include "../Chasseur.h"
#include "../../../Labyrinthe.h"

using namespace std;

/*
 *  Tente un deplacement.
 */
bool Chasseur::move_aux (double dx, double dy)
{
  auto i = _y / (double)Environnement::scale;
  auto j = _x / (double)Environnement::scale;

  auto nx = _x + dx;
  auto ny = _y + dy;

  auto ni = ny / (double)Environnement::scale;
  auto nj = nx / (double)Environnement::scale;

  auto& curr_cell = (*lab)( i,  j);
  auto& next_cell = (*lab)(ni, nj);

  if(!lab->isWall(next_cell))
  {
    //  Update de la position
    _x = nx;
    _y = ny;

    return true;
  }
  return false;
}
