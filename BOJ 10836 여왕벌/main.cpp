#include <iostream>

int M, N;
int inputs[1402];
int growth[701][701];

int main() {
    std::cin.tie(NULL);
    std::ios::sync_with_stdio(false);

    std::cin >> M >> N;

    int zeros, ones, twos;
    for (int i = 0; i < N; i++) {
        std::cin >> zeros >> ones >> twos;
        int index = 2 * M - 2;
        for (int j = 0; j < twos; j++) {
            inputs[index] += 2;
            index--;
        }
        for (int j = 0; j < ones; j++) {
            inputs[index] += 1;
            index--;
        }
    }
    for (int i = 2 * M - 2; i > M - 2; i--) {
        growth[0][i - M + 1] = inputs[i];
    }
    for (int i = M - 2; i > -1; i--) {
        growth[M - 1 - i][0] = inputs[i];
    }
    for (int i = 0; i < M; i++) {
        std::cout << growth[0][i] + 1 << " ";
    }
    std::cout << "\n";
    for (int i = 1; i < M; i++) {
        std::cout << growth[i][0] + 1 << " ";
        for (int j = 1; j < M; j++) {
            int max_growth = std::max(growth[i - 1][j - 1], std::max(growth[i - 1][j], growth[i][j - 1]));
            growth[i][j] = max_growth;
            std::cout << growth[i][j] + 1 << " ";
        }
        std::cout << "\n";
    }

    return 0;
}
