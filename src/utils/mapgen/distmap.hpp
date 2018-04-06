#pragma once

#include "../../Labyrinthe.h"

namespace labyrinth::mapgen {
  void distmap(Labyrinthe& lab, vector<int>& res)
  {
    vector<bool> visited(lab.width() * lab.height(), false);
    res.resize(lab.width() * lab.height(), -1);
  }
}