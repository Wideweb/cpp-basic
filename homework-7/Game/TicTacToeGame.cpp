#include "TicTacToeGame.hpp"

#include "AI/MinMaxStrategy.hpp"
#include "Controllers/AIController.hpp"
#include "Controllers/UserController.hpp"

#include <cstdlib>
#include <iostream>

TicTacToeGame::TicTacToeGame() {
    m_Plyaer2 = std::make_unique<AIController>(
        m_Board, TicTacToeSign::Cross, std::make_unique<MinMaxStrategy>());
    m_Plyaer1 =
        std::make_unique<UserController>(m_Board, TicTacToeSign::Circle);
}

void TicTacToeGame::run() {
    m_Running = true;

    while (m_Running) {
        draw();
        update();
    }
    draw();

    switch (m_Result) {
    case GameResult::Player1:
        std::cout << "Player 1 won the game!" << std::endl;
        break;
    case GameResult::Player2:
        std::cout << "Player 2 won the game!" << std::endl;
        break;
    case GameResult::Draw:
        std::cout << "Draw!" << std::endl;
        break;

    default:
        break;
    }
}

void TicTacToeGame::draw() {
#if defined _WIN32
    system("cls");
#elif defined(__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
    system("clear");
#elif defined(__APPLE__)
    system("clear");
#endif

    if (m_isFirst) {
        std::cout << "     Player 1" << std::endl;
    } else {
        std::cout << "     Player 2" << std::endl;
    }

    m_BoardRender.draw(m_Board);
}

void TicTacToeGame::update() {
    const auto move = get_current_player().move();

    if (move.position < 0 || move.position >= m_Board.size()) {
        return;
    }

    if (m_Board[move.position] != TicTacToeSign::None) {
        return;
    }

    m_Board.fill(move);

    const auto winner = m_Board.get_winner();
    if (winner.has_value()) {
        m_Result = m_isFirst ? GameResult::Player1 : GameResult::Player2;
        m_Running = false;
        return;
    }

    if (m_Board.is_full()) {
        m_Result = GameResult::Draw;
        m_Running = false;
        return;
    }

    next_player();
}

PlayerController &TicTacToeGame::get_current_player() {
    return m_isFirst ? *m_Plyaer1 : *m_Plyaer2;
}

void TicTacToeGame::next_player() { m_isFirst = !m_isFirst; }
