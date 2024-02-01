#include <iostream>
#include <vector>
#include <queue>
#include <cstring>

#define INF 987654321

int N;
int population[11];
bool graph[11][11];
bool visited[11];
bool selected[11];
int min_diff = INF;

bool bfs(std::vector<int> v, bool is_selected) {
    std::memset(visited, false, sizeof(visited));
    std::queue<int> q;
    q.push(v[0]);
    visited[v[0]] = true;
    int cnt = 1;

    while (!q.empty()) {
        int cur = q.front();
        q.pop();

        for (int i = 1; i < N + 1; i++) {
            if (graph[cur][i] && selected[i] == is_selected && !visited[i]) {
                visited[i] = true;
                q.push(i);
                cnt++;
            }
        }
    }

    if (v.size() == cnt) {
        return true;
    } else {
        return false;
    }
}

void combination(int index) {
    bool is_separated = true;
    std::vector<int> A, B;
    for (int i = 1; i < N + 1; i++) {
        if (selected[i]) {
            A.push_back(i);
        } else {
            B.push_back(i);
        }
    }

    if (A.empty() || B.empty()) {
        is_separated = false;
    } else {
        if (!bfs(A, true)) {
            is_separated = false;
        } else if (!bfs(B, false)) {
            is_separated = false;
        }
    }

    if (is_separated) {
        int sum1 = 0, sum2 = 0;
        for (int i = 1; i < N + 1; i++) {
            if (selected[i]) {
                sum1 += population[i];
            } else {
                sum2 += population[i];
            }
        }
        if (sum1 != 0 && sum2 != 0) {
            min_diff = std::min(min_diff, std::abs(sum1 - sum2));
        }
    }

    if (index == N + 1) {
        return;
    }

    selected[index] = true;
    combination(index + 1);
    selected[index] = false;
    combination(index + 1);
}

int main() {
    std::cin >> N;

    for (int i = 1; i < N + 1; i++) {
        std::cin >> population[i];
    }

    int isolated_areas = 0;
    int areas, area;
    for (int i = 1; i < N + 1; i++) {
        std::cin >> areas;
        if (areas == 0) {
            isolated_areas++;
        }
        for (int j = 0; j < areas; j++) {
            std::cin >> area;
            graph[i][area] = true;
            graph[area][i] = true;
        }
    }

    if (N > 2 && isolated_areas > 1) {
        std::cout << "-1\n";
        return 0;
    }

    combination(1);

    if (min_diff == INF) {
        std::cout << "-1\n";
    } else {
        std::cout << min_diff << "\n";
    }

    return 0;
}