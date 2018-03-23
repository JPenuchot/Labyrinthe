#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <tuple>
#include <map>
#include <set>

#include "../Environnement.h"

namespace labyrinth::utils
{
  using namespace std;

  void parse_level
    ( vector<vector<char>>& mapvec
    , vector<string>& maptxt  
    , tuple<set<char>, map<char, string>, map<char, int>>& spray_info
    , vector<Wall>& walls
    )
  {
    Wall wallval = { 0, 0, 0, 0, 0 };
    bool inWall = false;
    
    //  Détermine la borne du labyrinthe
    int begin_x = -1;

    int max_hori = 0;
    
    //  On déclare l'action effectuée à la rencontre d'un coin
    //  ici pour alléger la boucle par la suite.
    const auto toggleWall = [&](int x, int y)
    {
      cout << "Ajout de mur...\n";
      if(inWall)
      {
        wallval._x2 = x - begin_x; wallval._y2 = y;
        walls.push_back(wallval);
        inWall = !inWall;
      }
      else
      {
        //  On détermine la borne du labyrinthe (une fois seulement)
        begin_x = begin_x == -1 ? x : begin_x;

        wallval._x1 = x - begin_x; wallval._y1 = y;
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
      //  On vérifie que ce n'est pas une ligne d'infos

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

        //  On retourne une erreur si on n'a pas vu
        //  de coin de mur avant la fin de la ligne
        if(inWall) throw runtime_error("lol");
      }
    }

    //  Parcours vertical


  }
};