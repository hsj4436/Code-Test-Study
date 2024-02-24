#include <iostream>
#include <vector>
#include <set>

#define PII std::pair<int, int>

int N;
int arr[51];

int main() {
    std::cin >> N;

    for (int i = 0; i < N; i++) {
        std::cin >> arr[i];
    }

    if (N == 1) {
        std::cout << "A\n";
        return 0;
    }

    std::vector<PII> p;
    for (int a = -10000; a < 10001; a++) {
        int b = -1000000000;
        bool possible = true;
        for (int i = 0; i < N - 1; i++) {
            if (b == -1000000000) {
                b = arr[i + 1] - arr[i] * a;
            } else {
                if (arr[i] * a + b != arr[i + 1]) {
                    possible = false;
                    break;
                }
            }
        }
        if (possible) {
            p.push_back({a, b});
        }
    }

    std::set<int> answers;
    for (PII ab : p) {
        answers.insert(arr[N - 1] * ab.first + ab.second);
    }

    if (answers.empty()) {
        std::cout << "B\n";
    } else if (answers.size() > 1) {
        std::cout << "A\n";
    } else {
        std::cout << *answers.begin() << "\n";
    }

    return 0;
}
