#ifndef EXHAUSTIVE_MEMO3_HPP
#define EXHAUSTIVE_MEMO3_HPP 1

#include "Nyaan/hashmap.hpp"
Nyaan::HashMap<std::pair<unsigned long long, unsigned long long>, std::pair<int, int>> memo3;
#include "kk2/gen.hpp"

struct memo3_init {
    memo3_init() {
        memo3.reserve(1 << 21);
    }
} memo3_init;

std::pair<int, int> exhaustive_memo3(Board board) {
    if (memo3.count({board.board.to_ullong(), board.exist.to_ullong()})) {
        return memo3[{board.board.to_ullong(), board.exist.to_ullong()}];
    }
    if (board.exist == -1ull) {
        return {board.count(0) - board.count(1), -1};
    }
    bool not_memo = board.exist.count() >= 60;
    int score = -100;
    int put = -1;
    unsigned long long exist = ~board.exist.to_ullong();
    Board next_board = board;
    int w = 0;
    while (exist) {
        // int d = (w++ & 1) ? __builtin_ctzll(exist) : 63 - __builtin_clzll(exist);
        int d = 63 - __builtin_clzll(exist);
        exist ^= 1ull << d;
        int x = d / Board::SIZE;
        int y = d % Board::SIZE;
        if (next_board.put(x, y, 0)) {
            next_board.flip();
            auto [next_score, _] = exhaustive_memo3(next_board);
            next_board = board;
            if (score < -next_score) {
                score = -next_score;
                put = d;
            }
            // beta cut
            if (score > 0) {
                if (not_memo) return {score, put};
                return memo3[{board.board.to_ullong(), board.exist.to_ullong()}] = {score, put};
            }
        }
    }
    if (score != -100) {
        if (not_memo) return {score, put};
        return memo3[{board.board.to_ullong(), board.exist.to_ullong()}] = {score, put};
    }

    board.flip();
    if (memo3.count({board.board.to_ullong(), board.exist.to_ullong()})) {
        return memo3[{board.board.to_ullong(), board.exist.to_ullong()}];
    }
    next_board = board;
    exist = ~board.exist.to_ullong();
    while (exist) {
        // int d = (w++ & 1) ? __builtin_ctzll(exist) : 63 - __builtin_clzll(exist);
        int d = 63 - __builtin_clzll(exist);
        exist ^= 1ull << d;
        int x = d / Board::SIZE;
        int y = d % Board::SIZE;
        if (next_board.put(x, y, 0)) {
            next_board.flip();
            auto [next_score, _] = exhaustive_memo3(next_board);
            next_board = board;
            if (score < -next_score) {
                score = -next_score;
                put = d;
            }
            // beta cut
            if (score > 0) {
                if (not_memo) return {-score, -1};
                memo3[{board.board.to_ullong(), board.exist.to_ullong()}] = {score, d};
                board.flip();
                return memo3[{board.board.to_ullong(), board.exist.to_ullong()}] = {-score, -1};
            }
        }
    }
    if (score != -100) {
        if (not_memo) return {-score, -1};
        memo3[{board.board.to_ullong(), board.exist.to_ullong()}] = {score, put};
        board.flip();
        return memo3[{board.board.to_ullong(), board.exist.to_ullong()}] = {-score, -1};
    }
    if (not_memo) return {board.count(1) - board.count(0), -1};
    memo3[{board.board.to_ullong(), board.exist.to_ullong()}] = {board.count(0) - board.count(1), -1};
    board.flip();
    return memo3[{board.board.to_ullong(), board.exist.to_ullong()}] = {board.count(0) - board.count(1), -1};
}

#endif // EXHAUSTIVE_MEMO3_HPP
