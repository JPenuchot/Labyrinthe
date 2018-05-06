#include <algorithm>

#include "../../Labyrinthe.h"

using namespace std;

bool Labyrinthe::remove(Chasseur* c)
{
  //  Désigne la fin de l'array this->_guards
  auto arr_end = this->_guards + this->_nguards;

  auto pos_in_vec = find(this->hunters.begin(), this->hunters.end(), c);
  auto pos_in_arr = find(this->_guards, arr_end, c);

  if(pos_in_vec == this->hunters.end()) return false;

  //  On retire dans le vector hunters
  this->hunters.erase(pos_in_vec);

  //  On retire dans le tableau de Environnement (en décalant tout)
  copy(pos_in_arr + 1, arr_end, pos_in_arr);
  this->_nguards--;

  return true;
}

bool Labyrinthe::remove(Gardien* g)
{
  //  Désigne la fin de l'array this->_guards
  auto arr_end = this->_guards + this->_nguards;

  auto pos_in_vec = find(this->guardians.begin(), this->guardians.end(), g);
  auto pos_in_arr = find(this->_guards, arr_end, g);

  if(pos_in_vec == this->guardians.end()) return false;

  //  On retire dans le vector guardians
  this->guardians.erase(pos_in_vec);

  //  On retire dans le tableau de Environnement (en décalant tout)
  copy(pos_in_arr + 1, arr_end, pos_in_arr);
  this->_nguards--;

  return true;
}

bool Labyrinthe::remove(Box* b)
{
  auto boxes_end = this->_boxes + this->_nboxes;

  auto pos = find_if(this->_boxes, boxes_end, [&](auto& elmt)
    { return &elmt == b; });
  if(pos == boxes_end) return false;

  //  On retire dans la map
  this->walkable(b->_y, b->_x) = true;

  //  On retire dans le tableau de Environnement (en décalant tout)
  copy(pos + 1, boxes_end, pos);

  //  Appel de reconfigure pour rafaîchir la map...
  this->reconfigure();

  return true;
}

bool Labyrinthe::remove(Wall* w)
{
  auto walls_end = this->_walls + this->_nwall;
  auto pos = find_if(this->_walls, walls_end, [&](auto& elmt)
    { return &elmt == w; });

  if(pos == walls_end) return false;

  //  On retire les traces du mur dans la map
  this->refreshWalkMap();

  //  On retire dans le tableau de Environnement (en décalant tout)
  copy(pos + 1, walls_end, pos);

  //  Appel de reconfigure pour rafaîchir la map...
  this->reconfigure();

  return true;
}
