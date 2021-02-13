#include "AIStrategy.hpp"

class RandomAIStrategy : public AIStrategy {
  public:
    int make_decision(GameBoard &, TicTacToeSign) const override;
};