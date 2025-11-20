#include <iostream>

#include "cultivar_tree.hpp"

int main() {
  CultivarTree ct("sample_input/ex_2.txt");

  std::cout << ct << std::endl;

  std::cout << "The lowest common ancestor of Kale & Cabbage is: "
            << (ct.LowestCommonAncestor(
                   CultivarTree::Find(ct.GetRoot(), "Kale"),
                   CultivarTree::Find(ct.GetRoot(), "Cabbage")))
            << std::endl;

  return 0;
}
