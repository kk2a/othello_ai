#ifndef MINIMAX_HPP
#define MINIMAX_HPP 1

#include <utility>
#include "board.hpp"
#include "board_utils.hpp"

std::pair<int, int> minimax(Borad board, int dep) {
    int score = -(1 << 30);
    int put = -1;
    Board next_board = board;
    for (int d = 0; d < Board::SIZE * Borad::SIZE; d++) {
        int x = d / Board::SIZE;
        int y = d % Board::SIZE;
        if (next_board.put(x, y, 0)) {
            auto [next_score, _] = minimax(next_board);
            next_board = board;
            if (score < -next_score) {
                score = -next_score;
                put = d;
            }
        }
    }
}

#endif // MINIMAX_HPP
