#pragma once

#include <ostream>

/*
 *  Traduit un fichier de type definition de labyrinthe au format interne.
 */

// case vide (ou on peut marcher!)
#define EMPTY 0

extern void message (const char* format, ...);
class Mover;

struct Wall {
  int _x1, _y1; // point de depart.
  int _x2, _y2; // point d'arrivee.
  int _ntex;    // numero de texture.

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
  int _x, _y; // emplacement.
  int _ntex;  // numero de texture.

  friend std::ostream& operator<< (std::ostream& os, Box& b)
  {
    os << "Box( " << b._x << " , " << b._y << " ; ntex : " << b._ntex << " )";
    return os;
  }
};

class Environnement {
public:
  // facteur d'echelle (defini par moi, mais utilise par vous)
  static const int scale;
  
  // repertoire des textures.
  static const char* texture_dir;
  
  // repertoire des personnages.
  static const char* modele_dir;
/*
 * la fonction de creation du labyrinthe a definir
 * DANS Labyrinthe.cpp de la facon suivante:
 * 
 * Environnement* Environnement::init (char* filename) {
 *  return new Labyrinthe (filename);
 * }
 */
  static Environnement* init (char* filename);

  Wall*   _walls;   // les murs sous forme de tableau de segments.
  int     _nwall;   // le nombre de segments.
  Wall*   _picts;   // les affiches.
  int     _npicts;  // leur nombre.
  Box*    _boxes;   // les caisses.
  int     _nboxes;  // leur nombre.
  Box     _treasor; // le tresor.
  Mover** _guards;  // les gardes (tableau de pointeurs de gardiens).
  int     _nguards; // leur nombre.

  // retourne la largeur du labyrinthe.
  virtual int width () { return 0; };

  // retourne la longueur du labyrinthe.
  virtual int height () { return 0; };

  // retourne la case (i, j).
  virtual char data (int i, int j) { return 0; };

  virtual ~Environnement () {}

  // reconsidere le labyrinthe pour le reafficher.
  // fonction a n'appeller QUE si les murs ou les caisses ou le tresor BOUGENT
  void reconfigure ();

  // retourne le numero de texture pour le fichier image passe en argument.
  int wall_texture (char*);

  // recree les boules de feu des movers.
  // fonction a n'appeller QUE si des gardiens sont recrees.
  void make_fireballs (void);
};
