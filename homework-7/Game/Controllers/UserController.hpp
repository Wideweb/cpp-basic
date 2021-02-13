#pragma once

#include "PlayerController.hpp"

class UserController : public PlayerController {
  public:
    UserController(GameBoard &board, TicTacToeSign sign);
    GameBoardMove move() const override;
};