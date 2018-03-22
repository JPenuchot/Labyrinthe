#pragma once

#include <vector>
#include <string>
#include <iostream>

#include "../Environnement.h"

namespace labyrinth::utils
{
  using namespace std;

  void parse_level
    ( vector<vector<char>>& mapvec
    , vector<string>& maptxt
    , vector<Wall>& res
    )
  {
    Wall wallval = { 0, 0, 0, 0, 0 };
    bool inWall = false;

    int max_hori = 0;
    
    //  Action effectuée à la rencontre d'un coin de mur
    const auto toggleWall = [&](int x, int y)
    {
      if(inWall) 
      {
        wallval._x2 = x; wallval._y2 = y;
        res.push_back(wallval);
        inWall = !inWall;
      }
      else
      {
        wallval._x1 = x; wallval._y1 = y;
        inWall = !inWall;
      }
    };

    auto addVertTex = [&](int x, int y, int id)
      { cout << "Ajout des textures indisponible." << '\n'; };  //  TODO
    auto addHoriTex = [&](int x, int y, int id)
      { cout << "Ajout des textures indisponible." << '\n'; };  //  TODO
    
    //  Parcours horizontal
    for(size_t lncnt = 0; lncnt < mapvec.size(); lncnt++)
    {
      max_hori = max_hori < mapvec[lncnt].size()
        ? mapvec[lncnt].size()
        : max_hori;

      for(size_t charcnt = 0; charcnt < mapvec[lncnt].size(); charcnt++)
      {
        auto curr_char = mapvec[lncnt][charcnt];
        switch(curr_char)
        {
          case Element::wall_corner: {
            toggleWall(lncnt, charcnt);
          } break;
          case Element::hunter: {
            cout << "Ajout des chasseurs indisponible." << '\n';  //  TODO
          } break;
          case Element::guardian: {
            cout << "Ajout des gardiens indisponible." << '\n';   //  TODO
          } break;
          case Element::treasure: {
            cout << "Ajout des tresors indisponible." << '\n';    //  TODO
          } break;
          
          default: {
            cout << "Lecture de caractere arbitraire : TODO" << '\n'; //  TODO
          } break;

        }
      }
    }

    //  Parcours vertical


  }
};