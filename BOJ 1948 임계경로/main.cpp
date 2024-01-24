#include <iostream>
#include <queue>
#include <vector>

#define PII std::pair<int, int>

int N, M;
int S, E;
int in_degree[10001];
int times[10001];
std::vector<PII> graph[10001];
std::vector<PII> rev_graph[10001];


int main() {
    std::cin >> N >> M;

    int from, to, cost;
    for (int i = 0; i < M; i++) {
        std::cin >> from >> to >> cost;
        in_degree[to]++;
        graph[from].push_back({to, cost});
        rev_graph[to].push_back({from, cost});
    }

    std::cin >> S >> E;

    std::queue<int> q;
    q.push(S);

    while (!q.empty()) {
        int cur = q.front();
        q.pop();

        for (PII p : graph[cur]) {
            int next = p.first;
            int c = p.second;

            in_degree[next]--;
            times[next] = std::max(times[next], times[cur] + c);
            if (in_degree[next] == 0) {
                q.push(next);
            }
        }
    }

    std::cout << times[E] << "\n";

    q.push(E);
    in_degree[E] = 1;
    int cnt = 0;
    while (!q.empty()) {
        int cur = q.front();
        q.pop();

        if (cur == S) {
            break;
        }

        for (PII p : rev_graph[cur]) {
            int next = p.first;
            int c = p.second;

            if (times[cur] - c == times[next]) {
                cnt++;
                if (in_degree[next] == 0) {
                    in_degree[next] = 1;
                    q.push(next);
                }
            }
        }
    }

    std::cout << cnt << "\n";

    return 0;
}