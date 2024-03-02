#include <iostream>
#include <queue>

int N;

int main() {
    std::cin.tie(NULL);
    std::ios::sync_with_stdio(false);

    std::cin >> N;

    int n;
    std::priority_queue<int> left;
    std::priority_queue<int, std::vector<int>, std::greater<int>> right;
    for (int i = 0; i < N; i++) {
        std::cin >> n;
        if (left.empty()) {
            left.push(n);
            std::cout << n << "\n";
        } else if (right.empty()) {
            if (n > left.top()) {
                right.push(n);
                std::cout << left.top() << "\n";
            } else {
                right.push(left.top());
                left.pop();
                left.push(n);
                std::cout << n << "\n";
            }
        } else {
            if (n <= left.top()) {
                if (left.size() > right.size()) {
                    right.push(left.top());
                    left.pop();
                    left.push(n);
                } else {
                    left.push(n);
                }
            } else if (n < right.top()) {
                if (left.size() > right.size()) {
                    right.push(n);
                } else {
                    left.push(n);
                }
            } else {
                if (left.size() > right.size()) {
                    right.push(n);
                } else {
                    left.push(right.top());
                    right.pop();
                    right.push(n);
                }
            }
            std::cout << left.top() << "\n";
        }
    }
    return 0;
}