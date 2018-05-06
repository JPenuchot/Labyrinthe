#pragma once

#include <set>
#include <queue>
#include <vector>
#include <iostream>

#include "Environnement.h"

#include "entities/movers.hpp"
#include "utils/types.hpp"

using namespace std;

enum Element {
  //  Labyrinth walls
  wall_corner     = '+',
  wall_vertical   = '|',
  wall_horizontal = '-',

  //  NPCs
  hunter          = 'C',
  guardian        = 'G',

  //  Map elements
  box             = 'x',
  treasure        = 'T',

  //  Emptiness...
  empty           = ' '
};

using hit_info_t = Element;

class Labyrinthe : public Environnement {
private:
  vector<char>  table;
  vector<bool>  walkMap;
  vector<int>   distmap;

  set<char> text_ids;

  vector<Gardien*>   guardians;
  vector<Chasseur*>  hunters;

  size_t w;
  size_t h;

public:
  /*
   *  CONSTRUCTEUR/DESTRUCTEUR
   */

   Labyrinthe (char*);
  ~Labyrinthe () {}

  /*
   *  PLATEAU/WALKMAP
   */

  int width  () { return w; }
  int height () { return h; }

  inline std::vector<bool>::reference walkable(int i, int j)
    { return walkMap[i * w + j]; }
  inline std::vector<bool>::reference walkable(pos_int& p)
    { return walkMap[p.first * w + p.second]; }

  void refreshWalkMap();

  /*
   *  RECHERCHE D'ÉLÉMENTS
   */

  template <typename T>
  friend T* findInLab (Labyrinthe& lab, double x, double y);

  inline pos_int getPlayerPos()
  {
    auto& hun = this->hunters[0];
    return make_pair( hun->_y / Environnement::scale
                    , hun->_x / Environnement::scale);
  }

  inline pos_int getTreasurePos()
    { return make_pair(this->_treasor._y, this->_treasor._x); }

  /*
   *  AJOUT/RETRAIT D'ÉLÉMENTS
   */

  bool remove (Chasseur* c);
  bool remove (Gardien* g);
  bool remove (Box* b);
  bool remove (Wall* w);

  /*
   *  NAVIGATION
   */

  inline int dist_to_treasure  (int i, int j)  { return distmap[i * w + j]; }
  bool findPath(pos_int from, pos_int to, std::queue<pos_int>& res);

  /*
   *  DEBUG
   */

  void dump();

  /*
   *  MISC
   */

  inline bool isValid(pos_int& p)
  { return p.first  >= 0 && p.first  < this->h
        && p.second >= 0 && p.second < this->w; }
};

/*
 *  FONCTIONS FRIEND
 */

template <typename T>
T* findInLab (Labyrinthe& lab, double x, double y) { return nullptr; }

template <> Chasseur* findInLab (Labyrinthe& lab, double x, double y);
template <> Gardien*  findInLab (Labyrinthe& lab, double x, double y);
template <> Wall*     findInLab (Labyrinthe& lab, double x, double y);
template <> Box*      findInLab (Labyrinthe& lab, double x, double y);

/*
 * HELPERS
 */

inline pos_int playerPosToIJ(pos_float& p)
  { return make_pair( p.second / Environnement::scale
                    , p.first  / Environnement::scale ); }
