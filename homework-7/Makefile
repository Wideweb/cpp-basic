CXX     	= g++
CXXFLAGS  	= -Wall -Wextra -Wpedantic -std=c++17
ODIR		= build
EXECUTABLE	= main

main: main.o TicTacToeGame.o RandomStrategy.o MinMaxStrategy.o MinMaxStrategy.o UserController.o AIController.o GameBoard.o GameBoardRender.o
	mkdir -p $(ODIR)
	$(CXX) $(CXXFLAGS) $(ODIR)/main.o $(ODIR)/TicTacToeGame.o $(ODIR)/RandomStrategy.o $(ODIR)/MinMaxStrategy.o $(ODIR)/UserController.o $(ODIR)/AIController.o $(ODIR)/GameBoard.o $(ODIR)/GameBoardRender.o -o $(ODIR)/$(EXECUTABLE)

main.o: main.cpp Game/TicTacToeGame.hpp Game/GameBoard.hpp Game/GameBoardRender.hpp Game/Controllers/PlayerController.hpp Game/AI/AIStrategy.hpp Game/AI/MinMaxStrategy.hpp Game/AI/RandomStrategy.hpp Game/AI/MinMaxStrategy.hpp Game/Controllers/AIController.hpp Game/Controllers/UserController.hpp
	mkdir -p $(ODIR)
	$(CXX) $(CXXFLAGS) -c main.cpp -o $(ODIR)/main.o

TicTacToeGame.o: Game/TicTacToeGame.cpp Game/TicTacToeGame.hpp Game/GameBoard.hpp Game/GameBoardRender.hpp Game/Controllers/PlayerController.hpp Game/AI/MinMaxStrategy.hpp Game/Controllers/AIController.hpp Game/Controllers/UserController.hpp
	mkdir -p $(ODIR)
	$(CXX) $(CXXFLAGS) -c Game/TicTacToeGame.cpp -o $(ODIR)/TicTacToeGame.o

RandomStrategy.o: Game/AI/RandomStrategy.cpp Game/AI/RandomStrategy.hpp Game/AI/AIStrategy.hpp
	mkdir -p $(ODIR)
	$(CXX) $(CXXFLAGS) -c Game/AI/RandomStrategy.cpp -o $(ODIR)/RandomStrategy.o

MinMaxStrategy.o: Game/AI/MinMaxStrategy.cpp Game/AI/MinMaxStrategy.hpp Game/AI/AIStrategy.hpp
	mkdir -p $(ODIR)
	$(CXX) $(CXXFLAGS) -c Game/AI/MinMaxStrategy.cpp -o $(ODIR)/MinMaxStrategy.o

AIController.o: Game/Controllers/AIController.cpp Game/Controllers/AIController.hpp Game/Controllers/PlayerController.hpp Game/GameBoard.hpp Game/AI/AIStrategy.hpp
	mkdir -p $(ODIR)
	$(CXX) $(CXXFLAGS) -c Game/Controllers/AIController.cpp -o $(ODIR)/AIController.o

UserController.o: Game/Controllers/UserController.cpp Game/Controllers/UserController.hpp Game/Controllers/PlayerController.hpp Game/GameBoard.hpp
	mkdir -p $(ODIR)
	$(CXX) $(CXXFLAGS) -c Game/Controllers/UserController.cpp -o $(ODIR)/UserController.o

GameBoardRender.o: Game/GameBoardRender.cpp Game/GameBoardRender.hpp
	mkdir -p $(ODIR)
	$(CXX) $(CXXFLAGS) -c Game/GameBoardRender.cpp -o $(ODIR)/GameBoardRender.o

GameBoard.o: Game/GameBoard.cpp Game/GameBoard.hpp
	mkdir -p $(ODIR)
	$(CXX) $(CXXFLAGS) -c Game/GameBoard.cpp -o $(ODIR)/GameBoard.o

clean:
	rm -r $(ODIR)

run:
	./$(ODIR)/$(EXECUTABLE)
