#pragma once

#include <queue>
#include <random>
#include <optional>

#include "Mover.h"
#include "Chasseur.h"
#include "../../utils/types.hpp"

class Labyrinthe;
class Chasseur;

static const char modmarv[] = "Marvin";

class Gardien : public Mover
{
  Labyrinthe* lab;

  /**
   * Stocke le chemin en cours à suivre
   */
  std::queue<pos_int> path_to_follow;

  /**
   * Stocke la
   */
  float health = 12.f;

  /**
   * Pour la sélection aléatoire d'une coordonnée à rejoindre
   */
  std::random_device rd;

public:
  Gardien(int x, int y, Labyrinthe* l);
  ~Gardien () {}

  inline static float speed = .1f;

  bool move             (double dx, double dy);
  bool move_aux         (double dx, double dy);

  void fire             (int angle_vertical);
  void right_click      (bool shift, bool control);
  bool process_fireball (float dx, float dy);

  /**
   * @brief      Renvoie la position d'un joueur.
   *
   * @return     Position du joueur en coordonnées (i, j).
   */
  inline pos_int get_pos_int()
    { return std::make_pair ( (int)(this->_y / Environnement::scale)
                            , (int)(this->_y / Environnement::scale) ); }

  /*
   *    GAMEPLAY - Defined in ./Gardien/gameplay.cpp
   */

  float getHealth()           { return this->health; }
  void  setHealth(float val)  { this->health = val; }
  void  hit();
  void  die();

  /*
   * AI
   */

  void update       ();
  void moveToHunter (float agressivity);
  void shootHunter  (float agressivity);

  void followPath     ();
  void setRandomDest  ();

  void followPath(std::queue<pos_int>& path);
};
