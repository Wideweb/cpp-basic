#pragma once

#include "../GameBoard.hpp"

class AIStrategy {
  public:
    virtual ~AIStrategy() {}
    virtual int make_decision(const GameBoard &, TicTacToeSign) const = 0;
};