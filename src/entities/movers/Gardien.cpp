#include <iostream>

#include "Gardien.h"

using namespace std;

//  DESC
void Gardien::update (void){}

//  DESC
bool Gardien::process_fireball (float dx, float dy){ return false; }

//  DESC
bool Gardien::move (double dx, double dy)
{
  cout << _x + dx << ';' << _y + dy << '\n';
  return false;
}

//  DESC
void Gardien::fire (int angle_vertical){}

//  DESC
void Gardien::right_click (bool shift, bool control){}
