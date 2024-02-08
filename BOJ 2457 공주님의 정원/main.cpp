#include <iostream>
#include <vector>
#include <algorithm>

#define PII std::pair<int, int>

int N;
std::vector<PII> v;

int day_calculation(int m, int d) {
    int days = 0;
    for (int i = 1; i < m; i++) {
        if (i == 1 || i == 3 || i == 5 || i == 7 || i == 8 || i == 10 || i == 12) {
            days += 31;
        } else if (i == 4 || i == 6 || i == 9 || i == 11) {
            days += 30;
        } else {
            days += 28;
        }
    }

    return days + d;
}

int S = day_calculation(3, 1);
int E = day_calculation(11, 30);

int main() {
    std::cin >> N;

    int m1, d1, m2, d2;
    for (int i = 0; i < N; i++) {
        std::cin >> m1 >> d1 >> m2 >> d2;
        int start = day_calculation(m1, d1);
        int end = day_calculation(m2, d2);
        if (end + 1 < S || start > E) {
            continue;
        }
        v.push_back({start, end});
    }

    std::sort(v.begin(), v.end(), [&](PII a, PII b) {
        if (a.first == b.first) {
            return a.second > b.second;
        } else {
            return a.first < b.first;
        }
    });

    int cnt = 0;
    int index = 0, end = 0;
    while (S < E + 1) {
        bool bloomed = false;
        for (int i = index; i < v.size(); i++) {
            if (v[i].first > S) {
                break;
            }

            if (end < v[i].second) {
                end = v[i].second;
                index = i + 1;
                bloomed = true;
            }
        }

        if (bloomed) {
            S = end;
            cnt++;
        } else {
            break;
        }
    }

    if (max > E) {
        std::cout << cnt << "\n";
    } else {
        std::cout << "0\n";
    }

    return 0;
}
