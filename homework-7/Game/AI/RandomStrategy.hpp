#include "AIStrategy.hpp"

class RandomStrategy : public AIStrategy {
  public:
    int make_decision(const GameBoard &, TicTacToeSign) const override;
};