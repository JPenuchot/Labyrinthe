#pragma once

#include <string>
#include <vector>
#include <tuple>
#include <map>
#include <set>

#include "../../entities/movers/Chasseur.h"
#include "../../entities/movers/Gardien.h"
#include "../../entities/movers/Mover.h"
#include "../../Environnement.h"
#include "../../Labyrinthe.h"

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
    , vector<Gardien*>&                  guardians
    , vector<Chasseur*>&                 hunters
    )
  {
    auto& charSet = spray_info.first;
    auto& idMap   = spray_info.second;

    const auto& s = Environnement::scale;

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

        //  La fin du mur devient le debut d'un nouveau mur
        wallval._x1 = wallval._x2;
        wallval._y1 = wallval._y2;
      }
    };

    //  Arrête la construction d'un mur
    const auto abortWall = [&]() { inWall = false; };

    //  Ajout d'une texture verticale
    const auto addVertTex = [&](int i, int j, int id)
      { sprites.push_back({ j , i , j , i + 1 , id }); };

    //  Ajout d'une texture horizontale
    const auto addHoriTex = [&](int i, int j, int id)
      { sprites.push_back({ j , i , j + 1 , i , id }); };

    //  Ajout d'un gardien
    const auto addGuardian = [&](int i, int j)
    {
      //  On cree un gardien
      auto ng = new Gardien(j * s, i * s, &lab);

      //  On l'ajoute au vecteur guardians avec la semantique move
      guardians.push_back(ng);

      //  On ajoute le pointeur a movers (pour l'interface)
      movers.push_back(guardians.back());
    };

    //  Ajout d'un chasseur
    const auto addHunter = [&](int i, int j)
    {
      auto nc = new Chasseur(j * s, i * s, &lab);

      //  On ajoute le chasseur au vecteur hunters
      hunters.push_back(nc);

      //  On ajoute le pointeur vers le chasseur en tete de movers
      if(!movers.empty())
        { movers.push_back(movers[0]); movers[0] = nc; }
      else
        movers.push_back(nc);
    };

    //  Verifie si un caractere est un sprite
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

        if (curr_char == Element::wall_corner) visitCorner(i, j);

        else if
         (  inWall
        &&  curr_char != Element::wall_horizontal
        &&  !isSprite(curr_char) )
          abortWall();

        else if(inWall && isSprite(curr_char))
          addHoriTex(i, j, idMap[curr_char]);

        //    2.2/ GESTION DE L'AJOUT D'ENTITES

        else
        {
          switch(curr_char)
          {
            //  Ajout des chasseurs/gardiens
            case Element::hunter:   addHunter(i, j); break;
            case Element::guardian: addGuardian(i, j); break;

            //  Ajout des elements de map
            case Element::treasure:
              treasure = { (int)j, (int)i, 0 }; break;

            case Element::box:
              boxes.push_back({ (int)j, (int)i, 0 }); break;

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