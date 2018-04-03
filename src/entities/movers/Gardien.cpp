#include <iostream>

#include "Gardien.h"
#include "../../Labyrinthe.h"

using namespace std;

const auto is = 1. / (double)Environnement::scale;

bool Gardien::move_aux (double dx, double dy)
{
  if(Element::empty == _l->data ( (int)( (_x + dx) * is )
                                , (int)( (_y + dy) * is ) ) )
  {
    _x += dx;
    _y += dy;
    return true;
  }
  return false;
}

//  DESC
void Gardien::update (void){}

//  DESC
bool Gardien::process_fireball (float dx, float dy)
{
  // calculer la distance entre le chasseur et le lieu de l'explosion.
  float x = (_x - _fb -> get_x ()) * is;
  float y = (_y - _fb -> get_y ()) * is;
  
  float dist2 = x*x + y*y;
  
  // on bouge que dans le vide!
  if (Element::empty == _l -> data( (int)( (_fb->get_x() + dx) * is )
                                  , (int)( (_fb->get_y() + dy) * is ) ) )
    { return true; }
  
  // collision...
  // calculer la distance maximum en ligne droite.
  float dmax2 = ( _l->width() * _l->width() ) + ( _l->height() * _l->height() );
  
  message("* poof *");
  return false;
}

//  DESC
bool Gardien::move (double dx, double dy)
  { return move_aux (dx, dy) || move_aux (dx, 0.0) || move_aux (0.0, dy); }

//  DESC
void Gardien::fire (int angle_vertical){}

//  DESC
void Gardien::right_click (bool shift, bool control){ message("Right click"); }
