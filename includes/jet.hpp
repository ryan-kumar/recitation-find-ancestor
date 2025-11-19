#ifndef JET_HPP
#define JET_HPP
#include <string>

struct Jet {
  unsigned int ranking_ = 0;
  std::string pilot_name_;
  unsigned int height_ = 1;
  Jet* left_ = nullptr;
  Jet* right_ = nullptr;
  Jet* parent_ = nullptr;

  Jet() = default;
  Jet(unsigned int ranking, const std::string& pilot_name):
      ranking_(ranking), pilot_name_(pilot_name) {}
  Jet(unsigned int ranking, const std::string& pilot_name, Jet* parent):
      ranking_(ranking), pilot_name_(pilot_name), parent_(parent) {}
};
#endif