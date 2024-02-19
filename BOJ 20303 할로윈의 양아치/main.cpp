#include <iostream>
#include <vector>

#define PII std::pair<int, int>

int N, M, K;
int candies[30001];
int parent[30001];
int dp[3001];

int find_parent(int x) {
    if (parent[x] < 0) {
        return x;
    } else {
        return parent[x] = find_parent(parent[x]);
    }
}

int main() {
    std::cin >> N >> M >> K;

    for (int i = 1; i < N + 1; i++) {
        std::cin >> candies[i];
        parent[i] = -1;
    }

    int A, B;
    for (int i = 0; i < M; i++) {
        std::cin >> A >> B;

        int pA = find_parent(A);
        int pB = find_parent(B);

        if (pA == pB) {
            continue;
        }

        if (parent[pA] < parent[pB]) {
            candies[pA] += candies[pB];
            candies[pB] = 0;
            parent[pA] += parent[pB];
            parent[pB] = pA;
        } else {
            candies[pB] += candies[pA];
            candies[pA] = 0;
            parent[pB] += parent[pA];
            parent[pA] = pB;
        }
    }

    std::vector<PII> kid_group;
    for (int i = 1; i < N + 1; i++) {
        if (parent[i] < 0) {
            kid_group.push_back({candies[i], -parent[i]});
        }
    }

    for (int i = 0; i< kid_group.size(); i++) {
        for (int j = K - 1; j > 0; j--) {
            if (j >= kid_group[i].second) {
                dp[j] = std::max(dp[j], dp[j - kid_group[i].second] + kid_group[i].first);
            }
        }
    }

    std::cout << dp[K - 1] << "\n";

    return 0;
}
