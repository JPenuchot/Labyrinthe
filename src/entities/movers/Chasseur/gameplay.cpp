#include <iostream>

#include "../Chasseur.h"
#include "../../../Labyrinthe.h"

using namespace std;

void Chasseur::hit()
{
  message("Hunter hit !");
  this->setLife(10);
  if(this->getLife() <= 0) this->die();
}

void Chasseur::die()
{
	message("Hunter is die ! ");
	this->lab->remove(this);
	delete this;
}
