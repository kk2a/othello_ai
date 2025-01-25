#ifndef COM_VS_PLAYER_HPP
#define COM_VS_PLAYER_HPP 1

#include <iostream>
#include "board.hpp"
#include "board_utils.hpp"
#include "exhaustive.hpp"

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
                auto [score, d] = exhaustive_search(board, 0);
                std::cout << score << " " << d / Board::SIZE << " " << d % Board::SIZE << std::endl;
                player_put();
                board.print(Board::WHITE);
                std::cout << "Black: " << board.count(Board::BLACK) << std::endl;
                std::cout << "White: " << board.count(Board::WHITE) << std::endl;
            }
            if (!exist_can_put(board, Board::WHITE)) {
                if (!exist_can_put(board, Board::BLACK)) break;
                std::cout << "Black pass" << std::endl;
            } else {
                // なんかいい感じにおく
                // for (int d = 0; d < Board::SIZE * Board::SIZE; d++) {
                //     int x = d / Board::SIZE;
                //     int y = d % Board::SIZE;
                //     if (board.can_put(x, y, Board::Color::WHITE)) {
                //         com_put(x, y);
                //         break;
                //     }
                // }

                auto [_, d] = exhaustive_search(board, 1);
                std::cout << _ << std::endl;
                int x = d / Board::SIZE;
                int y = d % Board::SIZE;
                com_put(x, y);

                std::cout << "Black: " << board.count(Board::BLACK) << std::endl;
                std::cout << "White: " << board.count(Board::WHITE) << std::endl;
            }
        }
    }
};

#endif // COM_VS_PLAYER_HPP
