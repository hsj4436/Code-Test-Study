#include <iostream>

int M, N;
int map[501][501];
int dp[501][501];
bool visited[501][501];

int dx[4] = {1, -1, 0, 0};
int dy[4] = {0, 0, 1, -1};

int dfs(int x, int y) {
    if (dp[x][y] != 0) {
        return dp[x][y];
    }

    if (x == M - 1 && y == N - 1) {
        return 1;
    }

    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];

        if (nx < 0 || nx > M - 1 || ny < 0 || ny > N - 1) {
            continue;
        }

        if (map[nx][ny] >= map[x][y]) {
            continue;
        }

        if (visited[nx][ny]) {
            dp[x][y] += dp[nx][ny];
        } else {
            dp[x][y] += dfs(nx, ny);
        }
    }

    visited[x][y] = true;
    return dp[x][y];
}


int main() {
    std::cin.tie(NULL);
    std::cout.tie(NULL);
    std::ios::sync_with_stdio(false);

    std::cin >> M >> N;

    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            std::cin >> map[i][j];
        }
    }

    dfs(0, 0);

    std::cout << dp[0][0] << "\n";
    return 0;
}
