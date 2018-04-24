#include <algorithm>

#include "../Labyrinthe.h"

#include "../entities/movers/Chasseur.h"
#include "../entities/movers/Gardien.h"

using namespace std;

//  Distances de contact avec la boule de feu

template<typename T>
T* find_call(Labyrinthe& lab, double x, double y)
  { return find<T>(lab, x, y); }

bool Labyrinthe::hit(double x, double y, Mover& shooter)
{
  //  Lorsqu'on touche un gardien...
  auto hitGuardian = [&](double x, double y)
  {
    Gardien* gdn = find<Gardien>(*this, x, y);
    if(!gdn) return true;

    message("Gotcha, Guardian !");
    gdn->hit();
    return false;
  };

  //  Lorsqu'on touche un chasseur...
  auto hitHunter = [&](double x, double y)
  {
    Chasseur* hun = find<Chasseur>(*this, x, y);
    if(!hun) return true;

    message("Gotcha, Hunter !");
    hun->hit();
    return false;
  };

  //  Lorsqu'on touche un mur...
  auto hitWall = [&](double x, double y) {
    Wall* wal = find<Wall>(*this, x, y);
    if(!wal) return true;

    message("Gotcha, Wall !");
    //  wal->hit();
    return false;
  };

  //  Algo
  return hitWall(x, y) && hitHunter(x, y) && hitGuardian(x, y);
}
