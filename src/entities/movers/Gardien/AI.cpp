#include <array>
#include <cmath>

#ifndef M_PIf32
  #define M_PIf32  __f32 (3.141592653589793238462643383279502884) /* pi */
#endif

#include "../Gardien.h"
#include "../../../Labyrinthe.h"

/**
 * @brief      Update du gardien et point d'entrée pour la partie AI du projet
 */
void Gardien::update ()
{
  if (this->health <= 0.f) this->die();
  moveRandomly();
}

void Gardien::setRandomDest()
{
  //  Idée :  On pioche un angle au hasard et on parcourt une distance random
  //          avant de toucher un mur et paf ça nous fait un endroit où aller
  //          sans se taper un putain de mur au milieu. On adore.

  //  On initialise le générateur de nombre pseudo-random
  std::random_device rd;
  std::mt19937 gen(rd());

  //  Pour l'angle
  uniform_real_distribution<> rad(0, 2.f * M_PIf32);
  //  Pour la proba d'incrémenter la distance
  uniform_real_distribution<> prob(0, 1.f);


  //  On initialise la position de départ
  pos_int start = make_pair ( this->_y / Environnement::scale
                            , this->_x / Environnement::scale
                            );

  //  On calcule un angle et on calcule les sin/cos correspondants
  //  pour donner une direction pour chaque composante
  float angle = rad(gen);

  float dir_i = sin(angle);
  float dir_j = cos(angle);

  //  Distance initiale proposée
  float dist = 1.f;

  pos_int new_pos = make_pair ( start.first  + dir_i * dist
                              , start.second + dir_j * dist
                              );

  auto prev_pos = new_pos;

  //  machin et tout
  while(prob(gen) > .1 && !lab->isWall((*lab)(new_pos)))
  {
    dist++;

    //  On conserve l'ancienne position pour ne pas sortir du labyrinthe
    prev_pos = new_pos;

    //  On update la nouvelle
    pos_int new_pos = make_pair ( start.first  + dir_i * dist
                                , start.second + dir_j * dist
                                );
  }

  this->destination = make_unique<pos_int>(prev_pos);
}

void Gardien::moveToHunter (float agressivity)
{
  //  TODO
}

void Gardien::shootHunter  (float agressivity)
{
  //  TODO
}

bool Gardien::moveTowardsDest ()
{
  auto curr_pos = make_pair ( (int)(this->_y / Environnement::scale)
                            , (int)(this->_x / Environnement::scale) );

  //  Si on n'a pas de destination *snif*
  if (!this->destination)
    return false;

  //  Cas où on a atteint la destination
  else if (curr_pos == *this->destination)
  {
    this->destination = nullptr;
    return false;
  }

  //  Si on a bel et bien une destination
  else
  {
    float di = this->destination->first  - curr_pos.first;
    float dj = this->destination->second - curr_pos.second;

    float inv_norm = 1.f / sqrt(di * di + dj * dj);

    float dx = dj * inv_norm * Gardien::speed;
    float dy = di * inv_norm * Gardien::speed;

    move(dx, dy);
  }

  return true;
}

void Gardien::moveRandomly ()
{
  pos_float origin = make_pair( this->_y / Environnement::scale
                              , this->_x / Environnement::scale );

  if(this->moveTowardsDest());
  else
  {
    //  Find random destination
    this->setRandomDest();
  }
}
