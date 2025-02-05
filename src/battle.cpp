#include <iostream>
#include "board.hpp"
#include "board_utils.hpp"
#include "score.hpp"
#include "minimax.hpp"
#include "exhaustive_memo2.hpp"

int main() {
    int t = 1000;
    {
        int win = 0, lose = 0, draw = 0;
        for (int i = 0; i < t; i++) {
            if (i == t / 4) std::cout << i << std::endl;
            if (i == t / 2) std::cout << i << std::endl;
            if (i == t / 4 * 3) std::cout << i << std::endl;
            memo2.clear();
            // std::cout << win << " " << lose << " " << draw << std::endl;
            Board board;
            while (true) {
                if (!exist_can_put(board, Board::BLACK)) {
                    if (!exist_can_put(board, Board::WHITE)) break;
                } else {
                    if (board.exist.count() >= 50) {
                        auto [_, d] = exhaustive_memo2(board);
                        int x = d / Board::SIZE;
                        int y = d % Board::SIZE;
                        board.put(x, y, Board::BLACK);
                    } else {
                        auto [_, d] = minimax<score_1_1>::search(board, -1e9-1, 1e9+1, 4);
                        // board.print();
                        // std::cout << _ << " " << d << std::endl;
                        int x = d / Board::SIZE;
                        int y = d % Board::SIZE;
                        board.put(x, y, Board::BLACK);
                    }
                }
                if (exist_can_put(board, Board::WHITE)) {
                    random_put(board, 1);
                }
            }
            int black = board.count(Board::BLACK);
            int white = board.count(Board::WHITE);
            if (black > white) win++;
            else if (black < white) lose++;
            else draw++;
        }
        std::cout << "1_1 " << win << " " << lose << " " << draw << std::endl;
    }
    {
        int win = 0, lose = 0, draw = 0;
        for (int i = 0; i < t; i++) {
            memo2.clear();
            Board board;
            while (true) {
                if (!exist_can_put(board, Board::BLACK)) {
                    if (!exist_can_put(board, Board::WHITE)) break;
                } else {
                    if (board.exist.count() >= 50) {
                        auto [_, d] = exhaustive_memo2(board);
                        int x = d / Board::SIZE;
                        int y = d % Board::SIZE;
                        board.put(x, y, Board::BLACK);
                    } else {
                        auto [_, d] = minimax<score_10_1>::search(board, -1e9-1, 1e9+1, 4);
                        int x = d / Board::SIZE;
                        int y = d % Board::SIZE;
                        board.put(x, y, Board::BLACK);
                    }
                }
                if (exist_can_put(board, Board::WHITE)) {
                    random_put(board, 1);
                }
            }
            int black = board.count(Board::BLACK);
            int white = board.count(Board::WHITE);
            if (black > white) win++;
            else if (black < white) lose++;
            else draw++;
        }
        std::cout << "10_1 " << win << " " << lose << " " << draw << std::endl;
    }
    {
        int win = 0, lose = 0, draw = 0;
        for (int i = 0; i < t; i++) {
            memo2.clear();
            Board board;
            while (true) {
                if (!exist_can_put(board, Board::BLACK)) {
                    if (!exist_can_put(board, Board::WHITE)) break;
                } else {
                    if (board.exist.count() >= 50) {
                        auto [_, d] = exhaustive_memo2(board);
                        int x = d / Board::SIZE;
                        int y = d % Board::SIZE;
                        board.put(x, y, Board::BLACK);
                    } else {
                        auto [_, d] = minimax<score_1_10>::search(board, -1e9-1, 1e9+1, 4);
                        int x = d / Board::SIZE;
                        int y = d % Board::SIZE;
                        board.put(x, y, Board::BLACK);
                    }
                }
                if (exist_can_put(board, Board::WHITE)) {
                    random_put(board, 1);
                }
            }
            int black = board.count(Board::BLACK);
            int white = board.count(Board::WHITE);
            if (black > white) win++;
            else if (black < white) lose++;
            else draw++;
        }
        std::cout << "1_10 " << win << " " << lose << " " << draw << std::endl;
    }
    return 0;
}