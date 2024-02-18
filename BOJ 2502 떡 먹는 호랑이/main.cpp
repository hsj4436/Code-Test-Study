#include <iostream>

int arr[31];

int main() {
    int D, K;
    std::cin >> D >> K;

    for (int A = 1; A < K; A++) {
        int left = A, right = K;
        arr[1] = A;
        while (left <= right) {
            int B = (left + right) / 2;
            arr[2] = B;
            for (int i = 3; i < D + 1; i++) {
                arr[i] = arr[i - 1] + arr[i - 2];
            }
            if (arr[D] == K) {
                std::cout << A << "\n" << B << "\n";
                return 0;
            } else if (arr[D] > K) {
                right = B - 1;
            } else {
                left = B + 1;
            }
        }
    }
    return 0;
}
