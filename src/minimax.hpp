#ifndef MINIMAX_HPP
#define MINIMAX_HPP 1

#include <utility>
#include "board.hpp"

template <int (*get_score)(const Board&, int)> struct minimax {
    static std::pair<int, int> search(Board board, int alpha, int beta, int depth) {
        // board.print();
        if (depth == 0) return {get_score(board, 0), -1};
        int put = -1;
        Board next_board = board;
        for (int d = 0; d < Board::SIZE * Board::SIZE; d++) {
            if (board.exist[d]) continue;
            int x = d / Board::SIZE;
            int y = d % Board::SIZE;
            if (next_board.put(x, y, 0)) {
                next_board.flip();
                auto [score, _] = search(next_board, -beta, -alpha, depth - 1);
                next_board = board;
                score = -score;
                if (score > alpha) {
                    alpha = score;
                    put = d;
                    if (alpha >= beta) return {alpha, put};
                }
            }
        }
        if (put != -1) return {alpha, put};

        board.flip();
        int tmp = alpha;
        alpha = -beta;
        beta = -tmp;
        for (int d = 0; d < Board::SIZE * Board::SIZE; d++) {
            if (board.exist[d]) continue;
            int x = d / Board::SIZE;
            int y = d % Board::SIZE;
            if (next_board.put(x, y, 0)) {
                next_board.flip();
                auto [score, _] = search(next_board, -beta, -alpha, depth - 1);
                next_board = board;
                score = -score;
                if (score > alpha) {
                    alpha = score;
                    put = d;
                    if (alpha >= beta) return {-alpha, -1};
                }
            }
        }
        if (put != -1) return {-alpha, -1};
        board.flip();
        // std::cout << 1 << std::endl;
        return {get_score(board, 0), -1};
    }
};

#endif // MINIMAX_HPP
