#include <iostream>

#include "Chasseur.h"
#include "../../Labyrinthe.h"

using namespace std;

const auto is = 1. / (double)Environnement::scale;

/*
 *  Tente un deplacement.
 */
bool Chasseur::move_aux (double dx, double dy)
{
  if(Element::empty == _l -> data ( (int)((_x + dx)  * is)
                                  , (int)((_y + dy)  * is) ) )
  {
    _x += dx;
    _y += dy;
    return true;
  }
  return false;
}

/*
 *  Constructeur.
 */

Chasseur::Chasseur (int x, int y, Labyrinthe* l): Mover (x, y, l, "Marvin")
{
  if(!_hunter_fire) _hunter_fire  = new Sound ("sons/hunter_fire.wav");
  if(!_hunter_hit)  _hunter_hit   = new Sound ("sons/hunter_hit.wav");
  if(!_wall_hit)    _wall_hit     = new Sound ("sons/hit_wall.wav");
}

/*
 *  Fait bouger la boule de feu (ceci est une exemple, a vous de traiter
 *  les collisions specifiques...)
 */

bool Chasseur::process_fireball (float dx, float dy)
{
  // calculer la distance entre le chasseur et le lieu de l'explosion.
  float x = (_x - _fb->get_x()) * is;
  float y = (_y - _fb->get_y()) * is;
  
  float dist2 = x*x + y*y;
  
  // on bouge que dans le vide!
  if (Element::empty == _l -> data( (int)( (_fb->get_x() + dx) * is )
                                  , (int)( (_fb->get_y() + dy) * is ) ) )
  {
    message ("Woooshh..... %d", (int) dist2);
    // il y a la place.
    return true;
  }
  
  // collision...
  // calculer la distance maximum en ligne droite.
  float dmax2 = ( _l->width() * _l->width() ) + ( _l->height() * _l->height() );
  
  // faire exploser la boule de feu avec un bruit en fonction de la distance.
  _wall_hit->play(1. - dist2 / dmax2);
  
  message("Booom...");
  return false;
}

/*
 *  Tire sur un ennemi.
 */
void Chasseur::fire (int angle_vertical)
{
  message("Woooshh...");
  _hunter_fire->play();
  _fb->init(_x, _y, 10., angle_vertical, _angle);
}
