#include <iostream>

int N, M;
bool has_road[201][201];
int travel[1001];

int main() {
    std::cin >> N >> M;

    int cell;
    for (int i = 1; i < N + 1; i++) {
        for (int j = 1; j < N + 1; j++) {
            std::cin >> cell;
            if (cell == 1) {
                has_road[i][j] = true;
            }
            if (i == j) {
                has_road[i][j] = true;
            }
        }
    }

    for (int k = 1; k < N + 1; k++) {
        for (int i = 1; i < N + 1; i++) {
            if (i == k) {
                continue;
            }
            for (int j = 1; j < N + 1; j++) {
                if (i == j || j == k) {
                    continue;
                }
                if (has_road[i][j] || (has_road[i][k] && has_road[k][j])) {
                    has_road[i][j] = true;
                }
            }
        }
    }

    for (int i = 0; i < M; i++) {
        std::cin >> travel[i];
    }

    for (int i = 1; i < M; i++) {
        if (!has_road[travel[i - 1]][travel[i]]) {
            std::cout << "NO\n";
            return 0;
        }
    }
    std::cout << "YES\n";

    return 0;
}