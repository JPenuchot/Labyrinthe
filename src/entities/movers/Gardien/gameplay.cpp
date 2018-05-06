#include <iostream>

#include "../Gardien.h"
#include "../../../Labyrinthe.h"

using namespace std;

void Gardien::hit()
{
  message("Guardian hit !");
  this->setHealth(4);
  if(this->getHealth() <= 0) this->die();
}

void Gardien::die()
{
  message("Guardian is die");
  this->lab->remove(this);
  delete this;
}
