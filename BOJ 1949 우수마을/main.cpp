#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>

int N;
int dp[10001][2]; // 0 - normal, 1 - good
std::vector<int> populations(1, 0);
bool visited[10001];
std::vector<std::vector<int>> adjacent(10001, std::vector<int>());

void dfs(int current) {
    if (visited[current]) {
        return;
    }

    visited[current] = true;
    dp[current][1] = populations[current];

    for (int i = 0; i < adjacent[current].size(); i++) {
        if (visited[adjacent[current][i]]) {
            continue;
        }

        dfs(adjacent[current][i]);

        dp[current][0] += std::max(dp[adjacent[current][i]][0], dp[adjacent[current][i]][1]);
        dp[current][1] += dp[adjacent[current][i]][0];
    }
}

int main() {
    std::cin.tie(NULL);
    std::cout.tie(NULL);
    std::ios::sync_with_stdio(false);

    std::cin >> N;

    int population = 0;
    for (int i = 0; i < N; i++) {
        std::cin >> population;
        populations.push_back(population);
    }

    int village_a = 0, village_b = 0;
    for (int i = 0; i < N - 1; i++) {
        std::cin >> village_a >> village_b;
        adjacent[village_a].push_back(village_b);
        adjacent[village_b].push_back(village_a);
    }

    dfs(1);

    std::cout << std::max(dp[1][0], dp[1][1]) << "\n";

    return 0;
}