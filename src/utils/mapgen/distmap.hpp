#pragma once

#include <tuple>
#include <queue>

#include "../../Labyrinthe.h"

namespace labyrinth::mapgen
{
  void distmap(Labyrinthe& lab, vector<int>& res)
  {
    /*
     *  INTRODUCTION
     */

    using namespace std;

    //  Declarations/Allocations

    vector<bool> visited(lab.width() * lab.height(), false);
    res.resize(lab.width() * lab.height(), -1);

    //  Lambdas

    //  On definit localement un type designant une position
    using pos_t = pair<int, int>;

    auto ij_to_id   = [&](int i, int j) { return i * lab.width() + j; };
    auto pos_to_id  = [&](pos_t p) { return p.first * lab.width() + p.second; };

    auto access_res     = [&](pos_t p) -> vector<int>::reference
      { return res[pos_to_id(p)]; };

    auto access_visited = [&](pos_t p) -> vector<bool>::reference
      { return visited[pos_to_id(p)]; };

    auto access_lab     = [&](pos_t p) -> vector<char>::reference
      { return lab(p.first, p.second); };

    /*
     *  ALGORITHME
     */

    //  Initialisation

    pos_t init_pos = make_pair(lab._treasor._y, lab._treasor._x);

    queue<pos_t> pos_queue;
    pos_queue.push(init_pos);

    access_res(init_pos) = 0;
    access_visited(init_pos) = true;

    //  DFS

    while(!pos_queue.empty())
    {
      //  On recupere la position courante et la distance au tresor courante
      auto curr_pos = pos_queue.front();
      auto curr_dist = access_res(curr_pos);
      pos_queue.pop();

      //  On initialise les voisins
      array<pos_t, 4> neighbors =
        {  make_pair(curr_pos.first - 1, curr_pos.second) //  Up
        ,  make_pair(curr_pos.first + 1, curr_pos.second) //  Down
        ,  make_pair(curr_pos.first, curr_pos.second - 1) //  Left
        ,  make_pair(curr_pos.first, curr_pos.second + 1) //  Right
        };

      //  Pour chaque voisin...
      for (auto& n : neighbors)
      {
        //  On filtre les murs et on ne depasse pas les bornes
        if ( !( 0 <= n.first  && n.first  < lab.height() )
          || !( 0 <= n.second && n.second < lab.width()  )
          || Labyrinthe::isWall(access_lab(n))
          || access_visited(n)
           )
          continue;

        //  On met a jour la distance au tresor de la case
        access_res(n) = curr_dist + 1;
        access_visited(n) = true;

        //  On enfile la position
        pos_queue.push(n);
      }
    }
  }
}