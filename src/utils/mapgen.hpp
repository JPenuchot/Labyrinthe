#pragma once

#include <functional>
#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <map>
#include <set>

#include "../Environnement.h"
#include "../Labyrinthe.h"
#include "../entities/movers/Chasseur.h"
#include "../entities/movers/Gardien.h"
#include "../entities/movers/Mover.h"

namespace labyrinth::utils
{
  using namespace std;

  void parse_level
    ( vector<vector<char>>& mapvec
    , tuple<set<char>, map<char, string>, map<char, int>>& spray_info
    , Labyrinthe&     lab
    , vector<Wall>&   walls
    , vector<Wall>&   sprites
    , vector<Box>&    boxes
    , vector<Mover*>& movers
    , Box&            treasure
    )
  {    
    auto& charSet = get<0>(spray_info);
    auto& idMap   = get<2>(spray_info);

    /*
     *    1/ PRE-DEFINITION DES ACTIONS
     */

    auto i_to_x = [&](auto i) { return i * Environnement::scale; };
    auto j_to_y = [&](auto j) { return j * Environnement::scale; };

    Wall wallval = { 0, 0, 0, 0, 0 };
    bool inWall = false;

    int wallcnt = 0;

    //  On definit l'action effectuee a la rencontre d'un
    //  coin ici pour alleger les boucles par la suite.
    const auto toggleWall = [&](int x, int y)
    { 
      //  Mise a l'echelle (voir declaration de s)
      if(!inWall) //  Ouverture du mur
      {
        wallval._x1 = x;
        wallval._y1 = y;
      }
      else        //  Fermeture du mur
      {
        wallcnt++;
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
      { sprites.push_back({ x , y , x , y + 1 , id }); };
    
    const auto addHoriTex = [&](int x, int y, int id)
      { sprites.push_back({ x , y , x + 1 , y , id }); };

    /*
     *    2/ PARCOURS HORIZONTAL
     *
     *      - Ajout des murs horizontaux
     *      - Ajout des **entites**
     */

    for(size_t i = 0; i < mapvec.size(); i++)
    {
      for(size_t j = 0; j < mapvec[i].size(); j++)
      {
        const auto x = i_to_x(i);
        const auto y = j_to_y(j);

        const char curr_char = mapvec[i][j];
        
        lab(i, j) = curr_char;

        //    2.1/ GESTION DES MURS/AFFICHES

        //  A la rencontre d'un coin de mur...
        if (curr_char == Element::wall_corner)
          toggleWall(i, j);

        //  Si le caractere lu n'est ni un mur horizontal, ni un coin,
        //  ni une lettre de texture alors on deconstruit le mur.
        else if
         (  inWall
        &&  curr_char != Element::wall_horizontal
        &&  charSet.find(curr_char) == charSet.end() )
          abortWall();

        //  Ajout d'une affiche
        else if(inWall && charSet.find(curr_char) != charSet.end())
          addHoriTex(x, y, idMap[curr_char]);

        //    2.2/ GESTION DE L'AJOUT D'ENTITES

        else
        {
          switch(curr_char)
          {
            case Element::hunter: {
              cout << "Ajout des chasseurs indisponible." << '\n';   //  TODO
            } break;
            case Element::guardian: {;
              movers.push_back(new Gardien(x, y, &lab));
            } break;
            case Element::treasure: {
              treasure = { (int)x, (int)y, 0 };
            } break;
            
            case Element::empty: break;
            default: break;
          }
        }
      }

      if(inWall) throw runtime_error("Broken labyrinth: Wall not closed.\n");
    }

    /*
     *    3/ PARCOURS VERTICAL (AJOUT DE MURS SEULEMENT)
     */

    for(size_t j = 0; j < lab.width(); j++)
    {
      for(size_t i = 0; i < lab.height(); i++)
      {
        const auto x = i_to_x(i);
        const auto y = j_to_y(j);

        const char curr_char = lab(i, j);

        //  A la rencontre d'un coin de mur...
        if (curr_char == Element::wall_corner)
          toggleWall(i, j);

        //  A la rencontre d'autre chose qu'un coin de mur ou affiche
        else if
           (  inWall
          &&  curr_char != Element::wall_vertical
          &&  charSet.find(curr_char) == charSet.end() )
          abortWall();

        //  A la rencontre d'une affiche
        else if(inWall && charSet.find(curr_char) != charSet.end())
          addVertTex(i, j, idMap[curr_char]);
      }

      if(inWall) throw runtime_error("Broken labyrinth: Wall not closed.\n");
    }

    cout << wallcnt << " walls\n";
  }
};