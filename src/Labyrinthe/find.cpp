#include <algorithm>

#include "../entities/movers/Chasseur.h"
#include "../entities/movers/Gardien.h"
#include "../Labyrinthe.h"

using namespace std;

template<>
Chasseur* Labyrinthe::find<Chasseur>(int x, int y)
{
  for(auto h_ptr : this->hunters)
    if(  (int)(h_ptr->_y / (float)Environnement::scale) == y
      && (int)(h_ptr->_x / (float)Environnement::scale) == x )
      return h_ptr;
  return nullptr;
}

template<>
Gardien* Labyrinthe::find<Gardien>(int x, int y)
{
  for(auto h_ptr : this->guardians)
    if(  (int)(h_ptr->_y / (float)Environnement::scale) == y
      && (int)(h_ptr->_x / (float)Environnement::scale) == x )
      return h_ptr;
  return nullptr;
}

template<>
Wall* Labyrinthe::find<Wall>(int x, int y)
{
  const auto begin = _walls;
  const auto end = _walls + _nwall;
  Wall* ret = nullptr;

  for_each(begin, end, [&](Wall& w){
    if ( (w._x1 <= x && x <= w._x2)
      || (w._y1 <= y && y <= w._y2) )
      ret = &w;
  });

  return ret;
}
