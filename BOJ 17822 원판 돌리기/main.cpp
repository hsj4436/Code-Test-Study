#include <iostream>
#include <vector>

#define INF -99999

int N, M, T;
int circle[51][51];
int head[51];

int main() {
    std::cin >> N >> M >> T;

    for (int i = 1; i < N + 1; i++) {
        for (int j = 0; j < M; j++) {
            std::cin >> circle[i][j];
        }
    }

    int X, D, K;
    for (int tc = 0; tc < T; tc++) {
        if (tc == 2) {

        }
        std::cin >> X >> D >> K;
        for (int i = X; i < N + 1; i += X) {
            if (D == 0) {
                head[i] = (head[i] - K + M) % M;
            } else {
                head[i] = (head[i] + K + M) % M;
            }
        }

        std::vector<std::pair<int, int>> erase_vector;
        for (int i = 1; i < N + 1; i++) {
            if (i == 1) {
                for (int j = 0; j < M; j++) {
                    bool erased = false;
                    int center = circle[1][(head[1] + j + M) % M];
                    if (center == INF) {
                        continue;
                    }
                    int n1 = circle[1][(head[1] + j - 1 + M) % M];
                    int n2 = circle[1][(head[1] + j + 1 + M) % M];
                    int n3 = circle[2][(head[2] + j + M) % M];
                    if (n1 == center) {
                        erased = true;
                        erase_vector.push_back({1, (head[1] + j - 1 + M) % M});
                    }
                    if (n2 == center) {
                        erased = true;
                        erase_vector.push_back({1, (head[1] + j + 1 + M) % M});
                    }
                    if (n3 == center) {
                        erased = true;
                        erase_vector.push_back({2, (head[2] + j + M) % M});
                    }
                    if (erased) {
                        erase_vector.push_back({1, (head[1] + j + M) % M});
                    }
                }
            } else if (i == N) {
                for (int j = 0; j < M; j++) {
                    bool erased = false;
                    int center = circle[N][(head[N] + j + M) % M];
                    if (center == INF) {
                        continue;
                    }
                    int n1 = circle[N][(head[N] + j - 1 + M) % M];
                    int n2 = circle[N][(head[N] + j + 1 + M) % M];
                    int n3 = circle[N - 1][(head[N - 1] + j + M) % M];
                    if (center == n1) {
                        erased = true;
                        erase_vector.push_back({N, (head[N] + j - 1 + M) % M});
                    }
                    if (center == n2) {
                        erased = true;
                        erase_vector.push_back({N, (head[N] + j + 1 + M) % M});
                    }
                    if (center == n3) {
                        erased = true;
                        erase_vector.push_back({N - 1, (head[N - 1] + j + M) % M});
                    }
                    if (erased) {
                        erase_vector.push_back({N, (head[N] + j + M) % M});
                    }
                }
            } else {
                for (int j = 0; j < M; j++) {
                    bool erased = false;
                    int center = circle[i][(head[i] + j + M) % M];
                    if (center == INF) {
                        continue;
                    }
                    int n1 = circle[i][(head[i] + j - 1 + M) % M];
                    int n2 = circle[i][(head[i] + j + 1 + M) % M];
                    int n3 = circle[i - 1][(head[i - 1] + j + M) % M];
                    int n4 = circle[i + 1][(head[i + 1] + j + M) % M];
                    if (center == n1) {
                        erased = true;
                        erase_vector.push_back({i, (head[i] + j - 1 + M) % M});
                    }
                    if (center == n2) {
                        erased = true;
                        erase_vector.push_back({i, (head[i] + j + 1 + M) % M});
                    }
                    if (center == n3) {
                        erased = true;
                        erase_vector.push_back({i - 1, (head[i - 1] + j + M) % M});
                    }
                    if (center == n4) {
                        erased = true;
                        erase_vector.push_back({i + 1, (head[i + 1] + j + M) % M});
                    }
                    if (erased) {
                        erase_vector.push_back({i, (head[i] + j + M) % M});
                    }
                }
            }
        }

        if (erase_vector.empty()) {
            double average = 0;
            int count = 0;
            int sum = 0;
            for (int i = 1; i < N + 1; i++) {
                for (int j = 0; j < M; j++) {
                    if (circle[i][j] == INF) {
                        continue;
                    }
                    sum += circle[i][j];
                    count++;
                }
            }
            average = (double)sum / count;
            for (int i = 1; i < N + 1; i++) {
                for (int j = 0; j < M; j++) {
                    if (circle[i][j] == INF) {
                        continue;
                    }
                    if ((double)circle[i][j] > average) {
                        circle[i][j]--;
                    } else if ((double)circle[i][j] < average) {
                        circle[i][j]++;
                    }
                }
            }
        } else {
            for (auto p : erase_vector) {
                circle[p.first][p.second] = INF;
            }
        }
    }

    int answer = 0;
    for (int i = 1; i < N + 1; i++) {
        for (int j = 0; j < M; j++) {
            if (circle[i][j] == INF) {
                continue;
            }
            answer += circle[i][j];
        }
    }

    std::cout << answer << "\n";

    return 0;
}