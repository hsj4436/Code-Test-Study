#include <iostream>
#include <vector>
#include <queue>

#define INF 987654321
#define PII std::pair<int, int>

int N, M;
int A, B, D;
std::vector<PII> road[4002];

int fox_dist[4002];
int wolf_dist[4002][2];

void calculate_fox_case() {
    std::fill(fox_dist + 1, fox_dist + N + 1, INF);
    fox_dist[1] = 0;
    std::priority_queue<PII> pq;
    pq.push({0, 1});
    while (!pq.empty()) {
        int cur = pq.top().second;
        int d = -pq.top().first;
        pq.pop();

        if (d > fox_dist[cur]) {
            continue;
        }

        for (auto p : road[cur]) {
            if (d + p.second * 2 < fox_dist[p.first]) {
                fox_dist[p.first] = d + p.second * 2;
                pq.push({-(d + p.second * 2), p.first});
            }
        }
    }
}

void calculate_wolf_case() {
    for (int i = 1; i < N + 1; i++) {
        wolf_dist[i][0] = INF;
        wolf_dist[i][1] = INF;
    }

    std::priority_queue<std::pair<PII, bool>> pq; // true - passed with X2 speed
    pq.push({{0, 1}, false});
    while (!pq.empty()) {
        int cur = pq.top().first.second;
        int d = -pq.top().first.first;
        bool doubled = pq.top().second;
        pq.pop();

        for (auto p : road[cur]) {
            if (doubled) {
                if (d + p.second * 4 < wolf_dist[p.first][0]) {
                    wolf_dist[p.first][0] = d + p.second * 4;
                    pq.push({{-(d + p.second * 4), p.first}, !doubled});
                }
            } else {
                if (d + p.second < wolf_dist[p.first][1]) {
                    wolf_dist[p.first][1] = d + p.second;
                    pq.push({{-(d + p.second), p.first}, !doubled});
                }
            }
        }
    }
}

int main() {
    std::cin >> N >> M;

    for (int i = 0; i < M; i++) {
        std::cin >> A >> B >> D;
        road[A].push_back({B, D});
        road[B].push_back({A, D});
    }

    calculate_fox_case();
    calculate_wolf_case();

    int ans = 0;
    for (int i = 2; i < N + 1; i++) {
        if (fox_dist[i] < std::min(wolf_dist[i][0], wolf_dist[i][1])) {
            ans++;
        }
    }

    std::cout << ans << "\n";

    return 0;
}
