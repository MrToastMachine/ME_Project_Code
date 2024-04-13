# Makefile

CXX_FLAG = --std=c++11 -g

all: test game

test: tests.o cards.o utility.o
	g++ $(CXX_FLAG) -o test tests.o cards.o utility.o

tests.o: tests.cpp
	g++ -c $(CXX_FLAG) tests.cpp

game: game.o cards.o utility.o
	g++ $(CXX_FLAG) -o game game.o cards.o utility.o

game.o: main.cpp
	g++ -c $(CXX_FLAG) main.cpp -o game.o

cards.o: cards.cpp
	g++ -c $(CXX_FLAG) cards.cpp

utility.o: utility.cpp
	g++ -c $(CXX_FLAG) utility.cpp

play:
	./game a0.txt b0.txt

clean:
	rm -rf game test *.o