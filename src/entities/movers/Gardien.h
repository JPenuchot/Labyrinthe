#pragma once

#include <optional>
#include <random>

#include "Mover.h"
#include "Chasseur.h"
#include "../../utils/types.hpp"

class Labyrinthe;
class Chasseur;

static const char modmarv[] = "Marvin";

class Gardien : public Mover
{
  Labyrinthe* lab;

  std::optional<pos_int> destination;

  float health;

  std::random_device rd;

public:
  Gardien(int x, int y, Labyrinthe* l);
  ~Gardien () {}

  inline static float speed = 1.f;

  bool move             (double dx, double dy);
  bool move_aux         (double dx, double dy);

  void fire             (int angle_vertical);
  void right_click      (bool shift, bool control);
  bool process_fireball (float dx, float dy);

  /*
   *    GAMEPLAY - Defined in ./Gardien/gameplay.cpp
   */

  void hit();
  void die();

  /*
   * AI
   */

  void update       ();
  void moveToHunter (float agressivity);
  void shootHunter  (float agressivity);

  bool moveTowardsDest  ();
  void setRandomDest    ();
  void moveRandomly     ();
};
