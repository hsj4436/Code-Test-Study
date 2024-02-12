#include <iostream>
#include <cstring>
#include <queue>

#define PII std::pair<int, int>

int N;
int EX, EY;
char world[9][9];
bool visited[9][9];

int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, -1, 0, 1};

bool bfs(int x, int y, char kind) {
    std::queue<PII> q;
    q.push({x, y});
    visited[x][y] = true;

    while (!q.empty()) {
        int cur_x = q.front().first;
        int cur_y = q.front().second;
        q.pop();

        for (int i = 0; i < 4; i++) {
            int nx = cur_x + dx[i];
            int ny = cur_y + dy[i];

            if (nx < 0 || nx > EX || ny < 0 || ny > EY) {
                continue;
            }

            if (visited[nx][ny]) {
                continue;
            }

            if (world[nx][ny] == '-') {
                continue;
            }

            if (world[nx][ny] != '#' && world[nx][ny] != '.' && world[nx][ny] != kind) {
                return false;
            }
            visited[nx][ny] = true;
            q.push({nx, ny});
        }
    }

    return true;
}

bool dfs(int x, int y) {
    if (x == EX && y == EY) {
        std::memset(visited, false, sizeof(visited));
        for (int i = 1; i < EX; i++) {
            for (int j = 1; j < EY; j++) {
                if (world[i][j] != '#' && world[i][j] != '.' && world[i][j] != '-') {
                    if (!visited[i][j]) {
                        if (!bfs(i, j, world[i][j])) {
                            return false;
                        }
                    }
                }
            }
        }
        return true;
    }

    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];

        if (nx < 0 || nx > EX || ny < 0 || ny > EY) {
            continue;
        }

        if (world[nx][ny] == '#') {
            world[nx][ny] = '-';
            if (dfs(nx, ny)) {
                return true;
            }
            world[nx][ny] = '#';
        }
    }

    return false;
}

int main() {
    std::cin >> N;

    EX = 2 * N, EY = 2 * N;

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            world[i][j] = '#';
        }
    }

    for (int i = 1; i < EX; i += 2) {
        for (int j = 1; j < EY; j += 2) {
            std::cin >> world[i][j];
        }
    }

    world[0][0] = '-';
    if (dfs(0, 0)) {
        std::cout << "yes\n";
        for (int i = 0; i < 4 * N + 3; i++) {
            std::cout << "#";
        }
        std::cout << "\n";
        for (int i = 0; i < EX + 1; i++) {
            std::cout << "#";
            for (int j = 0; j < EY + 1; j++) {
                if (i % 2 != 0 && j % 2 != 0) {
                    std::cout << " " << world[i][j] << " ";
                } else if (world[i][j] == '-') {
                    if (i % 2 == 0) {
                        if (j % 2 == 0) {
                            std::cout << "+";
                        } else {
                            std::cout << "---";
                        }
                    } else {
                        std::cout << "|";
                    }
                } else {
                    if (i % 2 == 0) {
                        if (j % 2 == 0) {
                            std::cout << "+";
                        } else {
                            std::cout << "   ";
                        }
                    } else {
                        std::cout << " ";
                    }
                }
            }
            std::cout << "#\n";
        }
        for (int i = 0; i < 4 * N + 3; i++) {
            std::cout << "#";
        }
        std::cout << "\n";
    } else {
        std::cout << "no\n";
    }
    return 0;
}