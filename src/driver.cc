#include <iostream>

#include "cultivar_tree.hpp"

int main() {
  CultivarTree ct("sample_in/ex_1.txt");

  std::cout << ct << std::endl;

  return 0;
}
