FLAGS=-std=c++11 -finstrument-functions

all: main tests

main: main.cpp mymatrix.cpp
	g++ $(FLAGS) main.cpp mymatrix.cpp -o main

tests: tests.o mymatrix.cpp
	g++ $(FLAGS) tests.o mymatrix.cpp -o tests
tests.o: tests.cpp
	g++ $(FLAGS) -c -o tests.o tests.cpp 
clean:
	rm -f main tests tests.o
