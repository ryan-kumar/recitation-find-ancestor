#include <iostream>

#include "cultivar_tree.hpp"

int main() {
  CultivarTree ct("sample_in/ex_1.txt");

  std::cout << ct << std::endl;

  std::cout << (ct.LowestCommonAncestor(
                   CultivarTree::Find(ct.GetRoot(), "Broccoli"),
                   CultivarTree::Find(ct.GetRoot(), "Cabbage")))
            << std::endl;

  return 0;
}
