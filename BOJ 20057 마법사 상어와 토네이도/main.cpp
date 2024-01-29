#include <iostream>

int N;
int grid[510][510];

int dx[4] = {0, 1, 0, -1};
int dy[4] = {-1, 0, 1, 0};

int outer = 0;

void move(int x, int y, int direction) {
    // {x, y} == 문제 예시에서의 y
    // direction 0 - left, 1 - bottom, 2 - right, 3 - up
    int one = grid[x][y] * 0.01;
    int two = grid[x][y] * 0.02;
    int five = grid[x][y] * 0.05;
    int seven = grid[x][y] * 0.07;
    int ten = grid[x][y] * 0.1;
    int last = grid[x][y] - 2 * ten - 2 * seven - five - 2 * two - 2 * one;
    if (direction == 0) {
        grid[x - 1][y + 1] += one;
        grid[x + 1][y + 1] += one;
        grid[x - 1][y] += seven;
        grid[x + 1][y] += seven;
        if (x - 2 >= 0) {
            grid[x - 2][y] += two;
        } else {
            outer += two;
        }
        grid[x + 2][y] += two;
        grid[x - 1][y - 1] += ten;
        grid[x + 1][y - 1] += ten;
        if (y - 2 >= 0) {
            grid[x][y - 2] += five;
        } else {
            outer += five;
        }
        grid[x][y - 1] += last;
    } else if (direction == 1) {
        grid[x - 1][y + 1] += one;
        grid[x - 1][y - 1] += one;
        grid[x][y + 1] += seven;
        grid[x][y - 1] += seven;
        grid[x][y + 2] += two;
        if (y - 2 >= 0) {
            grid[x][y - 2] += two;
        } else {
            outer += two;
        }
        grid[x + 1][y + 1] += ten;
        grid[x + 1][y - 1] += ten;
        grid[x + 2][y] += five;
        grid[x + 1][y] += last;
    } else if (direction == 2) {
        grid[x - 1][y - 1] += one;
        grid[x + 1][y - 1] += one;
        grid[x - 1][y] += seven;
        grid[x + 1][y] += seven;
        grid[x + 2][y] += two;
        if (x - 2 >= 0) {
            grid[x - 2][y] += two;
        } else {
            outer += two;
        }
        grid[x - 1][y + 1] += ten;
        grid[x + 1][y + 1] += ten;
        grid[x][y + 2] += five;
        grid[x][y + 1] += last;
    } else {
        grid[x + 1][y + 1] += one;
        grid[x + 1][y - 1] += one;
        grid[x][y + 1] += seven;
        grid[x][y - 1] += seven;
        grid[x][y + 2] += two;
        if (y - 2 >= 0) {
            grid[x][y - 2] += two;
        } else {
            outer += two;
        }
        grid[x - 1][y + 1] += ten;
        grid[x - 1][y - 1] += ten;
        if (x - 2 >= 0) {
            grid[x - 2][y] += five;
        } else {
            outer += five;
        }
        grid[x - 1][y] += last;
    }
    grid[x][y] = 0;
}

int main() {
    std::cin >> N;

    for (int i = 1; i < N + 1; i++) {
        for (int j = 1; j < N + 1; j++) {
            std::cin >> grid[i][j];
        }
    }

    int x = N / 2 + 1, y = N / 2 + 1;
    int n = 1;
    bool end = false;
    while (true) {
        if (end) {
            break;
        }
        for (int i = 0; i < 4; i++) {
            if (i == 2) {
                n++;
            }
            if (end) {
                break;
            }
            for (int j = 0; j < n; j++) {
                x += dx[i];
                y += dy[i];
                if (x == 1 && y == 0) {
                    end = true;
                    break;
                }
                move(x, y, i);
            }
        }
        n++;
    }

    for (int i = 0; i < N + 3; i++) {
        for (int j = 0; j < N + 3; j++) {
            if (i < 1 || i > N) {
                outer += grid[i][j];
            } else {
                if (j == 0 || j > N) {
                    outer += grid[i][j];
                }
            }
        }
    }

    std::cout << outer << "\n";
    return 0;
}