CXX     	= g++
CXXFLAGS  	= -Wall -Wextra -Wpedantic -std=c++17
EXECUTABLE	= main

main: main.o
	$(CXX) $(CXXFLAGS) main.o -o ${EXECUTABLE}

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp

clean:
	rm -rf *.o main

run:
	./${EXECUTABLE}
