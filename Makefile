CXX=clang++
INCLUDES=-Iincludes/
CXXFLAGS=-std=c++20 -gdwarf-4 -Wall -Wextra -pedantic -fsanitize=address,null -Wno-error=unused $(INCLUDES)

exec: bin/exec
tests: bin/tests

bin/exec: ./src/driver.cc ./includes/cultivar_tree.hpp ./src/cultivar_tree.cc
	$(CXX) $(CXXFLAGS) ./src/driver.cc ./src/cultivar_tree.cc -o $@

bin/tests: obj/catch_main.o ./tests/tests.cc ./includes/cultivar_tree.hpp ./src/cultivar_tree.cc
	$(CXX) $(CXXFLAGS) obj/catch_main.o ./tests/tests.cc ./src/cultivar_tree.cc -o $@

obj/catch_main.o: ./tests/catch.cc ./tests/catch.hpp
	$(CXX) $(CXXFLAGS) -c ./tests/catch.cc -o $@

.DEFAULT_GOAL := exec
.PHONY: clean exec tests

clean:
	rm -fr bin/* obj/*