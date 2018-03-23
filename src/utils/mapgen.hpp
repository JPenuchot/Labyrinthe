#pragma once

#include <functional>
#include <iostream>
#include <vector>
#include <string>
#include <tuple>
#include <map>
#include <set>

#include "../Environnement.h"
#include "../Labyrinthe.h"

namespace labyrinth::utils
{
  using namespace std;

  void parse_level
    ( vector<vector<char>>& mapvec
    , tuple<set<char>, map<char, string>, map<char, int>>& spray_info
    , vector<Wall>& walls
    , Labyrinthe& lab
    )
  {
    Wall wallval = { 0, 0, 0, 0, 0 };
    bool inWall = false;
    
    //  On declare l'action effectuee a la rencontre d'un coin
    //  ici pour alleger la boucle par la suite.
    const auto toggleWall = [&](int x, int y)
    {
      if(inWall)
        { wallval._x2 = x; wallval._y2 = y; walls.push_back(wallval); }
      else
        { wallval._x1 = x; wallval._y1 = y; }
      inWall = !inWall;
    };

    auto addVertTex = [&](int x, int y, int id)
      { cout << "Ajout des textures indisponible." << '\n'; };  //  TODO
    auto addHoriTex = [&](int x, int y, int id)
      { cout << "Ajout des textures indisponible." << '\n'; };  //  TODO

    function<void(int, int, int)> addTex = addHoriTex;

    //  Parcours horizontal
    for(size_t lncnt = 0; lncnt < mapvec.size(); lncnt++)
    {
      for(size_t charcnt = 0; charcnt < mapvec[lncnt].size(); charcnt++)
      {
        auto curr_char = mapvec[lncnt][charcnt];
        lab(lncnt, charcnt) = curr_char;

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
          case Element::empty: break;
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

    addTex = addVertTex;
    for(int j = 0; j < lab.width(); j++)
    {
      for(int i = 0; i < lab.height(); i++)
      {
        //  TODO
      }
    }
  }
};