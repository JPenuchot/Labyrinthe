#include <algorithm>

#include "../../Labyrinthe.h"

#include "../../entities/movers/Chasseur.h"
#include "../../entities/movers/Gardien.h"

using namespace std;

template<>
Chasseur* findInLab<Chasseur>(Labyrinthe& lab, double x, double y)
{
  for(auto h_ptr : lab.hunters)
  { //  TODO : dist ?
    if(  (int)(h_ptr->_x / (double)Environnement::scale) == (int)x
      && (int)(h_ptr->_y / (double)Environnement::scale) == (int)y
      )
      return h_ptr;
  }
  return nullptr;
}

template<>
Gardien* findInLab<Gardien>(Labyrinthe& lab, double x, double y)
{
  for(auto h_ptr : lab.guardians)
  { //  TODO : dist ?
    if(  (int)(h_ptr->_x / (double)Environnement::scale) == (int)x
      && (int)(h_ptr->_y / (double)Environnement::scale) == (int)y
      )
      return h_ptr;
  }
  return nullptr;
}

template<>
Wall* findInLab<Wall>(Labyrinthe& lab, double x, double y)
{
  //  On cast x et y dans des int
  int xi = x;
  int yi = y;

  const auto begin  = lab._walls;
  const auto end    = lab._walls + lab._nwall;

  auto ret = find_if(begin, end, [&](Wall& w)
  {
    return  (  ( (w._x1 <= xi && xi <= w._x2) && (yi == w._y1) )
            || ( (w._y1 <= yi && yi <= w._y2) && (xi == w._x1) ) );
  });

  return ret == end ? nullptr : ret;
}

template<>
Box* findInLab<Box>(Labyrinthe& lab, double x, double y)
{
  //  On cast x et y dans des int
  int xi = x;
  int yi = y;

  const auto begin  = lab._boxes;
  const auto end    = lab._boxes + lab._nboxes;

  auto ret = find_if(begin, end, [&](Box& b)
    { return b._x == xi && yi == b._y; });

  return ret == end ? nullptr : ret;
}
