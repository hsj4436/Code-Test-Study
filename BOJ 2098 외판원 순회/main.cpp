#include <iostream>

#define INF 987654321

int N;
int cost[16][16];
int dp[16][1 << 16];
int all_masked;

int tsp(int cur, int state) {
    if (state == all_masked) {
        if (cost[cur][0] == 0) {
            return INF;
        } else {
            return cost[cur][0];
        }
    }

    if (dp[cur][state] != 0) {
        return dp[cur][state];
    }

    dp[cur][state] = INF;
    for (int i = 0; i < N; i++) {
        if (cost[cur][i] == 0) {
            continue;
        }
        if ((state & (1 << i)) != 0) {
            continue;
        }
        dp[cur][state] = std::min(dp[cur][state], tsp(i, state | (1 << i)) + cost[cur][i]);
    }

    return dp[cur][state];
}

int main() {
    std::cin >> N;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            std::cin >> cost[i][j];
        }
    }

    all_masked = (1 << N) - 1;

    std::cout << tsp(0, 1) << "\n";

    return 0;
}