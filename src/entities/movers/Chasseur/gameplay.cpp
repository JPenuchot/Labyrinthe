#include <iostream>

#include "../Chasseur.h"
#include "../../../Labyrinthe.h"

using namespace std;

void Chasseur::hit()
{
  message("Hunter hit !");
  this->setHealth(this->getHealth() - 10.f);
  if(this->getHealth() <= 0) this->die();
}

void Chasseur::die()
{
	message("Hunter died !");
	this->lab->remove(this);
	delete this;
}
