#include <iostream>
#include <vector>

#define LL long long
#define PLL std::pair<LL, LL>

LL dx[4] = {0, 1, 0, -1};
LL dy[4] = {1, 0, -1, 0};

LL L, N;
LL direction = 0;
std::vector<PLL > commands;
std::vector<std::pair<PLL, PLL>> vertical;
std::vector<std::pair<PLL, PLL>> horizon;
PLL head;
PLL tail;

int check_cross() {
    LL distance = 2000000099;
    for (auto pp : vertical) {
        if (direction == 0 || direction == 2) {
            // tail - head는 가로, 비교 대상은 세로
            if (tail > head) {
                if (head.second <= pp.first.second && pp.first.second < tail.second) {
                    if (pp.first.first <= tail.first && tail.first <= pp.second.first) {
                        distance = std::min(distance, std::abs(pp.first.second - tail.second));
                    }
                }
            } else {
                if (tail.second < pp.first.second && pp.first.second <= head.second) {
                    if (pp.first.first <= tail.first && tail.first <= pp.second.first) {
                        distance = std::min(distance, std::abs(pp.first.second - tail.second));
                    }
                }
            }
        } else {
            // 둘 다 세로
            if (tail.second == pp.first.second) {
                if (tail > head) {
                    if (tail.first > pp.second.first && head.first <= pp.second.first) {
                        distance = std::min(distance, std::abs(pp.second.first - tail.first));
                    }
                } else {
                    if (tail.first < pp.first.first && head.first > pp.first.first) {
                        distance = std::min(distance, std::abs(pp.first.first - tail.first));
                    }
                }
            }
        }
    }
    for (auto pp : horizon) {
        if (direction == 0 || direction == 2) {
            // 둘 다 가로
            if (tail.first == pp.first.first) {
                if (tail > head) {
                    if (tail.second > pp.second.second && head.second <= pp.second.second) {
                        distance = std::min(distance, std::abs(pp.second.second - tail.second));
                    }
                } else {
                    if (tail.second < pp.first.second && head.second >= pp.first.second) {
                        distance = std::min(distance, std::abs(pp.first.second - tail.second));
                    }
                }
            }
        } else {
            // tail - head는 세로, 비교 대상은 가로
            if (tail > head) {
                if (pp.first.second <= tail.second && tail.second <= pp.second.second) {
                    if (head.first <= pp.first.first && pp.first.first < tail.first) {
                        distance = std::min(distance, std::abs(pp.first.first - tail.first));
                    }
                }
            } else {
                if (pp.first.second <= tail.second && tail.second <= pp.second.second) {
                    if (tail.first < pp.first.first && pp.first.first <= head.first) {
                        distance = std::min(distance, std::abs(pp.first.first - tail.first));
                    }
                }
            }
        }
    }

    if (distance == 2000000099) {
        return -1;
    }

    return distance;
}

int main() {
    std::cin.tie(NULL);
    std::ios::sync_with_stdio(false);

    std::cin >> L >> N;

    vertical.push_back({{-L, -L - 1},
                        {L,  -L - 1}});
    vertical.push_back({{-L, L + 1},
                        {L,  L + 1}});
    horizon.push_back({{-L - 1, -L},
                       {-L - 1, L}});
    horizon.push_back({{L + 1, -L},
                       {L + 1, L}});

    LL T = 0;
    LL t;
    char dir;
    for (LL i = 0; i < N; i++) {
        std::cin >> t >> dir;
        T += t;
        if (dir == 'L') {
            commands.push_back({T, -1});
        } else {
            commands.push_back({T, 1});
        }
    }

    T = 0;
    tail = {0, 0};
    head = {0, 0};
    bool boom = false;
    for (int i = 0; i < N; i++) {
        LL next_T = commands[i].first;
        LL nx = head.first + dx[direction] * (next_T - T);
        LL ny = head.second + dy[direction] * (next_T - T);

        head = {nx, ny};

        LL distance = check_cross();
        if (distance == -1) {
            T = next_T;
        } else {
            T += distance;
            boom = true;
            break;
        }

        if (direction == 0 || direction == 2) {
            if (tail > head) {
                horizon.push_back({head, tail});
            } else {
                horizon.push_back({tail, head});
            }
        } else {
            if (tail > head) {
                vertical.push_back({head, tail});
            } else {
                vertical.push_back({tail, head});
            }
        }
        direction = (direction + commands[i].second + 4) % 4;
        tail = head;
    }

    if (!boom) {
        if (direction == 0) {
            head.second = L + 1;
        } else if (direction == 1) {
            head.first = L + 1;
        } else if (direction == 2) {
            head.second = -L - 1;
        } else {
            head.first = -L - 1;
        }
        LL distance = check_cross();
        T += distance;
    }

    std::cout << T << "\n";

    return 0;
}