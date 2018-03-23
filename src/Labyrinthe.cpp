#include <fstream>
#include <string>
#include <vector>
#include <regex>

#include "Labyrinthe.h"
#include "Chasseur.h"
#include "Gardien.h"

#include "utils/mapgen.hpp"

Sound*  Chasseur::_hunter_fire; // bruit de l'arme du chasseur.
Sound*  Chasseur::_hunter_hit;  // cri du chasseur touche.
Sound*  Chasseur::_wall_hit;  // on a tape un mur.

Environnement* Environnement::init (char* filename)
  { return new Labyrinthe (filename); }

Labyrinthe::Labyrinthe (char* filename)
{
  cout << "Début de lecture du fichier.\n";

  ifstream file(filename);
  
  vector<vector<char>> mapvec;

  tuple<set<char>, map<char, string>, map<char, int>> spray_info;
  int curr_int_id = 1;

  auto add_spray = [&](char id, string path)
  {
    get<0>(spray_info).insert(id);
    get<1>(spray_info)[id] = path;
    get<2>(spray_info)[id] = curr_int_id;
    curr_int_id++;
  };

  string line;
  size_t labwidth = 0;
  size_t labheight = 0;
  while(getline(file, line))
  {
    //  On retire le commentaire s'il existe
    auto hashpos = line.find('#');
    
    string line_clean ( line.begin()
      , hashpos == string::npos //  Si # non trouvé
        ? line.end()              //  Alors on prend tout
        : line.begin() + hashpos  //  Sinon on vire le commentaire
    );

    //  Cette regex permet de matcher les descripteurs de textures.
    //    Voir : https://regex101.com/r/JJzOXk/3
    regex descriptor("^\\s*([a-b])\\s*([^\\s]+)\\s*$");
    
    //  Celle-ci permet de matcher les lignes remplies d'espaces.
    regex spaces("^\\s*$");

    smatch match;

    if(regex_match(line_clean, match, descriptor))
    { //  On matche sur un descripteur (paire caractère * chemin)

      //  On récupère le seul caractère du 1er submatch
      auto char_id = match[1].str()[0];
      
      //  On récupère le chemin (2ème match)
      auto path = match[2];
    }
    
    //  On saute les lignes vides
    else if(regex_match(line_clean, match, spaces));

    else
    { //  Si on ne matche pas, on rajoute la ligne aux vecteurs.
      vector<char> line_vec(line_clean.begin(), line_clean.end());
      mapvec.push_back(line_vec);

      labwidth = max(labwidth, line_clean.size());
      labheight++;
    }

    this->table.resize(labwidth * labheight, ' ');
    this->w = labwidth;
    this->h = labheight;

    //labyrinth::utils::parse_level
    //  ( mapvec
    //  , spray_info
    //  )
    this->_walls    = this->wall_vec.data();
    this->_nwall    = this->wall_vec.size();
    
    this->_picts    = this->picts_vec.data();
    this->_npicts   = this->picts_vec.size();
    
    this->_boxes    = this->boxes_vec.data();
    this->_nboxes   = this->boxes_vec.size();
    
    //this->_treasor  = treasure; TODO

    //  Cas des gardiens
    this->_guards = new (Mover*);
    *(this->_guards)   = this->guardians_vec.data();
    this->_nguards  = this->guardians_vec.size();
  }
}
