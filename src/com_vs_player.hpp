#ifndef COM_VS_PLAYER_HPP
#define COM_VS_PLAYER_HPP 1

#include <iostream>
#include "board.hpp"
#include "board_utils.hpp"
// #include "exhaustive.hpp"
#include "exhaustive_memo2.hpp"
#include "minimax.hpp"
#include "score.hpp"

struct ComVsPlayer {
    Board board;
    ComVsPlayer() {}

    void player_put() {
        int x, y;
        std::cin >> x >> y;
        board.put(x, y, Board::BLACK);
    }

    void com_put(int x, int y) {
        board.put(x, y, Board::WHITE);
    }

    void run() {
        while (true) {
            board.print(Board::BLACK);
            std::cout << "Black: " << board.count(Board::BLACK) << std::endl;
            std::cout << "White: " << board.count(Board::WHITE) << std::endl;
            if (!exist_can_put(board, Board::BLACK)) {
                if (!exist_can_put(board, Board::WHITE)) break;
                std::cout << "White pass" << std::endl;
            } else {
                if (board.exist.count() >= 48) {
                    auto [_, d] = exhaustive_memo2(board);
                    std::cout << _ << " " << d << std::endl;
                }

                player_put();
                // if (board.exist.count() < 48) {
                //     auto [_, d] = minimax(board, -1e9, 1e9, 5);
                //     std::cout << _ << " " << d << std::endl;
                //     int x = d / Board::SIZE;
                //     int y = d % Board::SIZE;
                //     board.put(x, y, Board::BLACK);
                //     // com_put(x, y);
                // } else {
                //     auto [_, d] = exhaustive_memo2(board);
                //     std::cout << _ << std::endl;
                //     int x = d / Board::SIZE;
                //     int y = d % Board::SIZE;
                //     board.put(x, y, Board::BLACK);
                //     // com_put(x, y);
                // }
                // board.print(Board::WHITE);
                std::cout << "Black: " << board.count(Board::BLACK) << std::endl;
                std::cout << "White: " << board.count(Board::WHITE) << std::endl;
            }

            if (!exist_can_put(board, Board::WHITE)) {
                if (!exist_can_put(board, Board::BLACK)) break;
                std::cout << "Black pass" << std::endl;
            } else {
                board.flip();
                    if (board.exist.count() < 48) {
                    auto [_, d] = minimax<score_1_10>::search(board, -1e9 - 1, 1e9+1, 8);
                    board.flip();
                    std::cout << _ << " " << d << std::endl;
                    int x = d / Board::SIZE;
                    int y = d % Board::SIZE;
                    com_put(x, y);
                } else {
                    auto [_, d] = exhaustive_memo2(board);
                    board.flip();
                    std::cout << _ << std::endl;
                    int x = d / Board::SIZE;
                    int y = d % Board::SIZE;
                    com_put(x, y);
                }


                std::cout << "Black: " << board.count(Board::BLACK) << std::endl;
                std::cout << "White: " << board.count(Board::WHITE) << std::endl;
            }
        }
    }
};

#endif // COM_VS_PLAYER_HPP
