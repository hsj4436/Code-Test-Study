#include <iostream>
#include <queue>
#include <cstring>

int TC;
int H, W;
char building[102][102];
bool visited[102][102];
bool key[26];

int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, -1, 0, 1};

int main() {
    std::cin >> TC;

    for (int tc = 0; tc < TC; tc++) {
        std::memset(visited, false, sizeof(visited));
        std::memset(key, false, sizeof(key));
        std::cin >> H >> W;
        for (int i = 0; i < H + 2; i++) {
            for (int j = 0; j < W + 2; j++) {
                building[i][j] = '.';
            }
        }

        std::queue<std::pair<int, int>> movable;
        std::queue<std::pair<int, int>> blocked[26];
        for (int i = 1; i < H + 1; i++) {
            std::string row;
            std::cin >> row;
            for (int j = 1; j < W + 1; j++) {
                building[i][j] = row[j - 1];
            }
        }

        std::string keys;
        std::cin >> keys;
        if (keys != "0") {
            for (auto c : keys) {
                key[c - 'a'] = true;
            }
        }

        for (int i = 0; i < H + 2; i++) {
            if (i == 0 || i == H + 1) {
                for (int j = 0; j < W + 2; j++) {
                    if (building[i][j] == '.' && !visited[i][j]) {
                        visited[i][j] = true;
                        movable.push({i, j});
                    }
                }
            } else {
                if (building[i][0] == '.' && !visited[i][0]) {
                    visited[i][0] = true;
                    movable.push({i, 0});
                }
                if (building[i][W + 1] == '.' && !visited[i][W + 1]) {
                    visited[i][W + 1] = true;
                    movable.push({i, W + 1});
                }
            }
        }

        int answer = 0;
        while (!movable.empty()) {
            int x = movable.front().first;
            int y = movable.front().second;
            movable.pop();

            for (int i = 0; i < 4; i++) {
                int nx = x + dx[i];
                int ny = y + dy[i];

                if (nx < 1 || nx > H || ny < 1 || ny > W) {
                    continue;
                }

                if (visited[nx][ny] || building[nx][ny] == '*') {
                    continue;
                }

                visited[nx][ny] = true;
                if (building[nx][ny] == '.') {
                    movable.push({nx, ny});
                } else if (building[nx][ny] == '$') {
                    movable.push({nx, ny});
                    answer++;
                } else if ('a' <= building[nx][ny] && building[nx][ny] <= 'z') {
                    if (key[building[nx][ny] - 'a']) {
                        movable.push({nx, ny});
                    } else {
                        key[building[nx][ny] - 'a'] = true;
                        movable.push({nx, ny});
                        while (!blocked[building[nx][ny] - 'a'].empty()) {
                            movable.push(blocked[building[nx][ny] - 'a'].front());
                            blocked[building[nx][ny] - 'a'].pop();
                        }
                    }
                } else if ('A' <= building[nx][ny] && building[nx][ny] <= 'Z') {
                    if (key[building[nx][ny] - 'A']) {
                        movable.push({nx, ny});
                    } else {
                        blocked[building[nx][ny] - 'A'].push({nx, ny});
                    }
                }
            }
        }

        std::cout << answer << "\n";
    }

    return 0;
}