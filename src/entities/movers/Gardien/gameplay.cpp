#include <iostream>

#include "../Gardien.h"
#include "../../../Labyrinthe.h"

using namespace std;

void Gardien::hit()
{
  message("Guardian hit !");
  this->die();
}

void Gardien::die()
{
  message("F");
  this->lab->remove(this);
}
