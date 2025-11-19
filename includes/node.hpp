#ifndef NODE_HPP
#define NODE_HPP
#include <string>

struct Node {
  int key_;
  std::string label_;
  Node* left_ = nullptr;
  Node* right_ = nullptr;

  Node() = default;
  Node(int key, const std::string& label): key_(key), label_(label) {}
};
#endif