#include <fstream>
#include <string>
#include <vector>

#include "Labyrinthe.h"
#include "Chasseur.h"
#include "Gardien.h"

#include "utils/mapgen.hpp"

Sound*	Chasseur::_hunter_fire;	// bruit de l'arme du chasseur.
Sound*	Chasseur::_hunter_hit;	// cri du chasseur touche.
Sound*	Chasseur::_wall_hit;	// on a tape un mur.

Environnement* Environnement::init (char* filename)
	{ return new Labyrinthe (filename); }

Labyrinthe::Labyrinthe (char* filename)
{
	ifstream file(filename);
	vector<string> maptxt;
	vector<vector<char>> mapvec;

	string line;
	size_t maxsize = 0;
	while(getline(file, line))
	{
		//	On retire le commentaire s'il existe
		auto hashpos = line.find('#');
		
		string line_clean ( line.begin()
			, hashpos == string::npos
				? line.end()
				: line.begin() + hashpos
		);

		vector<char> line_vec(line_clean.begin(), line_clean.end());

		maptxt.push_back(line_clean);
		mapvec.push_back(line_vec);
	}
}
