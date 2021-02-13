#pragma once

#include "../GameBoard.hpp"

class AIStrategy {
  public:
    virtual ~AIStrategy() {}
    virtual int make_decision(GameBoard &, TicTacToeSign) const = 0;
};