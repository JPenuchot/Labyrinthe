#pragma once

class Labyrinthe; // la (future) votre

#include "FireBall.h"
#include "Environnement.h"

class Mover {
private:
  static void*  init (const char*); // initialise le modele md2.
public:
  Environnement*  _l; // le labyrinthe dans lequel il evolue.
  FireBall* _fb;      // sa boule de feu.
  float   _x, _y;     // position.
  int     _angle;     // angle de deplacement/tir.
  void*   _model;     // le modele graphique.

  Mover (int x, int y, Labyrinthe* l, const char* modele) :
    _l ((Environnement*)l), _fb (0), _x ((float)x), _y ((float)y),
    _angle (0)
  { _model = init (modele); }
  
  virtual ~Mover () {}
  
  // Fait tomber un personnage (gardien) et se relever
  void tomber ();
  
  // Fait tomber un personnage (gardien) et le laisse au sol.
  void rester_au_sol ();
  
  // Fait 'penser' le personnage (gardien).
  virtual void update (void) {};
  
  // Fait bouger la boule de feu du personnage.
  virtual bool process_fireball (float dx, float dy) { return false; }
  
  // tente de deplacer le personnage de <dx,dy>.
  virtual bool move (double dx, double dy) { return false; }
  
  // Fait tirer le personnage sur un ennemi (vous pouvez ignorer l'angle vertical).
  virtual void fire (int angle_vertical) {};

  // appelee pour le gardien 0 (chasseur) quand l'utilisateur fait un clic droit;
  // shift (control) est vrai si la touche shift (control) est appuyee.
  virtual void right_click (bool shift, bool control) {}
  
};
