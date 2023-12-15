#include <iostream>
#include <queue>
#include <cstring>

int T;
int A, B;
bool used[10001];

char command[4] = {'D', 'S',  'L', 'R'};

std::string bfs() {
    std::memset(used, false, sizeof(used));
    std::queue<std::pair<int, std::string>> trace;
    used[A] = true;
    trace.push({A, ""});

    while (!trace.empty()) {
        auto p = trace.front();
        trace.pop();

        if (p.first == B) {
            return p.second;
        }


        for (int i = 0; i < 4; i++) {
            if (command[i] == 'D') {
                if (used[(2 * p.first) % 10000]) {
                    continue;
                }
                std::string c = p.second;
                c.push_back('D');
                used[(2 * p.first) % 10000] = true;
                trace.push({(2 * p.first) % 10000, c});
            } else if (command[i] == 'S') {
                std::string c = p.second;
                c.push_back('S');
                if (p.first == 0) {
                    if (used[9999]) {
                        continue;
                    }
                    used[9999] = true;
                    trace.push({9999, c});
                } else {
                    if (used[p.first - 1]) {
                        continue;
                    }
                    used[p.first - 1] = true;
                    trace.push({p.first - 1, c});
                }
            } else if (command[i] == 'L') {
                int d1 = p.first / 1000;
                std::string c = p.second;
                c.push_back('L');
                if (d1 == 0) {
                    if (used[p.first * 10]) {
                        continue;
                    }
                    used[p.first * 10] = true;
                    trace.push({p.first * 10, c});
                } else {
                    if (used[(p.first % 1000) * 10 + d1]) {
                        continue;
                    }
                    used[(p.first % 1000) * 10 + d1] = true;
                    trace.push({(p.first % 1000) * 10 + d1, c});
                }
            } else {
                int d4 = p.first % 10;
                std::string c = p.second;
                c.push_back('R');
                if (d4 == 0) {
                    if (used[p.first / 10]) {
                        continue;
                    }
                    used[p.first / 10] = true;
                    trace.push({p.first / 10, c});
                } else {
                    if (used[(p.first / 10) + d4 * 1000]) {
                        continue;
                    }
                    used[(p.first / 10) + d4 * 1000] = true;
                    trace.push({(p.first / 10) + d4 * 1000, c});
                }
            }
        }
    }
}

int main() {
    std::cin >> T;

    for (int i = 0; i < T; i++) {
        std::cin >> A >> B;
        std::cout << bfs() << "\n";
    }

    return 0;
}