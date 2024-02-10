#include <iostream>

int M, N;
int map[501][501];
int dp[501][501];

int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, -1, 0, 1};

int sol(int x, int y) {
    dp[x][y] = 0;

    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];

        if (nx < 0 || nx > M - 1 || ny < 0 || ny > N - 1) {
            continue;
        }

        if (map[nx][ny] < map[x][y]) {
            if (dp[nx][ny] != -1) {
                dp[x][y] += dp[nx][ny];
            } else {
                dp[x][y] += sol(nx, ny);
            }
        }
    }

    return dp[x][y];
}

int main() {
    std::cin.tie(NULL);
    std::ios::sync_with_stdio(false);

    std::cin >> M >> N;

    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            std::cin >> map[i][j];
            dp[i][j] = -1;
        }
    }

    dp[M - 1][N - 1] = 1;
    std::cout << sol(0, 0) << "\n";

    return 0;
}