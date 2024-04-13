# Makefile
CXX_FLAG = --std=c++11 -g

all: testlist testrest

testlist: testlist.o intlist.o
	g++ $(CXX_FLAG) -o testlist testlist.o intlist.o

testrest: testrest.o intlist.o
	g++ $(CXX_FLAG) -o testrest testrest.o intlist.o

testlist.o: testlist.cpp
	g++ -c $(CXX_FLAG) testlist.cpp

testrest.o: testrest.cpp
	g++ -c $(CXX_FLAG) testrest.cpp

intlist.o: intlist.cpp
	g++ -c $(CXX_FLAG) intlist.cpp

myTests: myTests.o intlist.o
	g++ $(CXX_FLAG) -o myTests myTests.o intlist.o

myTests.o: myTests.cpp
	g++ -c $(CXX_FLAG) myTests.cpp

val:
	valgrind --leak-check=full ./myTests

clean:
	rm -f testrest testlist myTests *.o
