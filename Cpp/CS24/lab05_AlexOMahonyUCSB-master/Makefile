#Makefile
CXX_FLA = --std=c++11 -g

all: tests

run: tests
	./tests

redo: clean all

tests: intbst.cpp intbst.h tests.cpp
	g++ $(CXX_FLAG) -O0 tests.cpp -o tests

val:
	valgrind --leak-check=full ./tests

clean:
	rm -f tests *.o
