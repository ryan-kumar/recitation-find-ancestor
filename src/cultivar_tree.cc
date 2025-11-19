#include "cultivar_tree.hpp"

#include <fstream>
#include <iomanip>
#include <sstream>

////////////////////////////////////////////
/// Your implementation here!
///////////////////////////////////////////

void InsertNode(Node*& root, Node* node) {
  if (!root) {
    root = node;
  } else if (node->key_ < root->key_) {
    InsertNode(root->left_, node);
  } else {
    InsertNode(root->right_, node);
  }
}

CultivarTree::CultivarTree(const std::string& file_name) {
  std::vector<Node*> nodes = NodesFromFile(file_name);
  for (unsigned int i = 0; i < nodes.size(); i++) {
    InsertNode(root_, nodes[i]);
  }
}

Node* CultivarTree::LowestCommonAncestor(Node* root,
                                         Node* cultivar_one,
                                         Node* cultivar_two) {
  //   (void)cultivar_one;  // remove when you begin coding
  //   (void)cultivar_two;  // remove when you begin coding

  if (!root || cultivar_one == root || cultivar_two == root) {
    return root;
  }

  return "";
}

////////////////////////////////////////////
/// Provided Functions; DO NOT MODIFY
///////////////////////////////////////////
std::vector<Node*> CultivarTree::NodesFromFile(const std::string& file_name) {
  std::vector<Node*> nodes;
  std::ifstream ifs{file_name};
  if (!ifs.is_open()) {
    std::cerr << "Could not open " << file_name << std::endl;
    exit(1);
  }
  int key = 0;
  std::string label;
  while (ifs >> std::quoted(label) >> key) {
    nodes.push_back(new Node(key, label));
  }
  return nodes;
}

void Clear(Node* node) {
  if (node == nullptr) return;
  Clear(node->left_);
  Clear(node->right_);
  delete node;
}

CultivarTree::~CultivarTree() {
  Clear(root_);
  root_ = nullptr;
}

void CultivarTree::PrintHelper(unsigned int indent_lvl,
                               Node* current_node,
                               std::ostream& os) const {
  (void)indent_lvl;
  std::stringstream ss;
  os << ToStream(current_node, 0, "", ss).str();
}

std::stringstream& CultivarTree::ToStream(Node* n,
                                          unsigned int depth,
                                          std::string s,
                                          std::stringstream& os) const {
  if (n == nullptr) {
    os << "Empty" << std::endl;
    return os;
  }
  os << "(" << n->key_ << ": " << n->label_ << ")\n";
  os << s << " l--[L]";
  s += " |  ";
  if (n->left_)
    ToStream(n->left_, depth + 1, s, os);
  else
    os << "NULL\n";
  s.erase(s.end() - 4, s.end());

  os << s << " l--[R]";
  s += "    ";
  if (n->right_)
    ToStream(n->right_, depth + 1, s, os);
  else
    os << "NULL\n";
  s.erase(s.end() - 4, s.end());
  return os;
}

std::ostream& operator<<(std::ostream& os, CultivarTree& ct) {
  ct.PrintHelper(40, ct.GetRoot(), os);
  return os;
}