#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

int N, D;
std::vector<std::pair<int, int>> vec;

int main() {
    std::cin >> N;

    int h, o;
    for (int i = 0; i < N; i++) {
        std::cin >> h >> o;
        if (h > o) {
            std::swap(h, o);
        }
        vec.push_back({h, o});
    }

    std::cin >> D;

    std::sort(vec.begin(), vec.end(), [&](std::pair<int, int> a, std::pair<int, int> b) {
        if (a.second == b.second) {
            return a.first < b.first;
        } else {
            return a.second < b.second;
        }
    });

    int answer = 0;
    std::priority_queue<int, std::vector<int>, std::greater<int>> pq;
    for (int i = 0; i < vec.size(); i++) {
        if (vec[i].second - D <= vec[i].first) {
            pq.push(vec[i].first);
        }
        while (!pq.empty()) {
            if (vec[i].second - D <= pq.top()) {
                break;
            }
            pq.pop();
        }
        answer = std::max(answer, (int)pq.size());
    }

    std::cout << answer << "\n";

    return 0;
}
