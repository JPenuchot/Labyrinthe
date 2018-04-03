#pragma once

#include <stdio.h>
#include "Mover.h"
#include "../../Sound.h"

#include <iostream>

class Labyrinthe;

class Chasseur : public Mover {
private:
  // accepte ou non un deplacement.
  bool move_aux (double dx, double dy);
public:
  /*
   *  Le son...
   */
  static Sound* _hunter_fire; // bruit de l'arme du chasseur.
  static Sound* _hunter_hit;  // cri du chasseur touche.
  static Sound* _wall_hit;    // on a tape un mur.

  Chasseur (int x, int y, Labyrinthe* l);

  // ne bouger que dans une case vide (on 'glisse' le long des obstacles)
  bool move (double dx, double dy)
    { return move_aux (dx, dy) || move_aux (dx, 0.0) || move_aux (0.0, dy); }

  //  Le chasseur ne pense pas!
  void update (void) {};

  //  Fait bouger la boule de feu (ceci est une exemple,
  //  a vous de traiter les collisions specifiques...)
  bool process_fireball (float dx, float dy);

  // tire sur un ennemi.
  void fire (int angle_vertical);
};