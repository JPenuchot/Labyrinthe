#include <iostream>

#include "../Chasseur.h"
#include "../../../Labyrinthe.h"

using namespace std;

static const double is = 1. / (double)Environnement::scale;

void Chasseur::hit()
{
  message("Hunter hit !");
}