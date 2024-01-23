#include <iostream>
#include <vector>
#include <cmath>

int N;
bool visited[100001];
std::vector<int> edges[100001];
int dp[100001][17];
int max_color;

void dfs(int cur) {
    for (int i = 1; i < max_color + 1; i++) {
        dp[cur][i] = i;
    }

    for (int next : edges[cur]) {
        if (visited[next]) {
            continue;
        }
        visited[next] = true;
        dfs(next);
        for (int i = 1; i < max_color + 1; i++) {
            int local_min = (int)1e9;
            for (int j = 1; j < max_color + 1; j++) {
                if (i == j) {
                    continue;
                }
                local_min = std::min(dp[next][j], local_min);
            }
            dp[cur][i] += local_min;
        }
    }
}

int main() {
    std::cin >> N;
    max_color = std::floor(std::log2(N));
    int x, y;
    for (int i = 0; i < N - 1; i++) {
        std::cin >> x >> y;
        edges[x].push_back(y);
        edges[y].push_back(x);
    }

    visited[1] = true;
    dfs(1);

    int answer = (int)1e9;
    for (int i = 1; i < max_color + 1; i++) {
        answer = std::min(dp[1][i], answer);
    }

    std::cout << answer << "\n";

    return 0;
}