#include <algorithm>
#include <array>
#include <cmath>

#ifndef M_PI
  #define M_PI  3.141592653589793238462643383279502884 /* pi */
#endif

#include "../Gardien.h"
#include "../../../Labyrinthe.h"

using namespace std;

/**
 * @brief      Update du gardien et point d'entrée pour la partie AI du projet
 */
void Gardien::update ()
{
  if(!this->path_to_follow.empty())
    followPath();
  else
  {
    //this->lab->findPath ( this->get_pos_int() , this->lab->getPlayerPos()
    //                    , this->path_to_follow);
  }
}

void Gardien::setRandomDest()
{
  //  Idée :  On pioche un angle au hasard et on parcourt une distance random
  //          avant de toucher un mur et paf ça nous fait un endroit où aller
  //          sans se taper un putain de mur au milieu. On adore.

  //  On initialise le générateur de nombre pseudo-random
  mt19937 gen(rd());

  //  Pour l'angle
  uniform_real_distribution<> angle_dist(0.f, 2.f * M_PI);
  //  Pour la proba d'incrémenter la distance
  uniform_real_distribution<> prob_dist(0.f, 1.f);


  //  On initialise la position de départ
  pos_int start = make_pair ( this->_y / Environnement::scale
                            , this->_x / Environnement::scale );

  //  On calcule un angle et on calcule les sin/cos correspondants
  //  pour donner une direction pour chaque composante
  float angle = angle_dist(gen);

  float dir_i = sin(angle);
  float dir_j = cos(angle);

  //  Distance initiale proposée
  float dist = 1.f;

  pos_int new_pos = make_pair ( start.first  + (dir_i * dist)
                              , start.second + (dir_j * dist) );

  auto prev_pos = new_pos;

  //  machin et tout
  while(prob_dist(gen) > .01 && lab->walkable(new_pos))
  {
    dist += .1f;

    //  On conserve l'ancienne position pour ne pas sortir du labyrinthe
    prev_pos = new_pos;

    //  On update la nouvelle
    new_pos = make_pair ( start.first  + dir_i * dist
                        , start.second + dir_j * dist );
  }

  this->lab->findPath(this->get_pos_int(), prev_pos, this->path_to_follow);
  message("New destination : %d, %d", prev_pos.first, prev_pos.second);
}

void Gardien::followPath()
{
  auto curr_pos = make_pair ( (int)(this->_y / Environnement::scale)
                            , (int)(this->_x / Environnement::scale) );

  auto& curr_dest = this->path_to_follow.front();

  //  Cas où on a atteint la destination
  if (curr_pos == curr_dest)
    this->path_to_follow.pop();

  //  Sinon...
  else
  {
    float di = curr_dest.first  - curr_pos.first;
    float dj = curr_dest.second - curr_pos.second;

    float inv_norm = 1.f / sqrt((di * di) + (dj * dj));

    float dx = dj * inv_norm * Environnement::scale * Gardien::speed;
    float dy = di * inv_norm * Environnement::scale * Gardien::speed;

    //  On réinitialise la navigation dès lors qu'on ne peut plus bouger
    if(!move(dx, dy))
      this->path_to_follow = {};
  }
}

void Gardien::moveToHunter (float agressivity) { /* TODO */ }
void Gardien::shootHunter  (float agressivity) { /* TODO */ }
