#pragma once

#include <ostream>

extern void message (const char* format, ...);
extern void partie_terminee (bool);

class Mover;

struct Wall {
  int _x1, _y1; // Point de depart.
  int _x2, _y2; // Point d'arrivee.
  int _ntex;    // Numero de texture.

  friend std::ostream& operator<< (std::ostream& os, Wall& wall)
  {
    os
      << "Wall[ ( " << wall._x1
      << " , " << wall._y1
      << " ) => ( " << wall._x2
      << " , " << wall._y2 << " ) ]";
    return os;
  }
};

struct Box {
  int _x, _y; // Emplacement.
  int _ntex;  // Numero de texture.

  friend std::ostream& operator<< (std::ostream& os, Box& b)
  {
    os << "Box( " << b._x << " , " << b._y << " ; ntex : " << b._ntex << " )";
    return os;
  }
};

class Environnement {
public:
  // Facteur d'echelle (defini par moi, mais utilise par vous)
  static const int scale;

  // Repertoire des textures.
  static const char* texture_dir;

  // Repertoire des personnages.
  static const char* modele_dir;

  static Environnement* init (char* filename);

  Wall*   _walls;   // Les murs sous forme de tableau de segments.
  int     _nwall;   // Le nombre de segments.
  Wall*   _picts;   // Les affiches.
  int     _npicts;  // Leur nombre.
  Box*    _boxes;   // Les caisses.
  int     _nboxes;  // Leur nombre.
  Box     _treasor; // Le tresor.
  Mover** _guards;  // Les gardes (tableau de pointeurs de gardiens).
  int     _nguards; // Leur nombre.

  // Retourne la largeur du labyrinthe.
  virtual int width () { return 0; };

  // Retourne la longueur du labyrinthe.
  virtual int height () { return 0; };

  virtual ~Environnement () {}

  // Reconsidere le labyrinthe pour le reafficher.
  // Fonction a n'appeller QUE si les murs ou les caisses ou le tresor BOUGENT
  void reconfigure ();

  // Retourne le numero de texture pour le fichier image passe en argument.
  int wall_texture (char*);

  // Recree les boules de feu des movers.
  // Fonction a n'appeller QUE si des gardiens sont recrees.
  void make_fireballs (void);
};
