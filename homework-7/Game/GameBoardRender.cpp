#include "GameBoardRender.hpp"

#include <iostream>

void GameBoardRender::draw(const GameBoard &board) const {
    std::cout << "     |     |     " << std::endl;
    std::cout << "  ";
    draw_sign(board[0], 1);
    std::cout << "  |  ";
    draw_sign(board[1], 2);
    std::cout << "  |  ";
    draw_sign(board[2], 3);
    std::cout << std::endl;
    std::cout << "     |     |     " << std::endl;

    std::cout << "-----------------" << std::endl;

    std::cout << "     |     |     " << std::endl;
    std::cout << "  ";
    draw_sign(board[3], 4);
    std::cout << "  |  ";
    draw_sign(board[4], 5);
    std::cout << "  |  ";
    draw_sign(board[5], 6);
    std::cout << std::endl;
    std::cout << "     |     |     " << std::endl;

    std::cout << "-----------------" << std::endl;

    std::cout << "     |     |     " << std::endl;
    std::cout << "  ";
    draw_sign(board[6], 7);
    std::cout << "  |  ";
    draw_sign(board[7], 8);
    std::cout << "  |  ";
    draw_sign(board[8], 9);
    std::cout << std::endl;
    std::cout << "     |     |     " << std::endl;

    std::cout << std::endl;
}

void GameBoardRender::draw_sign(TicTacToeSign sign, int index) const {
    if (sign == TicTacToeSign::None) {
        std::cout << index;
    }
    if (sign == TicTacToeSign::Circle) {
        std::cout << "O";
    }
    if (sign == TicTacToeSign::Cross) {
        std::cout << "X";
    }
}