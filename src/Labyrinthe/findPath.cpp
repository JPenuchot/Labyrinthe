#include <tuple>
#include <queue>
#include <map>

#include "../Labyrinthe.h"

using namespace std;

bool Labyrinthe::findPath(pos_int from, pos_int to, queue<pos_int>& res)
{
  /**
   * Implémentation de l'algorithme A*
   */

  //  Retourne les 4 voisins d'une position
  auto neighborsOf = [](pos_int& p)
  {
    return array<pos_int, 4> (
      { make_pair(p.first + 1, p.second)
      , make_pair(p.first - 1, p.second)
      , make_pair(p.first, p.second + 1)
      , make_pair(p.first, p.second - 1)
      });
  };

  //  Heuristique
  auto h = [](pos_int& a, pos_int& b)
  {
    float dx = b.first - a.first, dy = b.second - a.second;
    return (dx * dx) + (dy * dy);
  };

  //  Stockage des coûts
  map<pos_int, int> costMap;

  //  Comparateur (coût + heuristique d'une arête)
  auto cmp = [&](pos_int& a, pos_int& b)
  {
    return (costMap[a] + h(a, from)) > (costMap[b] + h(b, from));
  };

  //  Queue
  priority_queue<pos_int, vector<pos_int>, decltype(cmp)> q(cmp);

  //  On commence de la destination
  //  (le résultat sera rempli depuis la destination)
  q.push(to);
  costMap[to] = 0;

  //  L'algo
  while((!q.empty()) && costMap.find(from) == costMap.end())
  {
    //  On défile la position (avec priority_queue et le comparateur maison,
    //  on obtient donc celle qui a la somme coût + heuristique la plus faible)
    auto curr_pos  = q.top();
    auto curr_cost = costMap[curr_pos];
    q.pop();

    //  On définit l'ensemble des voisins
    auto neighbors = neighborsOf(curr_pos);

    for(auto& n : neighbors)
    {
      //  On saute les murs et les éléments déjà vus
      if(   !isValid(n) || (!this->walkable(n))
        ||  costMap.find(n) != costMap.end() )
        continue;

      //  On définit le coût du sommet (de la case)
      costMap[n] = curr_cost + 1;

      //  On ajoute à la priority_queue qui se charge de calculer la somme
      //  coût + heuristique grâce au comparateur cmp
      q.push(n);
    }
  }

  //  Si on n'a aucun chemin (pas trouvé from depuis to), on renvoie false
  if(costMap.find(from) == costMap.end())
    return false;

  //  Backtrack : on part de from et on remonte jusqu'à "to"

  //  On part de la destination et on remonte jusqu'à l'origine
  //  (rappel : elles ont été inversées pour que le chemin soit
  //            enfilé dans le bon ordre)

  auto next = from;

  //  Tant qu'on ne tombe pas sur l'origine...
  while(next != to)
  {
    auto curr_cost = costMap[next];
    auto neighbors = neighborsOf(next);

    //  Pour chaque voisin (sauf si non exploré) on prend celui
    //  qui se rapproche le plus de l'origine
    for(auto& n : neighbors)
      if( costMap.find(n) != costMap.end() && costMap[n] <= costMap[next] )
        next = n;

    //  On ajoute la position en cours au résultat
    res.push(next);
  }

  //  On a trouvé le chemin, on renvoie true
  return true;
}
