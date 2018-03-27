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
#include "../Chasseur.h"
#include "../Mover.h"

namespace labyrinth::utils
{
  using namespace std;

  void parse_level
    ( vector<vector<char>>& mapvec
    , tuple<set<char>, map<char, string>, map<char, int>>& spray_info
    , Labyrinthe&           lab
    , vector<Wall>&         walls
    , vector<Box>&          boxes
    , vector<Mover>&        movers
    , Box&                  treasure
    )
  {    
    auto& charSet = get<0>(spray_info);
    auto& idMap   = get<2>(spray_info);

    /*
     *    1/ PRE-DEFINITION DES ACTIONS
     */

    Wall wallval = { 0, 0, 0, 0, 0 };
    bool inWall = false;

    //  On definit l'action effectuee a la rencontre d'un
    //  coin ici pour alleger les boucles par la suite.
    const auto toggleWall = [&](int x, int y)
    {
      if(!inWall) //  Ouverture du mur
      {
        wallval._x1 = x;
        wallval._y1 = y;
      }
      else        //  Fermeture du mur
      { 
        //  On definit la fin
        wallval._x2 = x;
        wallval._y2 = y;
        //  On l'ajoute au vecteur
        walls.push_back(wallval);
      }
      inWall = !inWall;
    };

    const auto abortWall = [&]() { inWall = false; };

    const auto addVertTex = [&](int x, int y, int id)
      { walls.push_back({ x , y , x , y + 1 , id }); };
    
    const auto addHoriTex = [&](int x, int y, int id)
      { walls.push_back({ x , y , x + 1 , y , id }); };

    /*
     *    2/ PARCOURS HORIZONTAL
     */

    for(size_t lncnt = 0; lncnt < mapvec.size(); lncnt++)
    {
      for(size_t charcnt = 0; charcnt < mapvec[lncnt].size(); charcnt++)
      {
        char curr_char = mapvec[lncnt][charcnt];
        lab(lncnt, charcnt) = curr_char;

        //    2.1/ GESTION DES MURS/AFFICHES

        //  A la rencontre d'un coin de mur...
        if (curr_char == Element::wall_corner)
          toggleWall(lncnt, charcnt);

        //  Si le caractere lu n'est ni un mur horizontal, ni un coin,
        //  ni une lettre de texture alors on deconstruit le mur.
        else if
         (  inWall
        &&  curr_char != Element::wall_corner
        &&  curr_char != Element::wall_horizontal
        &&  charSet.find(curr_char) == charSet.end() )
          abortWall();

        //  Ajout d'une affiche
        else if(inWall && charSet.find(curr_char) != charSet.end())
          addHoriTex(lncnt, charcnt, idMap[curr_char]);

        //    2.2/ GESTION DE L'AJOUT D'ENTITES

        else
        {
          switch(curr_char)
          {
            case Element::hunter: {
              Mover test(i, j, &lab, "");
              movers.push_back(test);
            } break;
            case Element::guardian: {
              cout << "Ajout des gardiens indisponible." << '\n';   //  TODO
            } break;
            case Element::treasure: {
              cout << "Ajout des tresors indisponible." << '\n';    //  TODO
            } break;
            
            case Element::empty: break;
            default: break;
          }
        }

        //  On retourne une erreur si on n'a pas vu
        //  de coin de mur avant la fin de la ligne
        if(inWall) throw runtime_error("lol ur lab's brokn");
      }
    }

    /*
     *    3/ PARCOURS VERTICAL (AJOUT DE MURS SEULEMENT)
     */

    for(size_t j = 0; j < lab.width(); j++)
    {
      for(size_t i = 0; i < lab.height(); i++)
      {
        auto curr_char = lab(i, j);

        //  A la rencontre d'un coin de mur...
        if (curr_char == Element::wall_corner)
          toggleWall(i, j);

        //  A la rencontre d'autre chose qu'un coin de mur ou affiche
        else if
           (  inWall
          &&  curr_char != Element::wall_horizontal
          &&  charSet.find(curr_char) == charSet.end() )
          abortWall();

        //  A la rencontre d'une affiche
        else if(inWall && charSet.find(curr_char) != charSet.end())
          addVertTex(i, j, idMap[curr_char]);
      }
    }
  }
};