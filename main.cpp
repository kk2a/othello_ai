#include <iostream>
#include "board.hpp"

int main() {
    Board board;
    board.print();

    board.put(2, 3, Board::Color::BLACK);
    board.print();
    std::cout << "Black: " << board.count(Board::Color::BLACK) << std::endl;
    std::cout << "White: " << board.count(Board::Color::WHITE) << std::endl;

    board.put(2, 4, Board::Color::WHITE);
    board.print();
    std::cout << "Black: " << board.count(Board::Color::BLACK) << std::endl;
    std::cout << "White: " << board.count(Board::Color::WHITE) << std::endl;
    return 0;
}