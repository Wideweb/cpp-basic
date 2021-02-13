#pragma once

#include "PlayerController.hpp"

class UserController : public PlayerController {
  public:
    UserController(const GameBoard &board, TicTacToeSign sign);
    GameBoardMove move() const override;
};