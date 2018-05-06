#include <algorithm>

#include "../Labyrinthe.h"

using namespace std;

void Labyrinthe::refreshWalkMap()
{
  //  Murs
	for_each(this->_walls, this->_walls + this->_nwall, [&](auto w) {
		for(int i = w._y1; i < w._y2; i++) {
			for(int j = w._x1; j < w._x2; j++) {
				this->walkable(i, j) = false;
			}
		}
	});

  //  Boxes
	for_each(this->_boxes, this->_boxes + this->_nboxes, [&](auto b) {
		this->walkable(b._y, b._x) = false;
	});

  //  Trésor
	this->walkable(this->_treasor._y, this->_treasor._x) = false;

}
