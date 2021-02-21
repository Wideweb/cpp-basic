#pragma once

#include "Controllers/PlayerController.hpp"
#include "GameBoard.hpp"
#include "GameBoardRender.hpp"

#include <memory>

class TicTacToeGame {
  private:
    enum class GameResult { Draw, Player1, Player2 };

    GameBoard m_Board;
    GameBoardRender m_BoardRender;

    std::unique_ptr<PlayerController> m_Plyaer1;
    std::unique_ptr<PlayerController> m_Plyaer2;

    bool m_isFirst = true;
    bool m_Running = false;
    GameResult m_Result;

  public:
    TicTacToeGame();
    void run();

  private:
    void draw();
    void update();
    PlayerController &get_current_player();
    void next_player();
};
