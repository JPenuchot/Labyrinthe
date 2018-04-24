#include <algorithm>

#include "../Labyrinthe.h"

using namespace std;

void Labyrinthe::dump()
{
  auto print      = [](auto& e) { cout <<  e << '\n'; };
  auto print_ptr  = [](auto& e) { cout << *e << '\n'; };

  cout << "\n# Walls :\n";
  for_each(this->_walls, &this->_walls[this->_nwall], print);

  cout << "\n# Picts :\n";
  for_each(this->_picts, &this->_picts[this->_npicts], print);

  cout << "\n# Boxes :\n";
  for_each(this->_boxes, &this->_boxes[this->_nboxes], print);

  cout << "\n# Treasure :\n";
  print(this->_treasor);

  cout << "\n# Guardians :\n";
  for_each(this->_guards, &this->_guards[this->_nguards], print_ptr);
}
