#include "flight_controller.hpp"

FlightController::FlightController(
    const std::vector<std::pair<unsigned int, std::string>>& jets) {
  for (auto const& [ranking, pilot_name] : jets) {
    JoinFormation(ranking, pilot_name);
  }
}

FlightController::~FlightController() {
  BreakFormation(leader_);
  leader_ = nullptr;
}

void FlightController::BreakFormation(Jet* jet) {
  // TODO
}

Jet* FlightController::FindPosition(unsigned int ranking) const {
  // TODO
  return nullptr;
}

void FlightController::UpdateHeights(Jet* current_jet) {
  // TODO
}

void FlightController::JoinFormation(unsigned int ranking,
                                     const std::string& pilot_name) {
  // TODO
}

void FlightController::RestoreFormation(Jet* current_jet) {
  // TODO
}

void FlightController::RightRotate(Jet* pivot_jet) {
  // TODO
}

void FlightController::LeftRotate(Jet* pivot_jet) {
  Jet* new_root = pivot_jet->right_;
  pivot_jet->right_ = new_root->left_;
  if (pivot_jet->right_) {
    pivot_jet->right_->parent_ = pivot_jet;
  }

  new_root->left_ = pivot_jet;

  new_root->parent_ = pivot_jet->parent_;
  pivot_jet->parent_ = new_root;

  if (new_root->parent_) {
    if (new_root->parent_->left_ == pivot_jet) {
      new_root->parent_->left_ = new_root;
    } else {
      new_root->parent_->right_ = new_root;
    }
  } else {
    leader_ = new_root;
  }

  UpdateHeights(pivot_jet);
  UpdateHeights(new_root);
}

int FlightController::GetBalanceFactor(Jet* current_jet) {
  if (!current_jet) return 0;
  int l_height = (current_jet->left_) ? current_jet->left_->height_ : 0;
  int r_height = (current_jet->right_) ? current_jet->right_->height_ : 0;
  return l_height - r_height;
}

void FlightController::RightLeftRotate(Jet* pivot_jet) {
  RightRotate(pivot_jet->right_);
  LeftRotate(pivot_jet);
}

void FlightController::LeftRightRotate(Jet* pivot_jet) {
  LeftRotate(pivot_jet->left_);
  RightRotate(pivot_jet);
}

void FlightController::PrintHelper(unsigned int indent_lvl,
                                   Jet* current_node,
                                   std::ostream& os) const {
  (void)indent_lvl;
  std::stringstream ss;
  os << ToStream(current_node, 0, "", ss).str();
}

std::stringstream& FlightController::ToStream(Jet* n,
                                              unsigned int depth,
                                              std::string s,
                                              std::stringstream& os) const {
  if (n == nullptr) {
    os << "Empty" << std::endl;
    return os;
  }
  os << "<(" << n->ranking_ << ": " << n->pilot_name_ << ")>\n";
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

std::ostream& operator<<(std::ostream& os, FlightController& fc) {
  fc.PrintHelper(40, fc.GetLeader(), os);
  return os;
}