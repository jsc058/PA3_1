# A simple makefile for CSE 100 PA4

CC=g++
CXXFLAGS=-std=c++11
LDFLAGS=

# if passed "type=opt" at command-line, compile with "-O3" flag (otherwise use "-g" for debugging)

ifeq ($(type),opt)
    CPPFLAGS += -g
    LDFLAGS += -g
else
    CPPFLAGS += -O3
    LDFLAGS += -O3
endif

all: pathfinder linkpredictor awardsceremony



# include what ever source code *.hpp files pathfinder relies on (these are merely the ones that were used in the solution)

pathfinder: pathfinder.o ActorGraph.o
	$(CC) $(CXXFLAGS) -o pathfinder pathfinder.o ActorGraph.hpp

pathfinder.o: pathfinder.cpp 
	$(CC) $(CXXFLAGS) $(CPPFlags) -c pathfinder.cpp 



# include what ever source code *.hpp files ActorGraph relies on (these are merely the ones that were used in the solution)

# Note: you do not have to include a *.cpp file if it aleady has a paired *.hpp file that is already included with class/method headers

ActorGraph.o: ActorGraph.hpp ActorNode.hpp MovieNode.hpp
	$(CC) $(CXXFLAGS) -c ActorGraph.hpp ActorNode.hpp MovieNode.hpp

clean:
	rm -f pathfinder *.o *.gch core*
