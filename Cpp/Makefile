#MakeFile

CXX_FLAG = --std=c++11 -g

# -g Includes Debugging information
all: clean main
	./interrupt_parse.o

main: interrupt_parse.cpp
	g++ $(CXX_FLAG) interrupt_parse.cpp -o interrupt_parse.o

test: clean testing.cpp
	g++ $(CXX_FLAG) testing.cpp -o testing.o
	./testing.o

clean:
	rm -f interrupt_parse testing *.o