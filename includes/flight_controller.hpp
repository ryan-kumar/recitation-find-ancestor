#ifndef FLIGHT_CONTROLLER_HPP
#define FLIGHT_CONTROLLER_HPP

#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

#include "jet.hpp"

class FlightController {
public:
  FlightController() = default;
  FlightController(
      const std::vector<std::pair<unsigned int, std::string>>& jets);
  FlightController(FlightController& other) = delete;
  FlightController& operator=(FlightController& rhs) = delete;
  ~FlightController();

  void BreakFormation(Jet* jet);                  // TODO
  Jet* FindPosition(unsigned int ranking) const;  // TODO
  void JoinFormation(unsigned int ranking,
                     const std::string& pilot_name);  // TODO
  void RestoreFormation(Jet* current_jet);            // TODO
  void UpdateHeights(Jet* current_jet);               // TODO
  void RightRotate(Jet* pivot_jet);                   // TODO

  void LeftRotate(Jet* pivot_jet);         // GIVEN
  void RightLeftRotate(Jet* pivot_jet);    // GIVEN
  void LeftRightRotate(Jet* pivot_jet);    // GIVEN
  int GetBalanceFactor(Jet* current_jet);  // GIVEN

  friend std::ostream& operator<<(std::ostream& os,
                                  const FlightController& fc);  // GIVEN
  void PrintHelper(unsigned int indent_lvl,
                   Jet* current_node,
                   std::ostream& os = std::cout) const;  // GIVEN

  std::stringstream& ToStream(Jet* n,
                              unsigned int depth,
                              std::string s,
                              std::stringstream& os) const;
  Jet* GetLeader() const { return leader_; }

private:
  Jet* leader_ = nullptr;
};

std::ostream& operator<<(std::ostream& os, FlightController& fc);

#endif