#ifndef BOARD_HPP
#define BOARD_HPP 1

#include <cassert>
#include <iostream>
#include <string>
#include <bitset>

struct Board {
    constexpr static int SIZE = 8;

    constexpr static int BLACK = 0;
    constexpr static int WHITE = 1;
    std::bitset<SIZE * SIZE> board, exist;

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
        std::cout << std::endl;
        std::cout << " ";
        for (int i = 0; i < SIZE; i++) std::cout << i;
        std::cout << std::endl;
        for (int i = 0; i < SIZE; i++) {
            std::cout << i;
            for (int j = 0; j < SIZE; j++) {
                if (!exist[i * SIZE + j]) std::cout << '.';
                else if (board[i * SIZE + j]) std::cout << 'W';
                else std::cout << 'B';
            }
            std::cout << std::endl;
        }
    }

    void print(int color) const {
        std::cout << std::endl;
        std::cout << " ";
        for (int i = 0; i < SIZE; i++) std::cout << i;
        std::cout << std::endl;
        for (int i = 0; i < SIZE; i++) {
            std::cout << i;
            for (int j = 0; j < SIZE; j++) {
                if (!exist[i * SIZE + j]) {
                    if (can_put(i, j, color)) std::cout << 'o';
                    else std::cout << '.';
                }
                else if (board[i * SIZE + j]) std::cout << 'W';
                else std::cout << 'B';
            }
            std::cout << std::endl;
        }
    }

    int count(int color) const {
        if (color == BLACK) {
            return (~board & exist).count();
        } else {
            return (board & exist).count();
        }
    }

    bool put(int x, int y, int color) {
        assert(0 <= x && x < SIZE);
        assert(0 <= y && y < SIZE);
        assert(!exist[x * SIZE + y]);

        int dx[] = {0, 1, 1, 1, 0, -1, -1, -1};
        int dy[] = {1, 1, 0, -1, -1, -1, 0, 1};

        bool can_put = false;
        for (int k = 0; k < 8; k++) {
            int nx = x;
            int ny = y;
            while (true) {
                nx += dx[k];
                ny += dy[k];
                if (nx < 0 || SIZE <= nx || ny < 0 || SIZE <= ny) break;
                if (!exist[nx * SIZE + ny]) break;
                if (board[nx * SIZE + ny] == color) {
                    nx -= dx[k], ny -= dy[k];
                    while (nx != x || ny != y) {
                        can_put = true;
                        board[nx * SIZE + ny].flip();
                        nx -= dx[k], ny -= dy[k];
                    }
                    break;
                }
            }
        }
        if (can_put) {
            exist[x * SIZE + y].flip();
            board[x * SIZE + y] = color;
        }
        return can_put;
    }

    bool can_put(int x, int y, int color) const {
        if (exist[x * SIZE + y]) return false;

        int dx[] = {0, 1, 1, 1, 0, -1, -1, -1};
        int dy[] = {1, 1, 0, -1, -1, -1, 0, 1};

        for (int k = 0; k < 8; k++) {
            int nx = x;
            int ny = y;
            while (true) {
                nx += dx[k];
                ny += dy[k];
                if (nx < 0 || SIZE <= nx || ny < 0 || SIZE <= ny) break;
                if (!exist[nx * SIZE + ny]) break;
                if (board[nx * SIZE + ny] == color && (nx - dx[k] != x || ny - dy[k] != y)) return true;
                else if (board[nx * SIZE + ny] == color) break;
            }
        }
        return false;
    }

    void flip() {
        board ^= exist;
    }

    Board get_flip() const {
        Board res = *this;
        res.flip();
        return res;
    }
};

#endif // BOARD_HPP
