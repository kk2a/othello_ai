#ifndef EXHAUSTIVE_HPP
#define EXHAUSTIVE_HPP 1

#include <iostream>
#include <utility>
#include "board_utils.hpp"

std::pair<int, int> exhaustive_search(const Board& board, int col) {
    int score = -100;
    int put = -1;
    // 8 * 8以下だけでしか使えない
    unsigned long long exist = board.exist.to_ullong();
    while (exist != -1ull) {
        int d = __builtin_ctzll(~exist);
        exist |= 1ull << d;
        int x = d / Board::SIZE;
        int y = d % Board::SIZE;
        Board next_board = board;
        if (next_board.put(x, y, col)) {
            auto [next_score, _] = exhaustive_search(next_board, col ^ 1);
            if (score < -next_score) {
                score = -next_score;
                put = d;
            }
            // beta cut
            if (score > 0) return {score, put};
        }
    }

    if (score != -100) return {score, put};
    exist = board.exist.to_ullong();
    col ^= 1;
    while (exist != -1ull) {
        int d = __builtin_ctzll(~exist);
        exist |= 1ull << d;
        int x = d / Board::SIZE;
        int y = d % Board::SIZE;
        Board next_board = board;
        if (next_board.put(x, y, col)) {
            auto [next_score, _] = exhaustive_search(next_board, col ^ 1);
            if (score < -next_score) {
                score = -next_score;
                put = d;
            }
            // beta cut
            if (score > 0) return {-score, -1};
        }
    }
    col ^= 1;
    if (score != -100) return {-score, -1};
    return {board.count(col) - board.count(col ^ 1), -1};
}

#endif // EXHAUSTIVE_HPP
