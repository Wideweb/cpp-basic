CXX     	= g++
CXXFLAGS  	= -Wall -Wextra -Wpedantic -std=c++17
ODIR		= build
EXECUTABLE	= main

main: main.o
	mkdir -p $(ODIR)
	$(CXX) $(CXXFLAGS) $(ODIR)/main.o -o $(ODIR)/$(EXECUTABLE)

main.o: main.cpp Stack.hpp
	mkdir -p $(ODIR)
	$(CXX) $(CXXFLAGS) -c main.cpp -o $(ODIR)/main.o

clean:
	rm -r $(ODIR)

run:
	./$(ODIR)/$(EXECUTABLE)
