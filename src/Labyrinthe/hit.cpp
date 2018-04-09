#include <algorithm>

#include "../Labyrinthe.h"

#include "../entities/movers/Chasseur.h"
#include "../entities/movers/Gardien.h"

using namespace std;

void Labyrinthe::hit(int x, int y, Mover& shooter)
{
  //  Lorsqu'on touche un gardien...  
  auto hitGuardian = [&](int i, int j)
  {
    Gardien* gdn = find<Gardien>(i, j);
  };

  //  Lorsqu'on touche un chasseur...
  auto hitHunter = [&](int i, int j)
  {
    Chasseur* hun = find<Chasseur>(i, j);
  };

  //  Lorsqu'on touche un mur...
  auto hitWall = [&](int i, int j)
  { 
    Wall* wal = find<Wall>(i, j);
  };

  //  Le switch sert a brancher sur
  //  les lambdas definies au-dessus
  switch((*this)(y, x))
  {
    case Element::wall_horizontal:
    case Element::wall_vertical:
    case Element::wall_corner:
      hitWall(y, x);
    break;

    case Element::hunter:
      hitHunter(y, x);
    break;

    case Element::guardian:
      hitGuardian(y, x);
    break;
  }
}
