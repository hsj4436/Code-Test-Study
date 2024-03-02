#include <iostream>
#include <queue>

#define PII std::pair<int, int>

struct cmp {
    bool operator() (PII a, PII b) {
        if (a.first == b.first) {
            return a.second > b.second;
        } else {
            return a.first > b.first;
        }
    }
};

int N, L;

int main() {
    std::cin.tie(NULL);
    std::ios::sync_with_stdio(false);

    std::cin >> N >> L;
    std::priority_queue<PII, std::vector<PII>, cmp> pq;
    int n;
    for (int i = 0; i < N; i++) {
        std::cin >> n;
        pq.push({n, i});
        while (pq.top().second < std::max(0, i - L + 1) || pq.top().second > i) {
            pq.pop();
        }
        std::cout << pq.top().first << " ";
    }

    return 0;
}