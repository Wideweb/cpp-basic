#pragma once

#include <optional>

enum class TicTacToeSign { None, Circle, Cross };

struct GameBoardMove {
    TicTacToeSign sign;
    int position;
};

class GameBoard {
  private:
    TicTacToeSign m_Cells[9] = {TicTacToeSign::None};

  public:
    void fill(GameBoardMove move);
    bool is_full() const;
    std::optional<TicTacToeSign> get_winner() const;
    TicTacToeSign &operator[](int index);
};