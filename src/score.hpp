#ifndef SCORE_HPP
#define SCORE_HPP 1

#include <cmath>
#include "board.hpp"
#include "board_utils.hpp"

int weight[8][8] = {
    {30, -12, 0, -1, -1, 0, -12, 30},
    {-12, -15, -3, -3, -3, -3, -15, -12},
    {0, -3, 0, -1, -1, 0, -3, 0},
    {-1, -3, -1, -1, -1, -1, -3, -1},
    {-1, -3, -1, -1, -1, -1, -3, -1},
    {0, -3, 0, -1, -1, 0, -3, 0},
    {-12, -15, -3, -3, -3, -3, -15, -12},
    {30, -12, 0, -1, -1, 0, -12, 30}
};

int score_1_1(const Board &board, int color) {
    int res = 0;
    for (int i = 0; i < Board::SIZE; i++) {
        for (int j = 0; j < Board::SIZE; j++) {
            if (board.exist[i * Board::SIZE + j]) {
                res += weight[i][j] * (board.board[i * Board::SIZE + j] == color ? 1 : -1);
            }
        }
    }
    int now = can_put_num(board, color);
    int opp = can_put_num(board, color ^ 1);
    if (now == 0 && opp == 0) {
        if (board.count(color) > board.count(color ^ 1)) return 1e9;
        if (board.count(color) < board.count(color ^ 1)) return -1e9;
        return 0;
    }
    res += (now - opp) * 1;
    return res;
}

int score_10_1(const Board &board, int color) {
    int res = 0;
    for (int i = 0; i < Board::SIZE; i++) {
        for (int j = 0; j < Board::SIZE; j++) {
            if (board.exist[i * Board::SIZE + j]) {
                res += weight[i][j] * (board.board[i * Board::SIZE + j] == color ? 10 : -10);
            }
        }
    }
    int now = can_put_num(board, color);
    int opp = can_put_num(board, color ^ 1);
    if (now == 0 && opp == 0) {
        if (board.count(color) > board.count(color ^ 1)) return 1e9;
        if (board.count(color) < board.count(color ^ 1)) return -1e9;
        return 0;
    }
    res += (now - opp) * 1;
    return res;
}

int score_1_10(const Board& board, int color) {
    int res = 0;
    for (int i = 0; i < Board::SIZE; i++) {
        for (int j = 0; j < Board::SIZE; j++) {
            if (board.exist[i * Board::SIZE + j]) {
                res += weight[i][j] * (board.board[i * Board::SIZE + j] == color ? 1 : -1);
            }
        }
    }
    int now = can_put_num(board, color);
    int opp = can_put_num(board, color ^ 1);
    if (now == 0 && opp == 0) {
        if (board.count(color) > board.count(color ^ 1)) return 1e9;
        if (board.count(color) < board.count(color ^ 1)) return -1e9;
        return 0;
    }
    res += (now - opp) * 10;
    return res;
}

#endif // SCORE_HPP
