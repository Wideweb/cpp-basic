#include "RandomStrategy.hpp"

#include <stdexcept>

int RandomStrategy::make_decision(const GameBoard &board, TicTacToeSign) const {
    for (int i = 0; i < board.size(); i++) {
        if (board[i] == TicTacToeSign::None) {
            return i;
        }
    }

    throw std::runtime_error("no empty cell");
}