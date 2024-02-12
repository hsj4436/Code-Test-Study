#include <iostream>

int N, M, D;
int **arr;
int **dp;

int main() {
    std::cin >> N >> M >> D;

    arr = new int*[N];
    dp = new int*[N];
    for (int i = 0; i < N; i++) {
        arr[i] = new int[M];
        for (int j = 0; j < M; j++) {
            std::cin >> arr[i][j];
        }
        dp[i] = new int[M];
    }

    for (int i = 0; i < N; i++) {
        if (i == 0) {
            for (int j = 0; j < M; j++) {
                dp[i][j] = 0;
            }
        } else {
            for (int j = 0; j < M; j++) {
                dp[i][j] = -2100000000;
            }
        }
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            for (int ii = i + 1; ii < std::min(N, i + D + 1); ii++) {
                int last_distance = D - (ii - i);
                for (int jj = std::max(0, j - last_distance); jj < std::min(M, j + last_distance + 1); jj++) {
                    dp[ii][jj] = std::max(dp[ii][jj], dp[i][j] + arr[i][j] * arr[ii][jj]);
                }
            }
        }
    }

    int answer = -2100000000;
    for (int i = 0; i < M; i++) {
        answer = std::max(answer, dp[N - 1][i]);
    }

    std::cout << answer << "\n";

    return 0;
}
