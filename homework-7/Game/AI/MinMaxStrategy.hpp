#include "AIStrategy.hpp"

class MinMaxStrategy : public AIStrategy {
  public:
    int make_decision(GameBoard &board, TicTacToeSign player) const override;

  private:
    int max_move(GameBoard board, GameBoardMove move) const;
    int min_move(GameBoard board, GameBoardMove move) const;
    TicTacToeSign get_next_player(TicTacToeSign player) const;
};