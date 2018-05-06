#include <iostream>

#include "../Gardien.h"
#include "../../../Labyrinthe.h"

using namespace std;

void Gardien::hit()
{
  message("Guardian hit !");
  this->setHealth(this->getHealth() - 4.f);
  if(this->getHealth() <= 0) this->die();
}

void Gardien::die()
{
  message("Guardian died !");
  this->lab->remove(this);
  delete this;
}
