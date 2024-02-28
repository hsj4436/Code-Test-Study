#include <iostream>
#include <vector>
#include <algorithm>

#define LL long long

LL N;
std::vector<LL> minus;
std::vector<LL> plus;

int main() {
    std::cin >> N;

    LL n;
    for (int i = 0; i < N; i++) {
        std::cin >> n;
        if (n <= 0) {
            minus.push_back(n);
        } else {
            plus.push_back(n);
        }
    }

    std::sort(minus.begin(), minus.end());
    std::sort(plus.begin(), plus.end());

    LL answer = 0;
    if (minus.size() % 2 == 0) {
        for (int i = 0; i < minus.size(); i += 2) {
            answer += minus[i] * minus[i + 1];
        }
    } else {
        for (int i = 0; i < minus.size() - 1; i += 2) {
            answer += minus[i] * minus[i + 1];
        }
    }
    if (plus.size() % 2 == 0) {
        for (int i = plus.size() - 1; i > -1; i -= 2) {
            if (plus[i] * plus[i - 1] > plus[i] + plus[i - 1]) {
                answer += plus[i] * plus[i - 1];
            } else {
                answer += plus[i] + plus[i - 1];
            }
        }
        if (minus.size() % 2 != 0) {
            answer += minus[minus.size() - 1];
        }
    } else {
        for (int i = plus.size() - 1; i > 0; i -= 2) {
            if (plus[i] * plus[i - 1] > plus[i] + plus[i - 1]) {
                answer += plus[i] * plus[i - 1];
            } else {
                answer += plus[i] + plus[i - 1];
            }
        }
        if (minus.size() % 2 != 0) {
            if (minus[minus.size() - 1] * plus[0] > minus[minus.size() - 1] + plus[0]) {
                answer += minus[minus.size() - 1] * plus[0];
            } else {
                answer += minus[minus.size() - 1] + plus[0];
            }
        } else {
            answer += plus[0];
        }
    }

    std::cout << answer << "\n";

    return 0;
}