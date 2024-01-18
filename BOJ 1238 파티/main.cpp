#include <iostream>
#include <queue>
#include <vector>

int N, M, X;
std::vector<std::pair<int, int>> edges[1001];
int dist[1001][1001];

void dijkstra(int start) {
    dist[start][start] = 0;
    std::priority_queue<std::pair<int, int>> pq;
    pq.push({0, start});

    while (!pq.empty()) {
        int v = pq.top().second;
        int d = -pq.top().first;
        pq.pop();

        for (auto p : edges[v]) {
            if (d + p.second < dist[start][p.first]) {
                dist[start][p.first] = d + p.second;
                pq.push({-(d + p.second), p.first});
            }
        }
    }
}

int main() {
    std::cin >> N >> M >> X;

    for (int i = 1; i < N + 1; i++) {
        for (int j = 1; j < N + 1; j++) {
            dist[i][j] = 987654321;
        }
    }

    for (int i = 0; i < M; i++) {
        int start, end, cost;
        std::cin >> start >> end >> cost;
        edges[start].push_back({end, cost});
    }

    for (int i = 1; i < N + 1; i++) {
        dijkstra(i);
    }

    int max_cost = 0;
    for (int i = 1; i < N + 1; i++) {
        max_cost = std::max(max_cost, dist[i][X] + dist[X][i]);
    }

    std::cout << max_cost << "\n";
    
    return 0;
}
