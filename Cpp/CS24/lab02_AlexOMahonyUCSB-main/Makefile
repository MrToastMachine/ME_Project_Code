# Makefile

all: tests
	./RunCar

tests: tests.cpp car.cpp car.hpp perf.hpp doors.hpp
	g++ -std=c++11 -O0 -g tests.cpp -o RunCar

clean:
	rm RunCar

v:
	valgrind --leak-check=full ./RunCar