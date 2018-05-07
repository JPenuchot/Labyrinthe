#pragma once

class Labyrinthe; // La (future) votre

#include "../FireBall.h"
#include "../../Environnement.h"

class Mover {
private:
  static void*  init (const char*); // Initialise le modele md2.
public:
  Environnement*  _l; // Le labyrinthe dans lequel il evolue.
  FireBall* _fb;      // Sa boule de feu.
  float   _x, _y;     // Position.
  int     _angle;     // Angle de deplacement/tir.
  void*   _model;     // Le modele graphique.

  friend std::ostream& operator<< (std::ostream& os, Mover& mover)
  {
    os << "Mover{ x : " << mover._x << " ; y : " << mover._y << " }";
    return os;
  }

  Mover (int x, int y, Labyrinthe* l, const char* modele)
  : _l ((Environnement*)l), _fb(0)
  , _x ((float)x), _y ((float)y)
  , _angle(0)
    { _model = init(modele); }

  virtual ~Mover() {}

  // Fait tomber un personnage (gardien) et se relever
  void tomber();

  // Fait tomber un personnage (gardien) et le laisse au sol.
  void rester_au_sol();

  // Fait 'penser' le personnage (gardien).
  virtual void update (void) {}

  // Fait bouger la boule de feu du personnage.
  virtual bool process_fireball (float dx, float dy) { return false; }

  // Tente de deplacer le personnage de <dx,dy>.
  virtual bool move (double dx, double dy) { return false; }

  // Fait tirer le personnage sur un ennemi
  // (vous pouvez ignorer l'angle vertical).
  virtual void fire (int angle_vertical) {}

  // Appelee pour le gardien 0 (chasseur) quand l'utilisateur fait un clic droit
  // Shift (control) est vrai si la touche shift (control) est appuyee.
  virtual void right_click (bool shift, bool control) {}
};
