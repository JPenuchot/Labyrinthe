/**
 * Contient le constructeur de Labyrinthe
 */

#include <fstream>
#include <string>
#include <vector>
#include <memory>
#include <regex>

#include "../entities/movers/Chasseur.h"
#include "../entities/movers/Gardien.h"
#include "../Labyrinthe.h"

#include "../utils/mapgen.hpp"

using namespace std;

Sound*  Chasseur::_hunter_fire; // bruit de l'arme du chasseur.
Sound*  Chasseur::_hunter_hit;  // cri du chasseur touche.
Sound*  Chasseur::_wall_hit;    // on a tape un mur.

Environnement* Environnement::init (char* filename)
  { return new Labyrinthe (filename); }

Labyrinthe::Labyrinthe (char* filename)
{
  ifstream file(filename);
  vector<vector<char>> mapvec;
  pair<set<char>, map<char, int>> spray_info;

  //  On definit des references sur les membres
  //  de spray_info pour la lisibilite du code
  auto& charSet = spray_info.first;
  auto& idMap   = spray_info.second;

  /*
   *    PRE-DEFINITION DES ACTIONS
   */

  int curr_int_id = 1;
  auto add_spray = [&](char id, string path)
  {
    charSet.insert(id);
    text_ids.insert(id);

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
  regex descriptor("^\\s*([a-z])\\s*([^\\s]+)\\s*$");

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
    //  Gestion des commentaires
    auto hashpos = line.find('#');

    string line_clean ( line.begin()
      , hashpos == string::npos //  Si '#' non trouve
        ? line.end()              //  Alors on prend tout
        : line.begin() + hashpos  //  Sinon on vire le commentaire
    );

    //  Regex matching

    smatch match;

    //  On ajoute les couples (lettre * path) a spray_info
    if(regex_match(line_clean, match, descriptor))
      add_spray ( match[1].str()[0] //  1er caractere du 1er groupe
                , match[2]          //  2eme groupe entier
                );

    //  On saute les lignes vides
    else if(regex_match(line_clean, match, spaces));

    //  Si on ne matche pas, on rajoute la ligne au vecteur mapvec.
    else
    {
      vector<char> line_vec(line_clean.begin(), line_clean.end());
      mapvec.push_back(line_vec);

      //  Update des dimensions du labyrinthe
      labwidth = max(labwidth, line_clean.size());
      labheight++;
    }
  }

  this->w = labwidth;
  this->h = labheight;

  /*
   *    GENERATION DE LA MAP
   */

  vector<Wall>    wall_vec;
  vector<Wall>    picts_vec;
  vector<Box>     boxes_vec;
  vector<Mover*>  movers_vec;

  //  On lance le parsing sur tout le niveau (yay)
  labyrinth::mapgen::parse_level( mapvec , spray_info , *this
                                , wall_vec, picts_vec, boxes_vec, movers_vec
                                , this->_treasor

                                , this->guardians
                                , this->hunters
                                );

  /*
   *    COPIE DES RESULTATS
   */

  this->_nwall    = wall_vec.size();
  this->_walls    = new Wall[wall_vec.size()];
  copy(wall_vec.begin(), wall_vec.end(), this->_walls);

  this->_npicts   = picts_vec.size();
  this->_picts    = new Wall[picts_vec.size()];
  copy(picts_vec.begin(), picts_vec.end(), this->_picts);

  this->_nboxes   = boxes_vec.size();
  this->_boxes    = new Box[boxes_vec.size()];
  copy(boxes_vec.begin(), boxes_vec.end(), this->_boxes);

  this->_nguards  = movers_vec.size();
  this->_guards   = new Mover*[movers_vec.size()];
  copy(movers_vec.begin(), movers_vec.end(), this->_guards);

  /*
   *    DISMAP/WALKMAP
   */

  //  Génération de la map de collision
  this->walkMap.resize(this->width() * this->height(), true);
  this->refreshWalkMap();

  //  Generation de la map de distance
  labyrinth::mapgen::distmap(*this, this->distmap);
}
