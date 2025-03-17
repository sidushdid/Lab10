CXXFLAGS = -g -std=c++17 -Wall -Wextra -Werror -Wno-unused-parameter
CXX      = g++

# These targets don't create any files:
.PHONY: clean

# Magic Variables!
# https://www.gnu.org/software/make/manual/html_node/Automatic-Variables.html
#  $@ is the name of the target
#  $+ is a list of all the dependencies
#  $< is the first dependency

main: main.o Map.o Point.o
	${CXX} $(CXXFLAGS) -o $@ $+


main.o: main.cpp Map.h Errors.h
	${CXX} $(CXXFLAGS) -c -o $@ $<

Map.o: Map.cpp Map.h Point.h
	${CXX} $(CXXFLAGS) -c -o $@ $<

Point.o: Point.cpp Point.h 
	${CXX} $(CXXFLAGS) -c -o $@ $<

clean:
	rm -f main main.o Map.o Point.o
