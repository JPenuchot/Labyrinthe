#include <tuple>
#include <queue>
#include <map>

#include "../Labyrinthe.h"

using namespace std;

bool Labyrinthe::findPath(pos_int from, pos_int to, queue<pos_int>& res)
{
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
    { return abs(b.first - a.first) + abs(b.second - a.second); };

  //  Stockage des coûts
  map<pos_int, int> costMap;

  //  Comparateur (coût + heuristique d'une arête)
  auto cmp = [&](pos_int& a, pos_int& b)
    { return (costMap[a] + h(a, from)) - (costMap[b] + h(b, from)); };

  //  Queue
  priority_queue<pos_int, vector<pos_int>, decltype(cmp)> q(cmp);

  //  On commence de la destination
  //  (le résultat sera rempli depuis la destination)
  q.push(to);
  costMap[to] = 0;

  //  L'algo
  while((!q.empty()) && costMap.find(from) == costMap.end())
  {
    auto curr_pos  = q.top();
    auto curr_cost = costMap[curr_pos];

    q.pop();

    //  On définit l'ensemble des voisins
    auto neighbors = neighborsOf(curr_pos);

    for(auto& n : neighbors)
    {
      //  On saute les éléments déjà vus
      if ( costMap.find(n) != costMap.end() || !this->walkable(n) )
        continue;

      //  On définit le coût du sommet (de la case)
      costMap[n] = curr_cost + 1;

      //  On ajoute à la priority_queue qui se charge de calculer la somme
      //  coût + heuristique grâce au comparateur cmp
      q.push(n);
    }
  }

  //  Si on n'a aucun chemin...
  if(costMap.find(from) == costMap.end())
    return false;

  //  Backtrack : on part de from et on remonte jusqu'à "to"

  //  On part de la destination et on remonte jusqu'à l'origine
  //  (rappel : elles ont été inversées pour que le chemin soit
  //            enfilé dans le bon ordre)

  auto next = from;
  while(next != to)
  {
    res.push(next);

    auto curr_cost = costMap[next];
    auto neighbors = neighborsOf(next);

    for(auto& n : neighbors)
      if( costMap.find(n) != costMap.end() && costMap[n] < costMap[next] )
        next = n;
  }

  return true;
}
