#ifndef BOARD_UTILS_HPP
#define BOARD_UTILS_HPP 1

#include "board.hpp"
#include "random.hpp"

void random_put(Board &board, int color) {
    std::vector<int> perm = kk2::random::perm<int>(Board::SIZE * Board::SIZE);
    for (int d : perm) {
        int x = d / Board::SIZE;
        int y = d % Board::SIZE;
        if (board.can_put(x, y, color)) {
            board.put(x, y, color);
            return;
        }
    }
}

bool exist_can_put(const Board &board, int color) {
    for (int d = 0; d < Board::SIZE * Board::SIZE; d++) {
        int x = d / Board::SIZE;
        int y = d % Board::SIZE;
        if (board.can_put(x, y, color)) return true;
    }
    return false;
}

// これは適当．最終的な手番は不明
Board random_board(int count) {
    Board board;
    while (board.count(Board::BLACK) + board.count(Board::WHITE) < count) {
        if (!exist_can_put(board, Board::BLACK) && !exist_can_put(board, Board::WHITE)) break;
        random_put(board, Board::BLACK);
        board.flip();
    }
    return board;
}

#endif // BOARD_UTILS_HPP
