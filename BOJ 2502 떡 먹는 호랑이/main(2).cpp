#include <iostream>

int As[31];
int Bs[31];

int main() {
    int D, K;
    std::cin >> D >> K;

    As[1] = 1, As[2] = 0;
    Bs[1] = 0, Bs[2] = 1;
    for (int i = 3; i < D + 1; i++) {
        As[i] = As[i - 1] + As[i - 2];
        Bs[i] = Bs[i - 1] + Bs[i - 2];
    }

    for (int i = 1; i < K; i++) {
        if ((K - i * As[D]) % Bs[D] == 0) {
            std::cout << i << "\n" << (K - i * As[D]) / Bs[D] << "\n";
            return 0;
        }
    }

    return 0;
}
