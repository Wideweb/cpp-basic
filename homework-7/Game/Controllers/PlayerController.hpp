#pragma once

#include "../GameBoard.hpp"

class PlayerController {
  protected:
    const GameBoard &m_Board;
    TicTacToeSign m_Sign;

  public:
    PlayerController(const GameBoard &board, TicTacToeSign sign)
        : m_Board(board), m_Sign(sign) {}
    virtual ~PlayerController() {}

    virtual GameBoardMove move() const = 0;
};