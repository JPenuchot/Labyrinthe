#pragma once

/*
 *	Traduit un fichier de type definition de labyrinthe au format interne.
 */

#define EMPTY	0		// case vide (ou on peut marcher!)

extern void message (const char* format, ...);
class Mover;

enum Element {
	//	Labyrinth walls
	wall_corner = '+',
	wall_vertical = '|',
	wall_horizontal = '-',
	
	//	Entities
	hunter = 'C',
	guardian = 'G',
	treasure = 'T'
};

struct Wall {
	int	_x1, _y1;	// point de depart.
	int	_x2, _y2;	// point d'arrivee.
	int	_ntex;		// numero de texture.
};

struct Box {
	int	_x, _y;		// emplacement.
	int	_ntex;		// numero de texture.
};

class Environnement {
public:
	static const int scale;		// facteur d'echelle (defini par moi, mais utilise par vous)
	static const char* texture_dir;	// repertoire des textures.
	static const char* modele_dir;	// repertoire des personnages.
/*
 * la fonction de creation du labyrinthe a definir
 * DANS Labyrinthe.cpp de la fa�on suivante:
 * 
 * Environnement* Environnement::init (char* filename) {
 *	return new Labyrinthe (filename);
 * }
 * 
 * 
 */
	static Environnement* init (char* filename);

	Wall*		_walls;		// les murs sous forme de tableau de segments.
	int		_nwall;		// le nombre de segments.
	Wall*		_picts;		// les affiches.
	int		_npicts;	// leur nombre.
	Box*		_boxes;		// les caisses.
	int		_nboxes;	// leur nombre.
	Box		_treasor;	// le tresor.
	Mover**		_guards;	// les gardes (tableau de pointeurs de gardiens).
	int		_nguards;	// leur nombre.

	virtual int width () =0;	// retourne la largeur du labyrinthe.
	virtual int height () =0;	// retourne la longueur du labyrinthe.
	virtual char data (int i, int j) = 0;	// retourne la case (i, j).
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
