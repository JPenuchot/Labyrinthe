#include <fstream>
#include <string>
#include <vector>
#include <regex>

#include "Labyrinthe.h"
#include "entities/movers/Chasseur.h"
#include "entities/movers/Gardien.h"

#include "utils/mapgen.hpp"

Sound*  Chasseur::_hunter_fire; // bruit de l'arme du chasseur.
Sound*  Chasseur::_hunter_hit;  // cri du chasseur touche.
Sound*  Chasseur::_wall_hit;    // on a tape un mur.

Environnement* Environnement::init (char* filename)
  { return new Labyrinthe (filename); }

Labyrinthe::Labyrinthe (char* filename)
{
  ifstream file(filename);
  vector<vector<char>> mapvec;
  tuple<set<char>, map<char, string>, map<char, int>> spray_info;
  
  //  On definit des references sur les membres
  //  de spray_info pour la lisibilite du code
  auto& charSet = get<0>(spray_info);
  auto& pathMap = get<1>(spray_info);
  auto& idMap   = get<2>(spray_info);

  /*
   *    PRE-DEFINITION DES ACTIONS
   */

  int curr_int_id = 1;
  auto add_spray = [&](char id, string path)
  {
    charSet.insert(id);
    pathMap[id] = path;

    char* str = new char[path.size()];
    copy(path.begin(), path.end(), str);

    idMap[id] = this->wall_texture(str);

    curr_int_id++;
  };

  /*
   *    REGEX
   */

  //  Cette regex permet de matcher les descripteurs de textures.
  //    1er  matching group : caractere de la texture
  //    2eme matching group : path de la texture
  //  Plus d'infos : https://regex101.com/r/JJzOXk/3
  regex descriptor("^\\s*([a-b])\\s*([^\\s]+)\\s*$");
  
  //  Celle-ci permet de matcher les lignes remplies d'espaces.
  regex spaces("^\\s*$");

  /*
   *    LECTURE DU FICHIER
   */

  string line;
  size_t labwidth = 0;
  size_t labheight = 0;

  while(getline(file, line))
  {
    //  On retire le commentaire s'il existe
    auto hashpos = line.find('#');
    
    string line_clean ( line.begin()
      , hashpos == string::npos //  Si '#' non trouve
        ? line.end()              //  Alors on prend tout
        : line.begin() + hashpos  //  Sinon on vire le commentaire
    );

    smatch match;

    //  On ajoute les couples (lettre * path) a spray_info
    if(regex_match(line_clean, match, descriptor))
      add_spray ( match[1].str()[0] //  1er caractere du 1er groupe
                , match[2]          //  2eme groupe entier
                );
    
    //  On saute les lignes vides
    else if(regex_match(line_clean, match, spaces));

    else
    { //  Si on ne matche pas, on rajoute la ligne au vecteur mapvec.
      vector<char> line_vec(line_clean.begin(), line_clean.end());
      mapvec.push_back(line_vec);

      labwidth = max(labwidth, line_clean.size());
      labheight++;
    }
  }

  this->w = labwidth;
  this->h = labheight;
  this->table.resize(labwidth * labheight, Element::empty);

  vector<Wall>    wall_vec;
  vector<Wall>    picts_vec;
  vector<Box>     boxes_vec;
  vector<Mover*>  guardians_vec;

  //  On lance le parsing sur tout le niveau (yay)
  labyrinth::mapgen::parse_level( mapvec , spray_info
                                , *this
                                , wall_vec , picts_vec
                                , boxes_vec , guardians_vec , this->_treasor
                                );

  //  On copie les resultats au format attendu pour l'interface...

  this->_nwall    = wall_vec.size();
  this->_walls    = new Wall[wall_vec.size()];
  copy(wall_vec.begin(), wall_vec.end(), this->_walls);

  this->_npicts   = picts_vec.size();
  this->_picts    = new Wall[picts_vec.size()];
  copy(picts_vec.begin(), picts_vec.end(), this->_picts);

  this->_nboxes   = boxes_vec.size();
  this->_boxes    = new Box[boxes_vec.size()];
  copy(boxes_vec.begin(), boxes_vec.end(), this->_boxes);
  
  this->_nguards  = guardians_vec.size();
  this->_guards   = new Mover*[guardians_vec.size()];
  copy(guardians_vec.begin(), guardians_vec.end(), this->_guards);

  cout  << "texture_dir : " << this->texture_dir  << '\n'
        << "modele_dir : " << this->modele_dir   << '\n';

  cout  << _nwall   << " walls\n"
        << _npicts  << " picts\n"
        << _nboxes  << " boxes\n"
        << _nguards << " movers\n";
}
