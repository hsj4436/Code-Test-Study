#include <iostream>
#include <queue>

#define AIR 2
#define PII std::pair<int, int>

int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, -1, 0, 1};

int N, M;
int grid[101][101];
bool visited[101][101];

int main() {
    std::cin >> N >> M;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            std::cin >> grid[i][j];
        }
    }

    std::queue<PII> q;
    grid[0][0] = AIR;
    visited[0][0] = true;
    q.push({0, 0});

    while (!q.empty()) {
        int x = q.front().first;
        int y = q.front().second;
        q.pop();

        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if (nx < 0 || nx > N - 1 || ny < 0 || ny > M - 1) {
                continue;
            }

            if (visited[nx][ny] || grid[nx][ny] == 1) {
                continue;
            }
            visited[nx][ny] = true;
            grid[nx][ny] = AIR;
            q.push({nx, ny});
        }
    }

    int T = 0;
    while (true) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                if (grid[i][j] == 1) {
                    int airs = 0;
                    for (int k = 0; k < 4; k++) {
                        int nx = i + dx[k];
                        int ny = j + dy[k];

                        if (grid[nx][ny] == AIR) {
                            airs++;
                        }
                    }
                    if (airs >= 2) {
                        q.push({i, j});
                    }
                }
            }
        }

        if (q.empty()) {
            break;
        }

        while (!q.empty()) {
            int x = q.front().first;
            int y = q.front().second;
            q.pop();

            visited[x][y] = true;
            grid[x][y] = AIR;

            for (int i = 0; i < 4; i++) {
                int nx = x + dx[i];
                int ny = y + dy[i];

                if (nx < 0 || nx > N - 1 || ny < 0 || ny > M - 1) {
                    continue;
                }

                if (visited[nx][ny]) {
                    continue;
                }

                if (grid[nx][ny] == 0) {
                    visited[nx][ny] = true;
                    grid[nx][ny] = AIR;
                    q.push({nx, ny});
                }
            }
        }

        T++;
    }

    std::cout << T << "\n";

    return 0;
}