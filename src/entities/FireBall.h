#pragma once

#ifndef M_PI
#define M_PI 3.1415926
#endif

class Mover;

enum FBstat { FB_NONE, FB_MOVE, FB_EXPLODE };

class FireBall {
private:
  float _x, _y, _z;   // Position de la boule.
  float _size;        // Sa taille actuelle.
  float _orig_size;   // Sa taille a l'origine.
  int   _angle;       // Angle (elle tourne sur elle-meme).
  int   _angle2;      // Angle (elle tourne sur elle-meme sur un autre axe).
  unsigned int  _fire_texture;  // Sa texture.
  int   _move_angle;  // Angle de deplacement.
  int   _azimuth;     // Le meme en hauteur.
  Mover*  _owner;     // Le proprio.

  static unsigned int _fire_list;   // Sa display list.
  FBstat  _state;     // Etat de la boule.
  void explode ();

public:
  FireBall (float size, unsigned int tex, Mover*);
  
  void display ();
  
  void move_step ();
  
  // Initialise un tir.
  void init (float x, float y, float z, int angle_vertical, int angle_horizontal);
  
  // Decide de la taille initiale de la boule.
  void set_orig_size (float size) { _orig_size = size; }
  
  // Recupère la position actuelle de la boule.
  float get_x () { return _x; }
  float get_y () { return _y; }
};
