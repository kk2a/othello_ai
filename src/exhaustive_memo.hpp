#ifndef EXHAUSTIVE_MEMO_HPP
#define EXHAUSTIVE_MEMO_HPP 1

#include "Nyaan/hashmap.hpp"
Nyaan::HashMap<std::pair<unsigned long long, unsigned long long>, std::pair<int, int>> memo;

struct memo_init {
    memo_init() {
        memo.reserve(1 << 21);
    }
} memo_init;

std::pair<int, int> exhaustive_memo(Board board) {
    if (memo.count({board.board.to_ullong(), board.exist.to_ullong()})) {
        return memo[{board.board.to_ullong(), board.exist.to_ullong()}];
    }
    if (board.exist == -1ull) {
        return {board.count(0) - board.count(1), -1};
    }
    bool not_memo = board.exist.count() >= 60;
    int score = -100;
    int put = -1;
    unsigned long long exist = ~board.exist.to_ullong();
    Board next_board = board;
    while (exist) {
        int d = __builtin_ctzll(exist);
        exist ^= 1ull << d;
        int x = d / Board::SIZE;
        int y = d % Board::SIZE;
        if (next_board.put(x, y, 0)) {
            next_board.flip();
            auto [next_score, _] = exhaustive_memo(next_board);
            next_board = board;
            if (score < -next_score) {
                score = -next_score;
                put = d;
            }
            // beta cut
            if (score > 0) {
                if (not_memo) return {score, put};
                return memo[{board.board.to_ullong(), board.exist.to_ullong()}] = {score, put};
            }
        }
    }
    if (score != -100) {
        if (not_memo) return {score, put};
        return memo[{board.board.to_ullong(), board.exist.to_ullong()}] = {score, put};
    }

    exist = ~board.exist.to_ullong();
    board.flip();
    if (memo.count({board.board.to_ullong(), board.exist.to_ullong()})) {
        return memo[{board.board.to_ullong(), board.exist.to_ullong()}];
    }
    next_board = board;
    while (exist) {
        int d = __builtin_ctzll(exist);
        exist ^= 1ull << d;
        int x = d / Board::SIZE;
        int y = d % Board::SIZE;
        if (next_board.put(x, y, 0)) {
            next_board.flip();
            auto [next_score, _] = exhaustive_memo(next_board);
            next_board = board;
            if (score < -next_score) {
                score = -next_score;
                put = d;
            }
            // beta cut
            if (score > 0) {
                if (not_memo) return {-score, -1};
                memo[{board.board.to_ullong(), board.exist.to_ullong()}] = {score, d};
                board.flip();
                return memo[{board.board.to_ullong(), board.exist.to_ullong()}] = {-score, -1};
            }
        }
    }
    if (score != -100) {
        if (not_memo) return {-score, -1};
        memo[{board.board.to_ullong(), board.exist.to_ullong()}] = {score, put};
        board.flip();
        return memo[{board.board.to_ullong(), board.exist.to_ullong()}] = {-score, -1};
    }
    if (not_memo) return {board.count(1) - board.count(0), -1};
    memo[{board.board.to_ullong(), board.exist.to_ullong()}] = {board.count(0) - board.count(1), -1};
    board.flip();
    return memo[{board.board.to_ullong(), board.exist.to_ullong()}] = {board.count(0) - board.count(1), -1};
}

#endif // EXHAUSTIVE_MEMO_HPP
