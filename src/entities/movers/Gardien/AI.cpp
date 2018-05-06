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
  {
    followPath();
  }
  else
  {
    queue<pos_int> path_to_player;

    this->lab->findPath ( this->get_pos_int() , this->lab->getPlayerPos()
                        , this->path_to_follow);

    for(int i = 0; i < 5; i++)
    {
      if(path_to_player.empty()) break;
      else
      {
        this->path_to_follow.push(path_to_player.front());
        path_to_player.pop();
      }
    }
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
  auto dist2 = [](pos_float a, pos_float b) -> float
    {
      auto dx = a.first - b.first;
      auto dy = a.second - b.second;
      return (dx * dx) + (dy * dy);
    };

  auto curr_pos = make_pair ( (this->_y / Environnement::scale)
                            , (this->_x / Environnement::scale) );

  auto& curr_dest_ = this->path_to_follow.front();
  auto curr_dest = make_pair(curr_dest_.first + .5f, curr_dest_.second + .5f);

  //  Cas où on a atteint la destination
  if (dist2(curr_pos, curr_dest) < .5)
  {
    this->path_to_follow.pop();
    cout << this << " : ting goes pop\n";
  }

  //  Sinon...
  else
  {
    float di = curr_dest.first  - curr_pos.first;
    float dj = curr_dest.second - curr_pos.second;

    float norm = sqrt((di * di) + (dj * dj));

    float dx = (dj / norm) * Environnement::scale * Gardien::speed;
    float dy = (di / norm) * Environnement::scale * Gardien::speed;

    dx = abs(dj) < abs(dx) ? dj : dx;
    dy = abs(di) < abs(dy) ? di : dy;

    cout << this << " : ( " << dx << " ; " << dy << " )\n";

    //  On réinitialise la navigation dès lors qu'on ne peut plus bouger
    if(!move(dx, dy))
    {
      cout << this << "FUCK\n";
      this->path_to_follow = {};
    }
  }
}

void Gardien::moveToHunter (float agressivity) { /* TODO */ }
void Gardien::shootHunter  (float agressivity) { /* TODO */ }
