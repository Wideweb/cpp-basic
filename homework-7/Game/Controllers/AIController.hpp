#pragma once

#include "../AI/AIStrategy.hpp"
#include "../GameBoard.hpp"
#include "PlayerController.hpp"

#include <memory>

class AIController : public PlayerController {
  private:
    std::unique_ptr<AIStrategy> m_Strategy;

  public:
    AIController(GameBoard &board, TicTacToeSign sign,
                 std::unique_ptr<AIStrategy> strategy);
    virtual ~AIController() {}

    GameBoardMove move() const override;
};