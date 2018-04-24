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
  //  On cast x et y dans des int
  int xi = x;
  int yi = y;

  const auto begin = lab._walls;
  const auto end = lab._walls + lab._nwall;
  Wall* ret = nullptr;

  for_each(begin, end, [&](Wall& w)
  {
    if (  ( (w._x1 <= xi && xi <= w._x2) && (yi == w._y1) )
       || ( (w._y1 <= yi && yi <= w._y2) && (xi == w._x1) )
       )
      ret = &w;
  });

  return ret;
}

template<>
Box* find<Box>(Labyrinthe& lab, double x, double y)
{
  //  On cast x et y dans des int
  int xi = x;
  int yi = y;

  const auto begin = lab._boxes;
  const auto end = lab._boxes + lab._nboxes;
  Box* ret = nullptr;

  for_each(begin, end, [&](Box& b)
  {
    if ( b._x == xi && yi == b._y )
      ret = &b;
  });

  return ret;
}
