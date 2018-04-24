#include <algorithm>

#include "../Labyrinthe.h"

#include "../entities/movers/Chasseur.h"
#include "../entities/movers/Gardien.h"

using namespace std;

bool Labyrinthe::hit(double x, double y, Mover& shooter)
{
  //  Lorsqu'on touche un chasseur...
  auto detectHunterCollision = [&]()
  {
    Chasseur* hun = find<Chasseur>(*this, x, y);
    if(!hun) return true;

    message("Gotcha, Hunter !");
    hun->hit();
    return false;
  };

  //  Lorsqu'on touche un mur...
  auto detectWallCollision = [&]()
  {
    Wall* wal = find<Wall>(*this, x, y);
    if(!wal) return true;

    message("Gotcha, Wall !");

    return false;
  };

  auto detectBoxCollision = [&]()
  {
    Box* box = find<Box>(*this, x, y);
    if(!box) return true;

    message("Gotcha, box !");

    return false;
  };

  auto detectTreasureCollision = [&]()
  {

    return false;
  };

  //  Algo
  return detectWallCollision      ()
      && detectHunterCollision    ()
      && detectBoxCollision       ()
      //&& detectTreasureCollision  ()
      ;
}
