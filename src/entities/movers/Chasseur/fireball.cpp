#include <iostream>

#include "../Chasseur.h"

#include "../../../Labyrinthe.h"

using namespace std;

const double is = 1. / (double)Environnement::scale;

/*
 *  Fait bouger la boule de feu
 */
bool Chasseur::process_fireball(float dx, float dy)
{
  float x = ( _fb->get_x() + dx ) * is;
  float y = ( _fb->get_y() + dy ) * is;

  //  Lorsqu'on touche un chasseur...
  auto detectGuardianCollision = [&]()
  {
    Gardien* gar = findInLab<Gardien>(*lab, x, y);
    if(!gar) return true;

    gar->hit(); 
    return false;
  };

  //  Lorsqu'on touche un mur...
  auto detectWallCollision = [&]()
  {
    Wall* wal = findInLab<Wall>(*lab, x, y);
    if(!wal) return true;

    message("Gotcha, Wall !");

    this->lab->remove(wal);

    return false;
  };

  auto detectBoxCollision = [&]()
  {
    Box* box = findInLab<Box>(*lab, x, y);
    if(!box) return true;

    message("Gotcha, box !");

    this->lab->remove(box);

    return false;
  };

  //  Algo
  return detectWallCollision      ()
      && detectGuardianCollision  ()
      && detectBoxCollision       ()
      ;
}

/*
 *  Tire sur un ennemi.
 */
void Chasseur::fire(int angle_vertical)
{
  _hunter_fire->play();
  _fb->init(_x, _y, 10., angle_vertical, _angle);
}
