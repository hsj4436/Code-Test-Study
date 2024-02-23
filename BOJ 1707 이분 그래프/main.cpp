#include <iostream>
#include <vector>

int K;
int V, E;
std::vector<int> edges[20001];
bool visited[20001];
int group[20001];

bool dfs(int cur, int cur_group) {
    for (int next : edges[cur]) {
        if (visited[next]) {
            if (group[next] == cur_group) {
                return false;
            }
            continue;
        }

        visited[next] = true;
        group[next] = cur_group == 1 ? 2 : 1;
        if (!dfs(next, group[next])) {
            return false;
        }
    }

    return true;
}

int main() {
    std::cin >> K;

    for (int tc = 0; tc < K; tc++) {
        std::cin >> V >> E;

        int u, v;
        for (int i = 0; i < E; i++) {
            std::cin >> u >> v;
            edges[u].push_back(v);
            edges[v].push_back(u);
        }

        bool possible = true;
        for (int i = 1; i < V + 1; i++) {
            if (!possible) {
                break;
            }
            if (!visited[i]) {
                visited[i] = true;
                group[i] = 1;
                if (!dfs(i, 1)) {
                    possible = false;
                    std::cout << "NO\n";
                }
            }
        }

        if (possible) {
            std::cout << "YES\n";
        }

        std::fill(visited, visited + V + 1, false);
        std::fill(group, group + V + 1, 0);
        for (int i = 1; i < V + 1; i++) {
            edges[i].clear();
        }
    }

    return 0;
}