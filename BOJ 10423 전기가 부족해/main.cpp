#include <iostream>
#include <queue>

#define PII std::pair<int, int>

int N, M, K;
bool is_power[1001];
int parents[1001];

int find_parent(int x) {
    if (parents[x] == x) {
        return x;
    } else {
        return parents[x] = find_parent(parents[x]);
    }
}

bool is_end() {
    for (int i = 1; i < N + 1; i++) {
        int p = find_parent(i);
        if (!is_power[p]) {
            return false;
        }
    }
    return true;
}

int main() {
    std::cin >> N >> M >> K;

    int city = 0;
    for (int i = 0; i < K; i++) {
        std::cin >> city;
        is_power[city] = true;
    }

    for (int i = 1; i < N + 1; i++) {
        parents[i] = i;
    }

    int U, V, W;
    std::priority_queue<std::pair<int, PII>, std::vector<std::pair<int, PII>>, std::greater<std::pair<int, PII>>> pq;
    for (int i = 0; i < M; i++) {
        std::cin >> U >> V >> W;
        pq.push({W, {U, V}});
    }

    int answer = 0;
    while (!is_end()) {
        int cost = pq.top().first;
        U = pq.top().second.first;
        V = pq.top().second.second;
        pq.pop();

        int pu = find_parent(U);
        int pv = find_parent(V);

        if (pu == pv) {
            continue;
        }

        if (is_power[pu] && is_power[pv]) {
            continue;
        }

        answer += cost;
        if (is_power[pu] && !is_power[pv]) {
            parents[pv] = pu;
        } else if (!is_power[pu] && is_power[pv]) {
            parents[pu] = pv;
        } else {
            if (pu < pv) {
                parents[pv] = pu;
            } else {
                parents[pu] = pv;
            }
        }
    }

    std::cout << answer << "\n";

    return 0;
}