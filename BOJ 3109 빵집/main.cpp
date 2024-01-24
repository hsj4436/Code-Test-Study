#include <iostream>
#include <vector>
#include <algorithm>

int R, C;
char ground[10001][501];
bool visited[10001][501];

bool dfs(int x, int y) {
    if (y == C - 1) {
        return true;
    }
    if (x - 1 >= 0 && y + 1 < C && ground[x - 1][y + 1] == '.' && !visited[x - 1][y + 1]) {
        visited[x - 1][y + 1] = true;
        if (dfs(x - 1, y + 1)) {
            return true;
        }
    }

    if (y + 1 < C && ground[x][y + 1] == '.' && !visited[x][y + 1]) {
        visited[x][y + 1] = true;
        if (dfs(x, y + 1)) {
            return true;
        }
    }

    if (x + 1 < R && y + 1 < C && ground[x + 1][y + 1] == '.' && !visited[x + 1][y + 1]) {
        visited[x + 1][y + 1] = true;
        if (dfs(x + 1, y + 1)) {
            return true;
        }
    }

    return false;
}

int main() {
    std::cin >> R >> C;

    for (int i = 0; i < R; i++) {
        std::string row;
        std::cin >> row;
        for (int j = 0; j < C; j++) {
            ground[i][j] = row[j];
        }
    }

    int answer = 0;
    for (int i = 0; i < R; i++) {
        if (dfs(i, 0)) {
            visited[i][0] = true;
            answer++;
        }
    }

    std::cout << answer << "\n";

    return 0;
}