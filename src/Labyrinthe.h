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
  /**
   * Stocke pour chaque case si celle-ci est translucide ou non, CàD si on peut
   * marcher dessus ou non.
   */
  vector<bool>  walkMap;

  /**
   * Stocke pour chaque case la distance au trésor.
   */
  vector<int>   distmap;

  /**
   * Liste des lettres correspondant à une texture.
   */
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

  /**
   * @brief      Accès à la walkmap : true si case translucide, sinon false
   *
   * @param[in]  i     Coordonnée i
   * @param[in]  j     Coordonnée j
   *
   * @return     Référence vers la case de walkmap correspondant à la paire
   * de coordonnées (i, j). La valeur est true si la case est vide sinon false.
   */
  inline std::vector<bool>::reference walkable(int i, int j)
    { return walkMap[i * w + j]; }

  /**
   * @brief      Accès à la walkmap : true si case translucide, sinon false
   *
   * @param      p     Position au format défini dans types.hpp
   *
   * @return     Référence vers la case de walkmap correspondant à la paire
   * de coordonnées (i, j). La valeur est true si la case est vide sinon false.
   */
  inline std::vector<bool>::reference walkable(pos_int& p)
    { return walkMap[p.first * w + p.second]; }

  /**
   * @brief      Rafraîchit la walkmap
   */
  void refreshWalkMap();

  /*
   *  RECHERCHE D'ÉLÉMENTS
   */

  /**
   * @brief      Cherche un élément de type T à la position (x, y)
   *
   * @param      lab   Labyrinthe
   * @param[in]  x     Coordonnée x
   * @param[in]  y     Coordonnée y
   *
   * @tparam     T     Type de l'élément recherché
   *
   * @return     Pointeur vers l'élément recherché, nullptr si non trouvé
   */
  template <typename T>
  friend T* findInLab (Labyrinthe& lab, double x, double y);

  /**
   * @brief      Renvoie la position du joueur
   *
   * @return     Position du joueur
   */
  inline pos_int getPlayerPos()
  {
    auto& hun = this->hunters[0];
    return make_pair( hun->_y / Environnement::scale
                    , hun->_x / Environnement::scale);
  }

  /**
   * @brief      Renvoie la position du trésor
   *
   * @return     Position du trésor
   */
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

  /**
   * @brief      Renvoie la distance au trésor de la case de coordonnées (i, j)
   *
   * @param[in]  i     Coordonnée i
   * @param[in]  j     Coordonnée j
   *
   * @return     Distance au trésor
   */
  inline int dist_to_treasure  (int i, int j)  { return distmap[i * w + j]; }

  /**
   * @brief      Construit un chemin de la position from à la position to
   *
   * @param[in]  from  Début du chemin
   * @param[in]  to    Fin du chemin
   * @param      res   File contenant le chemin
   *
   * @return     true si un chemin existe sinon false
   */
  bool findPath(pos_int from, pos_int to, std::queue<pos_int>& res);

  /*
   *  DEBUG
   */

  /**
   * @brief      Effectue un dump du labyrinthe dans la sortie standard
   */
  void dump();

  /*
   *  MISC
   */

  /**
   * @brief      Vérifie la validité d'une position
   *
   * @param      p     position
   *
   * @return     true si valide sinon false
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

/**
 * @brief      Convertit une position 'joueur' en une position (i, j)
 *
 * @param      p     Position joueur
 *
 * @return     Position (i, j)
 */
inline pos_int playerPosToIJ(pos_float& p)
  { return make_pair( p.second / Environnement::scale
                    , p.first  / Environnement::scale ); }
