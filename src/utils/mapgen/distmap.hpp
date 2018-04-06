#pragma once

#include <tuple>

#include "../../Labyrinthe.h"

namespace labyrinth::mapgen
{
  template<typename T>
  using annotated_type = pair<T, string>;
  
  void distmap(Labyrinthe& lab, vector<int>& res)
  {
    using namespace std;

    pos_t pos = make_pair(lab._treasor._x, lab._treasor._y);

    vector<bool> visited(lab.width() * lab.height(), false);
    res.resize(lab.width() * lab.height(), -1);

    auto access_res = [&](int i, int j) -> vector<int>::reference
      { return res[i * lab.width() + j]; };

    auto access_visited = [&](int i, int j) -> vector<bool>::reference
      { return visited[i * lab.width() + j]; };


  }
}