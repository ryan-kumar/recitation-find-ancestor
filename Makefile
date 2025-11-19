CXX=clang++
INCLUDES=-Iincludes/
CXXFLAGS=-std=c++20 -gdwarf-4 -Wall -Wextra -pedantic -fsanitize=address,null -Wno-error=unused $(INCLUDES)

exec: bin/exec
tests: bin/tests

bin/exec: ./src/driver.cc ./includes/flight_controller.hpp ./src/flight_controller.cc
	$(CXX) $(CXXFLAGS) ./src/driver.cc ./src/flight_controller.cc -o $@

bin/tests: obj/catch_main.o ./tests/tests.cc ./includes/flight_controller.hpp ./src/flight_controller.cc
	$(CXX) $(CXXFLAGS) obj/catch_main.o ./tests/tests.cc ./src/flight_controller.cc -o $@

obj/catch_main.o: ./tests/catch.cc ./tests/catch.hpp
	$(CXX) $(CXXFLAGS) -c ./tests/catch.cc -o $@

.DEFAULT_GOAL := exec
.PHONY: clean exec tests

clean:
	rm -fr bin/* obj/*