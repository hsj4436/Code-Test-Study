#include <iostream>
#include <vector>
#include <queue>

#define INF 10000001
#define PII std::pair<int, int>

int N, M, K;
int A, B, C;
std::vector<PII> roads[1001];
std::priority_queue<int> shortest_path[1001];

int main() {
    std::cin >> N >> M >> K;

    for (int i = 0; i < M; i++) {
        std::cin >> A >> B >> C;
        roads[A].push_back({B, C});
    }

    shortest_path[1].push(0);

    std::priority_queue<PII> pq;
    pq.push({0, 1});

    while (!pq.empty()) {
        int current = pq.top().second;
        int cost = -pq.top().first;
        pq.pop();

        for (PII next : roads[current]) {
            if (shortest_path[next.first].size() < K) {
                shortest_path[next.first].push(cost + next.second);
                pq.push({-(cost + next.second), next.first});
            } else if (cost + next.second < shortest_path[next.first].top()) {
                shortest_path[next.first].pop();
                shortest_path[next.first].push(cost + next.second);
                pq.push({-(cost + next.second), next.first});
            }
        }
    }

    for (int i = 1; i < N + 1; i++) {
        if (shortest_path[i].size() == K) {
            std::cout << shortest_path[i].top() << "\n";
        } else {
            std::cout << "-1\n";
        }
    }

    return 0;
}