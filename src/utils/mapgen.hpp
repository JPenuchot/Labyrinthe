#pragma once

#include "../Labyrinthe.h"

#include <vector>
#include <tuple>
#include <set>
#include <map>

namespace labyrinth::mapgen
{
  using namespace std;

  void parse_level
    ( vector<vector<char>>&             mapvec
    , pair<set<char>, map<char, int>>&  spray_info
    , Labyrinthe&                       lab

    //  Les tableaux de Environnement
    , vector<Wall>&                     walls
    , vector<Wall>&                     sprites
    , vector<Box>&                      boxes
    , vector<Mover*>&                   movers

    //  Le tresor
    , Box&                              treasure

    //  Les vecteurs de Labyrinthe
    , vector<Gardien*>&                 guardians
    , vector<Chasseur*>&                hunters
    );

  void distmap(Labyrinthe& lab, vector<int>& res);
};
