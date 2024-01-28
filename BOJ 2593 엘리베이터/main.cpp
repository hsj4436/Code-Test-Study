#include <iostream>
#include <vector>
#include <queue>

#define INF 987654321

int N, M;
int X, Y;
int A, B;
int dist[1000102];
int parent[1000102];
std::vector<int> edges[1000102];

int main() {
    std::cin >> N >> M;

    for (int i = 1; i < M + 1; i++) {
        std::cin >> X >> Y;
        for (int j = X; j < N + 1; j += Y) {
            edges[j].push_back(i + 1000000);
            edges[i + 1000000].push_back(j);
        }
    }

    std::cin >> A >> B;

    std::fill(dist, dist + 1000102, INF);
    std::fill(parent, parent + 1000102, -1);

    std::queue<int> q;
    q.push(B);
    dist[B] = 0;

    while (!q.empty()) {
        int cur = q.front();
        q.pop();

        for (auto next : edges[cur]) {
            if (dist[next] == INF) {
                dist[next] = dist[cur] + 1;
                parent[next] = cur;
                q.push(next);
            }
        }
    }

    if (dist[A] == INF) {
        std::cout << "-1\n";
    } else {
        std::cout << dist[A] / 2 << "\n";
        for (int i = parent[A]; i >= 0; i = parent[parent[i]]) {
            std::cout << i - 1000000 << "\n";
        }
    }

    return 0;
}
