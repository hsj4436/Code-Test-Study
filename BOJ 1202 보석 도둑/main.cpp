#include <iostream>
#include <algorithm>

int N, K;
std::pair<int, int> jewels[300001];
int weights[300001];
int parents[300001];

int find_parent(int x) {
    if (parents[x] == x) {
        return x;
    } else {
        return parents[x] = find_parent(parents[x]);
    }
}

int main() {
    std::cin >> N >> K;

    for (int i = 0; i < N; i++) {
        std::cin >> jewels[i].second >> jewels[i].first;
    }

    std::sort(jewels, jewels + N, std::greater<std::pair<int, int>>());

    for (int i = 1; i < K + 1; i++) {
        std::cin >> weights[i];
        parents[i] = i;
    }
    parents[K + 1] = K + 1;

    std::sort(weights + 1, weights + K + 1);

    long long answer = 0;
    for (int i = 0; i < N; i++) {
        if (parents[1] == K + 1) {
            break;
        }
        auto it = std::upper_bound(weights + 1, weights + K + 1, jewels[i].second - 1);
        if (*it < jewels[i].second) {
            continue;
        }
        int parent = find_parent(it - weights);
        if (parent != K + 1) {
            parents[parent]++;
            answer += jewels[i].first;
        }
    }

    std::cout << answer << "\n";
    return 0;
}