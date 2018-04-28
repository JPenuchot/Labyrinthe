#include <iostream>

#include "../Gardien.h"
#include "../../../Labyrinthe.h"

using namespace std;

const double is = 1. / (double)Environnement::scale;

/*
 *  Fait bouger la boule de feu
 */
bool Gardien::process_fireball (float dx, float dy)
{
  float x = ( _fb->get_x() + dx ) * is;
  float y = ( _fb->get_y() + dy ) * is;

  //  Lorsqu'on touche un chasseur...
  auto detectHunterCollision = [&]()
  {
    Chasseur* cha = findInLab<Chasseur>(*lab, x, y);
    if(!cha) return true;

    message("Guardian hit a Hunter !");
    cha->hit();
    return false;
  };

  //  Lorsqu'on touche un mur...
  auto detectWallCollision = [&]()
  {
    Wall* wal = findInLab<Wall>(*lab, x, y);
    if(!wal) return true;

    message("Guardian hit a Wall !");

    return false;
  };

  auto detectBoxCollision = [&]()
  {
    Box* box = findInLab<Box>(*lab, x, y);
    if(!box) return true;

    message("Guardian hit a box !");

    return false;
  };

  //  Algo
  return detectWallCollision    ()
      && detectHunterCollision  ()
      && detectBoxCollision     ()
      ;
}

/*
 *  Tire sur un ennemi.
 */
void Gardien::fire(int angle_vertical)
{
  _fb->init(_x, _y, 10., angle_vertical, _angle);
}
