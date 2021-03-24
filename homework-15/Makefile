CXX     	= g++
CXXFLAGS  	= -Wall -Wextra -Wpedantic -std=c++17
ODIR		= build
EXECUTABLE	= main

main: main.o LibApplication.o MainMenu.o BaseMenu.o LibService.o
	mkdir -p $(ODIR)
	$(CXX) $(CXXFLAGS) $(ODIR)/main.o $(ODIR)/LibApplication.o $(ODIR)/MainMenu.o $(ODIR)/BaseMenu.o $(ODIR)/LibService.o -o $(ODIR)/$(EXECUTABLE)

main.o: src/main.cpp src/LibApplication.hpp src/Menu/MainMenu.hpp src/Menu/BaseMenu.hpp
	mkdir -p $(ODIR)
	$(CXX) $(CXXFLAGS) -c src/main.cpp -o $(ODIR)/main.o

LibApplication.o: src/LibApplication.cpp src/LibApplication.hpp
	mkdir -p $(ODIR)
	$(CXX) $(CXXFLAGS) -c src/LibApplication.cpp -o $(ODIR)/LibApplication.o

MainMenu.o: src/Menu/MainMenu.cpp src/Menu/MainMenu.hpp src/LibService.hpp
	mkdir -p $(ODIR)
	$(CXX) $(CXXFLAGS) -c src/Menu/MainMenu.cpp -o $(ODIR)/MainMenu.o

BaseMenu.o: src/Menu/BaseMenu.cpp src/Menu/BaseMenu.hpp
	mkdir -p $(ODIR)
	$(CXX) $(CXXFLAGS) -c src/Menu/BaseMenu.cpp -o $(ODIR)/BaseMenu.o

LibService.o: src/LibService.cpp src/LibService.hpp
	mkdir -p $(ODIR)
	$(CXX) $(CXXFLAGS) -c src/LibService.cpp -o $(ODIR)/LibService.o

clean:
	rm -r $(ODIR)

run:
	./$(ODIR)/$(EXECUTABLE)
