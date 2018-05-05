#include <tuple>
#include <queue>
#include <map>

#include "../Labyrinthe.h"

using namespace std;

void findPath(pos_int from, pos_int to, queue<pos_int>& res)
{
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
  while(!q.empty() && costMap.find(from) == costMap.end())
  {
    auto curr_pos  = q.top();
    auto curr_cost = costMap[curr_pos];

    q.pop();

    //  On définit l'ensemble des voisins
    array<pos_int, 4> neighbors =
      { make_pair( curr_pos.first + 1 , curr_pos.second )
      , make_pair( curr_pos.first - 1 , curr_pos.second )
      , make_pair( curr_pos.first     , curr_pos.second + 1 )
      , make_pair( curr_pos.first     , curr_pos.second - 1 )
      };

    for(auto& n : neighbors)
    {
      //  On saute les éléments déjà vus
      if(costMap.find(n) == costMap.end()) continue;

      //  On définit le coût du sommet (de la case)
      costMap[n] = curr_cost + 1;

      //  On ajoute à la priority_queue qui se charge de calculer la somme
      //  coût + heuristique grâce au comparateur cmp
      q.push(n);
    }
  }

  //  Backtrack : on part de from et on remonte jusqu'à "to"

  auto next = from;
  while(next != to)
  {
    res.push(next);

    array<pos_int, 4> neighbors =
      { make_pair( next.first + 1 , next.second )
      , make_pair( next.first - 1 , next.second )
      , make_pair( next.first     , next.second + 1 )
      , make_pair( next.first     , next.second - 1 )
      };

    auto curr_cost = costMap[next];

    for(auto& n : neighbors)
    {
      if(costMap.find(n) != costMap.end() && costMap[n] < costMap[next])
        next = n;
    }
  }
}
