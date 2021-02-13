#include "GameBoard.hpp"

#include <iostream>
#include <stdexcept>

void GameBoard::fill(GameBoardMove move) {
    TicTacToeSign &cell = m_Cells[move.position];
    if (cell != TicTacToeSign::None) {
        throw std::runtime_error("cell is bussy");
    }

    cell = move.sign;
}

bool GameBoard::is_full() const {
    for (int i = 0; i < 9; i++) {
        if (m_Cells[i] == TicTacToeSign::None) {
            return false;
        }
    }

    return true;
}

std::optional<TicTacToeSign> GameBoard::get_winner() const {
    for (int i = 0; i < 3; i++) {
        if (m_Cells[i * 3] == m_Cells[i * 3 + 1] &&
            m_Cells[i * 3 + 1] == m_Cells[i * 3 + 2] &&
            m_Cells[i * 3] != TicTacToeSign::None) {

            return m_Cells[i * 3];
        }

        if (m_Cells[i] == m_Cells[i + 3] && m_Cells[i + 3] == m_Cells[i + 6] &&
            m_Cells[i] != TicTacToeSign::None) {

            return m_Cells[i];
        }
    }

    if (m_Cells[0] == m_Cells[4] && m_Cells[4] == m_Cells[8] &&
        m_Cells[0] != TicTacToeSign::None) {
        return m_Cells[0];
    }

    if (m_Cells[2] == m_Cells[4] && m_Cells[4] == m_Cells[6] &&
        m_Cells[2] != TicTacToeSign::None) {
        return m_Cells[0];
    }

    return std::nullopt;
}

TicTacToeSign &GameBoard::operator[](int index) { return m_Cells[index]; }