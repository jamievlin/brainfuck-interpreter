CXX=g++
CXXFLAGS=-Wall -std=c++17 -O2

default: brainfuck

brainfuck: brainfuck.cc

clean:
	rm -f brainfuck *.exe *.a *.o
