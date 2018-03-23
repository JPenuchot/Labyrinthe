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
  vector<string> maptxt;
  vector<vector<char>> mapvec;

  tuple<set<char>, map<char, string>, map<char, int>> spray_info;
  int curr_int_id = 0;

  auto add_spray = [&](char id, string path)
  {
    get<0>(spray_info).insert(id);
    get<1>(spray_info)[id] = path;
    get<2>(spray_info)[id] = curr_int_id;
    curr_int_id++;
  };

  string line;
  size_t maxwidth = 0;
  while(getline(file, line))
  {
    cout << "Ligne.\n";
    //  On retire le commentaire s'il existe
    auto hashpos = line.find('#');
    
    string line_clean ( line.begin()
      , hashpos == string::npos //  Si # non trouvé
        ? line.end()              //  Alors on prend tout
        : line.begin() + hashpos  //  Sinon on vire le commentaire
    );

    //  Cette regex permet de matcher les descripteurs de textures.
    //  Voir : https://regex101.com/r/JJzOXk/3
    regex descriptor("^\\s*([a-b])\\s*([^\\s]+)\\s*$");
    smatch match;

    if(regex_match(line_clean, match, descriptor))
    { //  On matche sur un descripteur (paire caractère * chemin)

      //  On récupère le seul caractère du 1er submatch
      auto char_str = match[1].str();
      auto char_id = char_str[0];
      
      //  On récupère le chemin (2ème match)
      auto path = match[2];

      cout << "Ajout de " << char_id << "=" << path << '\n';
    }
    
    else
    { //  Si on ne matche pas, on rajoute la ligne aux vecteurs.
      vector<char> line_vec(line_clean.begin(), line_clean.end());
      maptxt.push_back(line_clean);
      mapvec.push_back(line_vec);
    }
  }
}
