#pragma once

#include "Mover.h"

class Labyrinthe;

static char modmarv[] = "Marvin";

class Gardien : public Mover {
public:
  Gardien(int x, int y, Labyrinthe* l): Mover(x, y, l, modmarv) {}
  
  ~Gardien () { /* TODO ? */ }
  
  void update (void);
  
  bool process_fireball (float dx, float dy);
  
  bool move (double dx, double dy);
  
  void fire (int angle_vertical);
  
  void right_click (bool shift, bool control);
  
  bool move_aux (double dx, double dy);
};
