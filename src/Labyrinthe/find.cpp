#include <algorithm>

#include "../entities/movers/Chasseur.h"
#include "../entities/movers/Gardien.h"
#include "../Labyrinthe.h"

using namespace std;

template<typename T> constexpr double hit_dist2()           { return 1.; }
template<>           constexpr double hit_dist2<Chasseur>() { return 10.; }
template<>           constexpr double hit_dist2<Gardien>()  { return 10.; }

template<>
Chasseur* find<Chasseur>(Labyrinthe& lab, double x, double y)
{
  for(auto h_ptr : lab.hunters)
  { //  TODO : dist
    if(  (int)(h_ptr->_y / (double)Environnement::scale) == (int)y
      && (int)(h_ptr->_x / (double)Environnement::scale) == (int)x
      )
      return h_ptr;
  }
  return nullptr;
}

template<>
Gardien* find<Gardien>(Labyrinthe& lab, double x, double y)
{
  for(auto h_ptr : lab.guardians)
  { //  TODO : dist
    if(  (int)(h_ptr->_y / (double)Environnement::scale) == (int)y
      && (int)(h_ptr->_x / (double)Environnement::scale) == (int)x
      )
      return h_ptr;
  }
  return nullptr;
}

template<>
Wall* find<Wall>(Labyrinthe& lab, double x, double y)
{
  const auto begin = lab._walls;
  const auto end = lab._walls + lab._nwall;
  Wall* ret = nullptr;

  for_each(begin, end, [&](Wall& w){
    if (  ( (w._x1 <= (int)x && (int)x <= w._x2) && ((int)y == w._y1) )
       || ( (w._y1 <= (int)y && (int)y <= w._y2) && ((int)x == w._x1) )
       )
      ret = &w;
  });

  return ret;
}
