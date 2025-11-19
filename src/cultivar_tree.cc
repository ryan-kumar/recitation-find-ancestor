#include "cultivar_tree.hpp"

#include <fstream>
#include <iomanip>
#include <sstream>

////////////////////////////////////////////
/// Your implementation here!
///////////////////////////////////////////

// You may find it helpful to implement this helper function!
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

std::string CultivarTree::LowestCommonAncestor(Node* cultivar_one,
                                               Node* cultivar_two) {
  //   (void)cultivar_one;  // remove when you begin coding
  //   (void)cultivar_two;  // remove when you begin coding

  Node* curr = root_;

  while (curr) {
    if (cultivar_one->key_ > curr->key_ && cultivar_two->key_ > curr->key_) {
      curr = curr->right_;
    } else if (cultivar_one->key_ < curr->key_ &&
               cultivar_two->key_ < curr->key_) {
      curr = curr->left_;
    } else {
      return curr->label_;
    }
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
    std::cout << "Could not open " << file_name << std::endl;
    exit(1);
  }
  int key = 0;
  std::string label;
  while (ifs >> std::quoted(label) >> key) {
    nodes.push_back(new Node(key, label));
  }
  return nodes;
}

Node* CultivarTree::Find(Node* root, const std::string& label) {
  if (root == nullptr || root->label_ == label) {
    return root;
  }
  Node* left = Find(root->left_, label);
  Node* right = Find(root->right_, label);
  return (left && left->label_ == label) ? left : right;
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