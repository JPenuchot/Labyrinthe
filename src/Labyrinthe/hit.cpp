#include <algorithm>

#include "../Labyrinthe.h"

#include "../entities/movers/Chasseur.h"
#include "../entities/movers/Gardien.h"

using namespace std;

void Labyrinthe::hit(int x, int y, Mover& shooter)
{
  //  Lorsqu'on touche un gardien...  
  auto hitGuardian = [&](int x, int y)
  {
    message("Gardien");
    Gardien* gdn = find<Gardien>(x, y);
    gdn->hit();
  };

  //  Lorsqu'on touche un chasseur...
  auto hitHunter = [&](int x, int y)
  {
    message("Chasseur");
    Chasseur* hun = find<Chasseur>(x, y);
    hun->hit();
  };

  //  Lorsqu'on touche un mur...
  auto hitWall = [&](int x, int y)
  { 
    message("Mur");
    Wall* wal = find<Wall>(x, y);
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
