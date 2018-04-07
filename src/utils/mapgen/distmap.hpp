#pragma once

#include <tuple>
#include <queue>

#include "../../Labyrinthe.h"

namespace labyrinth::mapgen
{
  void distmap(Labyrinthe& lab, vector<int>& res)
  {
    using namespace std;

    //  On definit localement un type designant une position
    using pos_t = pair<int, int>;

    pos_t init_pos = make_pair(lab._treasor._y, lab._treasor._x);

    vector<bool> visited(lab.width() * lab.height(), false);
    res.resize(lab.width() * lab.height(), -1);

    //  Les lambdas suivantes nous permettent d'alleger la suite du code
    //  pour rendre l'algorithme plus lisible. Elles permettent egalement
    //  de factoriser des calculs pour faciliter les modifications et eviter
    //  des erreurs de repetition.

    //  Retourne pour des coordonnees (i,j) la position dans un vecteur
    //  correspondant a la map.
    auto ij_to_id   = [&](int i, int j) { return i * lab.width() + j; };

    //  Idem avec un type pos
    auto pos_to_id  = [&](pos_t p) { return p.first * lab.width() + p.second; };

    //  Retourne une reference a l'element de coordonnees p
    //  dans le vecteur res
    auto access_res     = [&](pos_t p) -> vector<int>::reference
      { return res[pos_to_id(p)]; };

    //  Retourne une reference a l'element de coordonnees p
    //  dans le vecteur visited
    auto access_visited = [&](pos_t p) -> vector<bool>::reference
      { return visited[pos_to_id(p)]; };

    //  Retourne une reference a l'element de coordonnees p
    //  dans le labyrinthe
    auto access_lab = [&](pos_t p) -> vector<char>::reference
      { return lab(p.first, p.second); };

    queue<pos_t> pos_queue;
    pos_queue.push(init_pos);
    access_res(init_pos) = 0;

    //  Parcours DFS
    while(!pos_queue.empty())
    {
      //  On recupere la position courante et la distance au tresor courante
      auto curr_pos = pos_queue.front();
      auto curr_dist = access_res(curr_pos);
      pos_queue.pop();

      //  On initialise les voisins
      array<pos_t, 4> neighbors =
      {
        make_pair(curr_pos.first - 1, curr_pos.second), //  Up
        make_pair(curr_pos.first + 1, curr_pos.second), //  Down
        make_pair(curr_pos.first, curr_pos.second - 1), //  Left
        make_pair(curr_pos.first, curr_pos.second + 1)  //  Right
      };

      //  Pour chaque voisin...
      for (auto& p : neighbors)
      {
        //  On filtre les murs
        if ( Labyrinthe::isWall(access_lab(p))
          || access_visited(p)
          || !(0 <= p.first && p.first < lab.height())
          || !(0 <= p.second && p.second < lab.width())
          ) continue;

        //  On met a jour la distance au tresor de la case
        access_res(p) = curr_dist + 1;
        access_visited(p) = true;
        
        //  On enfile la position
        pos_queue.push(p);
      }
    }
  }
}