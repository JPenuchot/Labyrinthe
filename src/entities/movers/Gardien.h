#pragma once

#include "Mover.h"

class Labyrinthe;

static char modmarv[] = "Marvin";

class Gardien : public Mover {
public:
  Gardien(int x, int y, Labyrinthe* l):
  Mover(x, y, l, modmarv)
  {
    //if(!_hunter_fire) _hunter_fire  = new Sound ("sons/hunter_fire.wav");
    //if(!_hunter_hit)  _hunter_hit   = new Sound ("sons/hunter_hit.wav");
    //if(!_wall_hit)    _wall_hit     = new Sound ("sons/hit_wall.wav");
  }
  
  ~Gardien () { /* TODO ? */ }
  
  void update (void);
  bool process_fireball (float dx, float dy);
  bool move (double dx, double dy);
  void fire (int angle_vertical);
  void right_click (bool shift, bool control);
};
