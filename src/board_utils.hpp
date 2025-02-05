#ifndef BOARD_UTILS_HPP
#define BOARD_UTILS_HPP 1

#include "board.hpp"
#include "kk2/gen.hpp"

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

bool exist_can_put(Board board, int color) {
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
    while (board.count(0) + board.count(1) < count) {
        if (!exist_can_put(board, 0) && !exist_can_put(board, 1)) break;
        random_put(board, 0);
        board.flip();
    }
    return board;
}

int can_put_num(const Board &board, int color) {
    int res = 0;
    for (int d = 0; d < Board::SIZE * Board::SIZE; d++) {
        int x = d / Board::SIZE;
        int y = d % Board::SIZE;
        if (board.can_put(x, y, color)) res++;
    }
    return res;
}

int eval(const Board &board, int color) {
    int now = can_put_num(board, color);
    int opp = can_put_num(board, color ^ 1);
    if (now == 0 and opp == 0) {
        if (now > opp) return 1e9;
        if (now < opp) return -1e9;
        return 0;
    }
    return 1 << (now / 3) + 1 << ((64 - opp) / 3);
}

#endif // BOARD_UTILS_HPP
