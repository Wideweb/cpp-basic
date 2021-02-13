#include "AIController.hpp"

#include <chrono>
#include <iostream>
#include <thread>

AIController::AIController(GameBoard &board, TicTacToeSign sign,
                           std::unique_ptr<AIStrategy> strategy)
    : PlayerController(board, sign), m_Strategy(std::move(strategy)) {}

GameBoardMove AIController::move() const {
    std::cout << "wait..." << std::endl;

    using namespace std::chrono_literals;
    std::this_thread::sleep_for(1000ms);

    int position = m_Strategy->make_decision(m_Board, m_Sign);
    return {m_Sign, position};
}
