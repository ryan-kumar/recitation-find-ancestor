#include <iostream>

#include "flight_controller.hpp"

int main() {
  std::vector<std::pair<unsigned int, std::string>> jets = {
      {5, "jack"}, {3, "james"}, {2, "juny"}};

  FlightController fc(jets);

  std::cout << fc << std::endl;

  return 0;
}