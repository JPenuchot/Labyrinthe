#pragma once

#include "Mover.h"
#include "Chasseur.h"

class Labyrinthe;
class Chasseur;

static const char modmarv[] = "Marvin";

class Gardien : public Mover {
Labyrinthe* lab;

float direction;
float health;

public:
  Gardien(int x, int y, Labyrinthe* l);

  ~Gardien () {}

  void update (void);

  bool process_fireball (float dx, float dy);

  bool move (double dx, double dy);

  void fire (int angle_vertical);

  void right_click (bool shift, bool control);

  bool move_aux (double dx, double dy);

  /*
   *    GAMEPLAY - Defined in ./Gardien/gameplay.cpp
   */

  void hit();
  void die();

  /*
   * AI
   */

  void moveToHunter (float agressivity);
  void shootHunter  (float agressivity);
  void moveRandomly ();
};
