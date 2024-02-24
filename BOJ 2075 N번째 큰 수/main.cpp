#include <iostream>
#include <queue>

int N;

int main() {
    std::cin.tie(NULL);
    std::ios::sync_with_stdio(false);

    std::cin >> N;

    std::priority_queue<int, std::vector<int>, std::greater<int>> pq;
    int num;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            std::cin >> num;
            if (pq.size() < N) {
                pq.push(num);
            } else if (pq.top() < num) {
                pq.pop();
                pq.push(num);
            }
        }
    }

    std::cout << pq.top() << "\n";

    return 0;
}