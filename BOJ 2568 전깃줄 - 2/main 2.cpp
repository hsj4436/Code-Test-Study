#include <iostream>
#include <algorithm>
#include <vector>

#define PII std::pair<int, int>

int N;
PII pairs[100001];

int main() {
    std::cin >> N;

    for (int i = 0; i < N; i++) {
        std::cin >> pairs[i].first >> pairs[i].second;
    }

    std::sort(pairs, pairs + N, [&](PII a, PII b) {
        return a.second < b.second;
    });

    std::vector<int> LIS;
    std::vector<int> order;
    for (int i = 0; i < N; i++) {
        if (LIS.empty() || LIS.back() < pairs[i].first) {
            LIS.push_back(pairs[i].first);
            order.push_back(LIS.size() - 1);
        } else {
            auto it = std::lower_bound(LIS.begin(), LIS.end(), pairs[i].first);
            *it = pairs[i].first;
            order.push_back(it - LIS.begin());
        }
    }

    std::cout << N - LIS.size() << "\n";

    std::vector<int> answer;
    int index = LIS.size() - 1;
    for (int i = order.size() - 1; i > -1; i--) {
        if (order[i] == index) {
            index--;
        } else {
            answer.push_back(pairs[i].first);
        }
    }

    std::sort(answer.begin(), answer.end());

    for (auto i : answer) {
        std::cout << i << "\n";
    }

    return 0;
}