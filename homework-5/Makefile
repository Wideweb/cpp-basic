CXX     = g++
CXXFLAGS  = -Wall -Wextra -Wpedantic -std=c++17

main: main.o shapes.o my_math.o 
	$(CXX) $(CXXFLAGS) main.o shapes.o my_math.o -o main

main.o: main.cpp shapes.hpp my_math.hpp
	$(CXX) $(CXXFLAGS) -c main.cpp

my_math.o: my_math.cpp my_math.hpp
	$(CXX) $(CXXFLAGS) -c my_math.cpp

clean:
	rm -rf *.o main