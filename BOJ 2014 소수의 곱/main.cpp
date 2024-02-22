#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>

#define LL long long

int K, N;
std::vector<LL> v;
std::map<LL, bool> m;

int main() {
    std::cin >> K >> N;

    LL k;
    std::priority_queue<LL, std::vector<LL>, std::greater<LL>> pq;
    LL max_value = 0;
    for (int i = 0; i < K; i++) {
        std::cin >> k;
        v.push_back(k);
        pq.push(k);
        max_value = std::max(max_value, k);
        m[k] = true;
    }

    std::sort(v.begin(), v.end());

    int popped = 0;
    LL last_popped = 0;
    while (true) {
        LL smallest = pq.top();
        last_popped = smallest;
        pq.pop();
        popped++;

        for (int i = 0; i < K; i++) {
            LL next_value = smallest * v[i];

            if (next_value >= max_value && pq.size() + popped + 1 > N) {
                continue;
            }

            if (m[next_value]) {
                continue;
            }
            max_value = std::max(max_value, next_value);
            m[next_value] = true;
            pq.push(next_value);
        }
        if (popped == N) {
            break;
        }
    }

    std::cout << last_popped;

    return 0;
}
