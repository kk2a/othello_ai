#ifndef BOARD_HPP
#define BOARD_HPP 1

#include <cassert>
#include <iostream>
#include <string>
#include <bitset>

struct Board {
    constexpr static int SIZE = 8;

    enum class Color { BLACK = 0, WHITE = 1 };

    // flagがたっている -> 白, たっていない -> 黒
    Board() {
        exist[(SIZE / 2 - 1) * SIZE + SIZE / 2 - 1].flip();
        exist[(SIZE / 2 - 1) * SIZE + SIZE / 2].flip();
        exist[(SIZE / 2) * SIZE + SIZE / 2 - 1].flip();
        exist[(SIZE / 2) * SIZE + SIZE / 2].flip();

        board[(SIZE / 2 - 1) * SIZE + SIZE / 2 - 1].flip();
        board[(SIZE / 2) * SIZE + SIZE / 2].flip();
    }

    void print() const {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                if (!exist[i * SIZE + j]) std::cout << '.';
                else if (board[i * SIZE + j]) std::cout << 'W';
                else std::cout << 'B';
            }
            std::cout << std::endl;
        }
    }

    int count(Color color) const {
        if (color == Color::BLACK) {
            return (~board & exist).count();
        } else {
            return (board & exist).count();
        }
    }

    void put(int x, int y, Color color) {
        assert(0 <= x && x < SIZE);
        assert(0 <= y && y < SIZE);
        assert(!exist[x * SIZE + y]);
        exist[x * SIZE + y].flip();
        board[x * SIZE + y] = int(color);

        int di[] = {0, 1, 1, 1, 0, -1, -1, -1};
        int dj[] = {1, 1, 0, -1, -1, -1, 0, 1};

        for (int k = 0; k < 8; k++) {
            int nx = x;
            int ny = y;
            while (true) {
                nx += di[k];
                ny += dj[k];
                if (nx < 0 || SIZE <= nx || ny < 0 || SIZE <= ny) break;
                if (!exist[nx * SIZE + ny]) break;
                if (board[nx * SIZE + ny] == int(color)) {
                    nx -= di[k], ny -= dj[k];
                    while (nx != x || ny != y) {
                        board[nx * SIZE + ny].flip();
                        nx -= di[k], ny -= dj[k];
                    }
                    break;
                }
            }
        }
    }

  private:
    std::bitset<SIZE * SIZE> board;
    std::bitset<SIZE * SIZE> exist;
};


#endif // BOARD_HPP
