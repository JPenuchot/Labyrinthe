#pragma once

#include <iostream>

#include "../../Sound.h"

#include "Mover.h"
#include "Gardien.h"

class Labyrinthe;
class Gardien;

class Chasseur : public Mover {
private:
  //  Accepte ou non un deplacement.
  bool move_aux (double dx, double dy);

  //  Labyrinthe (On ne veut pas faire de cast sur Environnement,
  //  on n'est pas des animaux...)
  Labyrinthe* lab;

  float life = 100.f;

public:
  /*
   *  Le son...
   */
  static Sound* _hunter_fire; // Bruit de l'arme du chasseur.
  static Sound* _hunter_hit;  // Cri du chasseur touche.
  static Sound* _wall_hit;    // On a tape un mur.

  Chasseur (int x, int y, Labyrinthe* l);

  // Ne bouger que dans une case vide (on 'glisse' le long des obstacles)
  bool move (double dx, double dy)
    { return move_aux (dx, dy) || move_aux (dx, 0.0) || move_aux (0.0, dy); }

  //  Le chasseur ne pense pas!
  void update (void) {};

  //  Fait bouger la boule de feu (ceci est une exemple,
  //  a vous de traiter les collisions specifiques...)
  bool process_fireball (float dx, float dy);

  // Tire sur un ennemi.
  void fire (int angle_vertical);

  /*
   *    GAMEPLAY
   */

  float getLife();
  void setLife(float decrease);

  /**
   * @brief      Le chasseur se fait tirer dessus
   */
  void hit();
  void die();
};
