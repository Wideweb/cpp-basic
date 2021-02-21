#include "MinMaxStrategy.hpp"

#include <limits>
#include <stdexcept>

int MinMaxStrategy::make_decision(const GameBoard &board,
                                  TicTacToeSign player) const {
    int best_score = std::numeric_limits<int>::min();
    int best_position = 0;
    for (int i = 0; i < board.size(); i++) {
        if (board[i] != TicTacToeSign::None) {
            continue;
        }

        int score = max_move(board, {player, i});
        if (score > best_score) {
            best_score = score;
            best_position = i;
        }
    }

    return best_position;
}

int MinMaxStrategy::max_move(GameBoard board, GameBoardMove move) const {
    board.fill(move);

    auto winner = board.get_winner();
    if (winner.has_value()) {
        return 10;
    }

    if (board.is_full()) {
        return 0;
    }

    int worst_score = std::numeric_limits<int>::max();
    for (int i = 0; i < board.size(); i++) {
        if (board[i] != TicTacToeSign::None) {
            continue;
        }

        int score = min_move(board, {get_next_player(move.sign), i});
        if (score < worst_score) {
            worst_score = score;
        }
    }

    return worst_score;
}

int MinMaxStrategy::min_move(GameBoard board, GameBoardMove move) const {
    board.fill(move);

    auto winner = board.get_winner();
    if (winner.has_value()) {
        return -10;
    }

    if (board.is_full()) {
        return 0;
    }

    int best_score = std::numeric_limits<int>::min();
    for (int i = 0; i < board.size(); i++) {
        if (board[i] != TicTacToeSign::None) {
            continue;
        }

        int score = max_move(board, {get_next_player(move.sign), i});
        if (score > best_score) {
            best_score = score;
        }
    }

    return best_score;
}

TicTacToeSign MinMaxStrategy::get_next_player(TicTacToeSign player) const {
    return player == TicTacToeSign::Circle ? TicTacToeSign::Cross
                                           : TicTacToeSign::Circle;
}
