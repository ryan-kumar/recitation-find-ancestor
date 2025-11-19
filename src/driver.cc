#include <iostream>

#include "cultivar_tree.hpp"

int main() {
  CultivarTree ct("sample_input/ex_3.txt");

  std::cout << ct << std::endl;

  std::cout << "The common ancestor of Dent Corn & Flint Corn is: "
            << (ct.LowestCommonAncestor(
                   CultivarTree::Find(ct.GetRoot(), "Dent Corn"),
                   CultivarTree::Find(ct.GetRoot(), "Flint Corn")))
            << std::endl;

  return 0;
}
