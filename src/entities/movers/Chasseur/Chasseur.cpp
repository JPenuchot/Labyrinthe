#include <iostream>

#include "../Chasseur.h"
#include "../../../Labyrinthe.h"

using namespace std;


/*
 *  Constructeur.
 */

Chasseur::Chasseur (int x, int y, Labyrinthe* l):
Mover (x, y, l, "Marvin"),
lab(l)
{
  if(!_hunter_fire) _hunter_fire  = new Sound ("sons/hunter_fire.wav");
  if(!_hunter_hit)  _hunter_hit   = new Sound ("sons/hunter_hit.wav");
  if(!_wall_hit)    _wall_hit     = new Sound ("sons/hit_wall.wav");
}

float Chasseur::getLife() {
	return this->life;
}

void Chasseur::setLife(float decrease) {
	this->life -= decrease;
}

