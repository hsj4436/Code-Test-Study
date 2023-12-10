#include <iostream>
#include <vector>
#include <algorithm>

int N;
std::vector<std::vector<int>> graph(200001, std::vector<int>(0, 0));
int ability[200001];
bool visited[200001];
int dp[200001][2]; // 0 - I'm mentee or nothing, 1 - I'm mentor

void dfs(int cur) {
    int not_mentor = 0;
    int mentor = 0;

    int from = 0;
    for (int i : graph[cur]) {
        if (visited[i]) {
            from = i;
            continue;
        }
        visited[i] = true;
        dfs(i);
        dp[cur][0] += std::max(dp[i][0], dp[i][1]);
        not_mentor += std::max(dp[i][0], dp[i][1]);
    }

    for (int i : graph[cur]) {
        if (i == from) {
            continue;
        }
        mentor = std::max(mentor, not_mentor - std::max(dp[i][0], dp[i][1]) + ability[cur] * ability[i] + dp[i][0]);
    }

    dp[cur][1] = std::max(not_mentor, mentor);

}

int main() {
    std::cin.tie(NULL);
    std::cout.tie(NULL);
    std::ios::sync_with_stdio(false);

    std::cin >> N;

    int supervisor;
    for (int i = 2; i < N + 1; i++) {
        std::cin >> supervisor;
        graph[i].push_back(supervisor);
        graph[supervisor].push_back(i);
    }

    for (int i = 1; i < N + 1; i++) {
        std::cin >> ability[i];
    }

    visited[1] = true;
    dfs(1);

    std::cout << std::max(dp[1][0], dp[1][1]) << "\n";

    return 0;
}
