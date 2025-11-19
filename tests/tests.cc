// clang-format off
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//  Written By : Ryan Kumar                    Environment : ubuntu:bionic               //
//  Date ......: 2025/11/19                      Compiler ...: clang++                  //
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
// clang-format on

///////////////////////////////////////////////////////////////////////////////
//                             Framework Set-up //
///////////////////////////////////////////////////////////////////////////////
#ifdef CATCH_CONFIG_MAIN
#  undef CATCH_CONFIG_MAIN
#endif
#include "catch.hpp"

///////////////////////////////////////////////////////////////////////////////
//                                 Includes //
///////////////////////////////////////////////////////////////////////////////
#include <fstream>
#include <stdexcept>

#include "catch.hpp"
#include "cultivar_tree.hpp"
#include "node.hpp"

///////////////////////////////////////////////////////////////////////////////
//                             Helpers/Constants //
///////////////////////////////////////////////////////////////////////////////
std::string WriteTempFile(const std::string& name,
                          const std::string& contents) {
  std::ofstream ofs{name};
  ofs << contents;
  return name;
}

///////////////////////////////////////////////////////////////////////////////
//                                Test Cases //
///////////////////////////////////////////////////////////////////////////////

TEST_CASE("Constructor: Builds correct single-node tree", "[cons-1]") {
  std::string fname = WriteTempFile("single.txt", "\"Root\" 10\n");

  CultivarTree ct(fname);
  REQUIRE(ct.GetRoot() != nullptr);
  REQUIRE(ct.GetRoot()->label_ == "Root");
  REQUIRE(ct.GetRoot()->key_ == 10);
  REQUIRE(ct.GetRoot()->left_ == nullptr);
  REQUIRE(ct.GetRoot()->right_ == nullptr);
}

TEST_CASE("Constructor: Inserts nodes in BST ordering", "[cons-2]") {
  std::string fname = WriteTempFile("bst1.txt",
                                    "\"Root\" 10\n"
                                    "\"Left\" 5\n"
                                    "\"Right\" 20\n");

  CultivarTree ct(fname);

  Node* r = ct.GetRoot();
  REQUIRE(r->label_ == "Root");
  REQUIRE(r->left_->label_ == "Left");
  REQUIRE(r->right_->label_ == "Right");
}

TEST_CASE("Constructor: Builds a more complex BST", "[cons-3]") {
  std::string fname = WriteTempFile("bst_deep.txt",
                                    "\"A\" 10\n"
                                    "\"B\" 6\n"
                                    "\"C\" 15\n"
                                    "\"D\" 3\n"
                                    "\"E\" 8\n");

  CultivarTree ct(fname);

  Node* r = ct.GetRoot();
  REQUIRE(r->left_->left_->label_ == "D");
  REQUIRE(r->left_->right_->label_ == "E");
}

TEST_CASE("LCA: Finds ancestor of immediate siblings", "[lca-1]") {
  CultivarTree ct;
  ct.Root() = new Node(10, "Root");
  ct.Root()->left_ = new Node(5, "A");
  ct.Root()->right_ = new Node(20, "B");

  REQUIRE(ct.LowestCommonAncestor(ct.Root()->left_, ct.Root()->right_) ==
          "Root");
}

TEST_CASE("LCA: Finds ancestor when leaves lie in left subtree", "[lca-2]") {
  CultivarTree ct;
  ct.Root() = new Node(30, "R");
  Node* L = ct.Root()->left_ = new Node(10, "L");
  Node* LL = L->left_ = new Node(5, "LL");
  Node* LR = L->right_ = new Node(15, "LR");

  REQUIRE(ct.LowestCommonAncestor(LL, LR) == "L");
}

TEST_CASE("LCA: Finds ancestor when leaves lie in right subtree", "[lca-3]") {
  CultivarTree ct;
  ct.Root() = new Node(30, "R");
  Node* R = ct.Root()->right_ = new Node(40, "X");
  Node* RL = R->left_ = new Node(35, "Y");
  Node* RR = R->right_ = new Node(50, "Z");

  REQUIRE(ct.LowestCommonAncestor(RL, RR) == "X");
}

TEST_CASE("LCA: Finds root ancestor, split both in both directions",
          "[lca-4]") {
  CultivarTree ct;
  ct.Root() = new Node(20, "R");
  Node* L = ct.Root()->left_ = new Node(10, "L");
  Node* R = ct.Root()->right_ = new Node(30, "RR");
  Node* RL = R->left_ = new Node(25, "RL");

  REQUIRE(ct.LowestCommonAncestor(L, RL) == "R");
}

TEST_CASE("LCA: Larger distance between leaves", "[lca-5]") {
  CultivarTree ct;
  ct.Root() = new Node(50, "Root");
  Node* R1 = ct.Root()->right_ = new Node(70, "A");
  Node* R2 = R1->right_ = new Node(90, "B");
  Node* R3 = R2->left_ = new Node(80, "C");

  REQUIRE(ct.LowestCommonAncestor(R1, R3) == "A");
}

TEST_CASE("LCA: Throws exceptions properly", "[lca-6]") {
  CultivarTree ct;
  ct.Root() = new Node(10, "X");

  REQUIRE_THROWS_AS(ct.LowestCommonAncestor(nullptr, ct.Root()),
                    std::invalid_argument);
  REQUIRE_THROWS_AS(ct.LowestCommonAncestor(ct.Root(), nullptr),
                    std::invalid_argument);
}

///////////////////////////////////////////////////////////////////////////////