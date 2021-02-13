#pragma once

#include "GameBoard.hpp"

class GameBoardRender {
  public:
    void draw(const GameBoard &board) const;

  private:
    void draw_sign(TicTacToeSign sign, int index) const;
};