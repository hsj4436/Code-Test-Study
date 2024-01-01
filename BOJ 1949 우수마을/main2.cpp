#include <iostream>
#include <vector>

int N;
int population[10001];
std::vector<int> edges[10001];
bool visited[10001];
int dp[10001][2];

void dfs(int cur) {

    if (dp[cur][0] != 0 || dp[cur][1] != 0) {
        return;
    }
    dp[cur][1] = population[cur];

    for (int next : edges[cur]) {
        if (visited[next]) {
            continue;
        }
        visited[next] = true;
        dfs(next);
        dp[cur][0] += std::max(dp[next][0], dp[next][1]);
        dp[cur][1] += dp[next][0];
    }
}

int main() {
    std::cin >> N;
    for (int i = 1; i < N + 1; i++) {
        std::cin >> population[i];
    }

    for (int i = 0; i < N - 1; i++) {
        int from, to;
        std::cin >> from >> to;
        edges[from].push_back(to);
        edges[to].push_back(from);
    }

    visited[1] = true;
    dfs(1);

    std::cout << std::max(dp[1][0], dp[1][1]) << "\n";

    return 0;
}