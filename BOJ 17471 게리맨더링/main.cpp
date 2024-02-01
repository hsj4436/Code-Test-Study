#include <iostream>
#include <vector>
#include <cstring>

#define INF 987654321

int N;
int population[11];
bool graph[11][11];
bool visited[11];
bool selected[11];
int min_diff = INF;

bool dfs(int cur, int end, bool is_selected) {
    if (cur == end) {
        return true;
    }
    for (int i = 1; i < N + 1; i++) {
        if (!graph[cur][i]) {
            continue;
        }
        if (visited[i]) {
            continue;
        }
        if (selected[i] != is_selected) {
            continue;
        }
        visited[i] = true;
        if (dfs(i, end, is_selected)) {
            return true;
        }
    }
    return false;
}

void combination(int index) {
    bool is_separated = true;
    for (int i = 1; i < N + 1; i++) {
        for (int j = 1; j < N + 1; j++) {
            if (i == j) {
                continue;
            }
            if (selected[i] == selected[j]) {
                std::memset(visited, false, sizeof(visited));
                visited[i] = true;
                if (!dfs(i, j, selected[i])) {
                    is_separated = false;
                    break;
                }
            }
        }
        if (!is_separated) {
            break;
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