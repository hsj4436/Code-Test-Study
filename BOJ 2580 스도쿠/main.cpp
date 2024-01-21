#include <iostream>
#include <cstring>

int sudoku[9][9];
bool row[10][10];
bool col[10][10];
bool square[10][10];

// 5, 4  3,3 ~ 5,5
// (5 / 3) * 3
// (4 / 3) * 3
bool make_sudoku(int index) {
    int x = index / 9;
    int y = index % 9;

    while (sudoku[x][y] != 0) {
        if (index == 81) {
            break;
        }
        index++;
        x = index / 9;
        y = index % 9;
    }

    if (index == 81) {
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                std::cout << sudoku[i][j] << " ";
            }
            std::cout << "\n";
        }
        return true;
    }

    int x_square = (x / 3) * 3;
    int y_square = (y / 3);
    for (int i = 1; i < 10; i++) {
        if (!row[x][i] && !col[i][y] && !square[x_square + y_square][i]) {
            row[x][i] = true;
            col[i][y] = true;
            square[x_square + y_square][i] = true;
            sudoku[x][y] = i;
            if (make_sudoku(index + 1)) {
                return true;
            }
            sudoku[x][y] = 0;
            row[x][i] = false;
            col[i][y] = false;
            square[x_square + y_square][i] = false;
        }
    }

    return false;
}

int main() {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            std::cin >> sudoku[i][j];
        }
    }

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            row[i][sudoku[i][j]] = true;
            col[sudoku[j][i]][i] = true;
        }
    }

    for (int i = 0; i < 81; i++) {
        int x = i / 9;
        int y = i % 9;
        int x_square = (x / 3) * 3;
        int y_square = (y / 3);
        square[x_square + y_square][sudoku[x][y]] = true;
    }

    make_sudoku(0);

    return 0;
}
