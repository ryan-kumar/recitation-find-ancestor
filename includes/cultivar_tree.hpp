#ifndef CULTIVAR_TREE_HPP
#define CULTIVAR_TREE_HPP
#include <iostream>
#include <ostream>
#include <string>
#include <vector>

#include "node.hpp"

class CultivarTree {
public:
  ~CultivarTree();
  CultivarTree() = default;
  CultivarTree(const CultivarTree& other) = delete;
  CultivarTree& operator=(const CultivarTree& other) = delete;

  //////////////////////////////////////////////////////////////////
  //// Implement these functions!
  //////////////////////////////////////////////////////////////////

  CultivarTree(const std::string& file_name);  // TODO

  std::string LowestCommonAncestor(Node* cultivar_one,
                                   Node* cultivar_two);  // TODO

  //////////////////////////////////////////////////////////////////

  static Node* Find(Node* root, const std::string& label);

  std::vector<Node*> NodesFromFile(const std::string& file_name);

  friend std::ostream& operator<<(std::ostream& os, const CultivarTree& fc);
  void PrintHelper(unsigned int indent_lvl,
                   Node* current_node,
                   std::ostream& os = std::cout) const;

  std::stringstream& ToStream(Node* n,
                              unsigned int depth,
                              std::string s,
                              std::stringstream& os) const;

  Node* GetRoot() const { return root_; }

  Node*& Root() { return root_; }

private:
  Node* root_ = nullptr;
};

std::ostream& operator<<(std::ostream& os, CultivarTree& ct);

#endif