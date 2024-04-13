#Makefile
CXX_FLA = --std=c++11 -g

all: testbst test_intbst

redo: clean all

testbst: testbst.o intbst.o
	g++ $(CXX_FLAG) -o testbst testbst.o intbst.o

testbst.o:
	g++ -c $(CXX_FLAG) testbst.cpp

test_intbst: test_intbst.o intbst.o
	g++ $(CXX_FLAG) -o test_intbst test_intbst.o intbst.o

test_intbst.o:
	g++ -c $(CXX_FLAG) test_intbst.cpp

intbst.o: intbst.cpp
	g++ -c $(CXX_FLAG) intbst.cpp

val:
	valgrind --leak-check=full ./testbst

clean:
	rm -f testbst test_intbst *.o
