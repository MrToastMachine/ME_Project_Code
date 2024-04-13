#Makefile

CXX_FLAGS = --std=c++11 -g

all: eval

run: eval
	./evalfull

eval: evalfull.cpp
	g++ $(CXX_FLAGS) -O0 evalfull.cpp -o evalfull

usestack: usestack.cpp intstack.h
	g++ $(CXX_FLAGS) -O0 usestack.cpp -o usestack

clean:
	rm -f usestack evalfull *.o