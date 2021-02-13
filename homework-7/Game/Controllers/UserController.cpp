#include "UserController.hpp"

#include <iostream>

UserController::UserController(GameBoard &board, TicTacToeSign sign)
    : PlayerController(board, sign) {}

GameBoardMove UserController::move() const {
    char position;

    std::cout << "chose position [1-9]: ";
    std::cin >> position;

    return {m_Sign, position - '1'};
}