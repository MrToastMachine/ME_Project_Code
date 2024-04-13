# Makefile

CXX_FLAGS = --std=c++11 -g

all:

test: test.o heap.o
	g++ $(CXX_FLAGS) -O0 -o test test.o heap.o

test.o: test.cpp
	g++ -c $(CXX_FLAGS) test.cpp

examheap: examheap.o heap.o
	g++ $(CXX_FLAGS) -O0 -o examheap examheap.o heap.o

examheap.o: examheap.cpp
	g++ -c $(CXX_FLAGS) examheap.cpp

heap.o: heap.cpp
	g++ -c $(CXX_FLAGS) heap.cpp

clean:
	rm -f examheap test *.o
