#include <iostream>
#include <queue>
#include <vector>
#include <cstring>

#define PII std::pair<int, int>

int N, K;
std::vector<PII> bridges[1000];
bool visited[1000];
int max_cost = 0;
int max_vertex = 0;
int parents[1000];
std::priority_queue<std::pair<int, PII>> pq;

int find_parent(int x) {
    if (parents[x] == x) {
        return x;
    } else {
        return parents[x] = find_parent(parents[x]);
    }
}

void dfs(int cur, int dist) {
    if (dist > max_cost) {
        max_cost = dist;
        max_vertex = cur;
    }
    for (PII p : bridges[cur]) {
        if (visited[p.first]) {
            continue;
        }
        visited[p.first] = true;
        dfs(p.first, dist + p.second);
    }
}

int main() {
    std::cin >> N >> K;

    for (int i = 0; i < N; i++) {
        parents[i] = i;
    }

    int a, b, c;
    for (int i = 0; i < K; i++) {
        std::cin >> a >> b >> c;
        pq.push({-c, {a, b}});
    }

    int cnt = 0;
    int min_cost = 0;
    while (cnt != N - 1) {
        a = pq.top().second.first;
        b = pq.top().second.second;
        c = -pq.top().first;
        pq.pop();

        int pa = find_parent(a);
        int pb = find_parent(b);
        if (pa == pb) {
            continue;
        }
        bridges[a].push_back({b, c});
        bridges[b].push_back({a, c});
        min_cost += c;
        if (pa < pb) {
            parents[pb] = pa;
        } else {
            parents[pa] = pb;
        }
        cnt++;
    }

    visited[0] = true;
    dfs(0, 0);
    std::memset(visited, false, sizeof(visited));
    dfs(max_vertex, 0);
    std::cout << min_cost << "\n" << max_cost << "\n";

    return 0;
}