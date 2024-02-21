#include <iostream>
#include <queue>
#include <math.h>

#define LL long long
#define PLL std::pair<LL, LL>

int N, M;
PLL gods[1001];
bool connected[1001];
int parent[1001];

int find_parent(int x) {
    if (parent[x] == x) {
        return parent[x];
    } else {
        return parent[x] = find_parent(parent[x]);
    }
}

int main() {
    std::cin >> N >> M;

    for (int i = 1; i < N + 1; i++) {
        std::cin >> gods[i].first >> gods[i].second;
        parent[i] = i;
    }

    int count = 0;
    int L, R;
    for (int i = 0; i < M; i++) {
        std::cin >> L >> R;

        int pL = find_parent(L);
        int pR = find_parent(R);

        if (pL == pR) {
            continue;
        }
        count++;
        if (pL < pR) {
            parent[pR] = pL;
        } else {
            parent[pL] = pR;
        }
        connected[R] = true;
        connected[L] = true;
    }

    std::priority_queue<std::pair<double, PLL>> pq;
    for (int i = 1; i < N + 1; i++) {
        for (int j = i + 1; j < N + 1; j++) {
            if (parent[i] == parent[j]) {
                continue;
            }
            double distance = std::sqrt(std::pow(gods[i].first - gods[j].first, 2) + std::pow(gods[i].second - gods[j].second, 2));
            pq.push({-distance, {i, j}});
        }
    }

    double answer = 0.0;
    while (count != N - 1) {
        double d = -pq.top().first;
        LL x = pq.top().second.first;
        LL y = pq.top().second.second;
        pq.pop();

        int pX = find_parent(x);
        int pY = find_parent(y);

        if (pX == pY) {
            continue;
        }

        count++;
        if (pX < pY) {
            parent[pY] = pX;
        } else {
            parent[pX] = pY;
        }
        answer += d;
    }

    std::cout << std::fixed;
    std::cout.precision(2);
    std::cout << answer << "\n";

    return 0;
}