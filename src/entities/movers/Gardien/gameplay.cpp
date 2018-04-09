#include <iostream>

#include "../Gardien.h"
#include "../../../Labyrinthe.h"

using namespace std;

static const double is = 1. / (double)Environnement::scale;

void Gardien::hit()
{
  message("Guardian hit !");
}