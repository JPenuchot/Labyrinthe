#pragma once

#include <functional>
#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <map>
#include <set>

#include "../entities/movers/Chasseur.h"
#include "../entities/movers/Gardien.h"
#include "../entities/movers/Mover.h"
#include "../Environnement.h"
#include "../Labyrinthe.h"

namespace labyrinth::mapgen
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

    //  Mur en cours de construction
    Wall wallval = { 0, 0, 0, 0, 0 };
    //  Vrai si mur en cours de construction
    bool inWall = false;

    //  Amorce/termine la construction d'un mur
    const auto visitCorner = [&](int i, int j)
    {
      //  Mise a l'echelle (voir declaration de s)
      if(!inWall) //  Ouverture du mur
      {
        wallval._x1 = j;
        wallval._y1 = i;
        inWall = true;
      }
      else        //  Fermeture du mur
      {
        //  On definit la fin
        wallval._x2 = j;
        wallval._y2 = i;
        //  On l'ajoute au vecteur
        walls.push_back(wallval);

        //  La fin du mur devient le début d'un nouveau mur
        wallval._x1 = wallval._x2;
        wallval._y1 = wallval._y2;
      }
    };

    //  Arrête la construction d'un mur
    const auto abortWall = [&]() { inWall = false; };

    //  Ajout d'une texture verticale
    const auto addVertTex = [&](int i, int j, int id)
      { sprites.push_back({ j , i , j + 1 , i , id }); };
    
    //  Ajout d'une texture horizontale
    const auto addHoriTex = [&](int i, int j, int id)
      { sprites.push_back({ j , i , j , i + 1 , id }); };

    //  Vérifie si un caractère est un sprite
    const auto isSprite = [&](char c)
      { return charSet.find(c) != charSet.end(); };

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
        const char curr_char = mapvec[i][j];
        
        lab(i, j) = curr_char == ' ' ? Element::empty : curr_char;

        //    2.1/ GESTION DES MURS/AFFICHES

        //  A la rencontre d'un coin de mur...
        if (curr_char == Element::wall_corner) visitCorner(i, j);

        //  Si le caractere lu n'est ni un mur horizontal, ni un coin,
        //  ni une lettre de texture alors on deconstruit le mur.
        else if
         (  inWall
        &&  curr_char != Element::wall_horizontal
        &&  !isSprite(curr_char) )
          abortWall();

        //  Ajout d'une affiche
        else if(inWall && isSprite(curr_char))
          addHoriTex(i, j, idMap[curr_char]);

        //    2.2/ GESTION DE L'AJOUT D'ENTITES

        else
        {
          switch(curr_char)
          {
            case Element::hunter: {
              cout << "Ajout des chasseurs indisponible." << '\n';   //  TODO
            } break;
            case Element::guardian: {
              //movers.push_back(new Gardien(j, i, &lab));
            } break;
            case Element::treasure: {
              treasure = { (int)j, (int)i, 0 };
            } break;

            case Element::box: {
              boxes.push_back({ (int)j, (int)i, 0 });
            } break;
            
            case Element::empty: break;
            default: break;
          }
        }
      }
      //  Fin de ligne : on annule la construction du mur.
      abortWall();
    }

    /*
     *    3/ PARCOURS VERTICAL (AJOUT DE MURS SEULEMENT)
     */

    for(size_t j = 0; j < lab.width(); j++)
    {
      for(size_t i = 0; i < lab.height(); i++)
      {
        const char curr_char = lab(i, j);

        //  A la rencontre d'un coin de mur...
        if (curr_char == Element::wall_corner) visitCorner(i, j);

        //  A la rencontre d'autre chose qu'un coin de mur ou affiche
        else if
           (  inWall
          &&  curr_char != Element::wall_vertical
          &&  !isSprite(curr_char) )
          abortWall();

        //  A la rencontre d'une affiche
        else if(inWall && charSet.find(curr_char) != charSet.end())
          addVertTex(i, j, idMap[curr_char]);
      }
      //  Fin de colonne : on annule la construction du mur.
      abortWall();
    }
  }
};