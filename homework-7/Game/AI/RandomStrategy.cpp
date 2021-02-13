#include "RandomStrategy.hpp"

#include <stdexcept>

int RandomAIStrategy::make_decision(GameBoard &board, TicTacToeSign) const {
    for (int i = 0; i < 9; i++) {
        auto &cell = board[i];
        if (cell == TicTacToeSign::None) {
            return i;
        }
    }

    throw std::runtime_error("no empty cell");
}