#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>

struct bus {
    int index;
    int start;
    int end;
    bus() {}
    bus(int index, int start, int end) : index(index), start(start), end(end) {}
};

int N, M;
std::vector<bus> vec;
bool alive[500001];

int main() {
    std::cin >> N >> M;

    int a, b;
    for (int i = 1; i < M + 1; i++) {
        std::cin >> a >> b;
        if (a > b) {
            vec.push_back(bus(i, a, b + N));
        } else {
            vec.push_back(bus(i, a, b));
            vec.push_back(bus(i, a + N, b + N));
        }
    }

    std::sort(vec.begin(), vec.end(), [&](bus a, bus b) {
        if (a.start == b.start) {
            return a.end > b.end;
        } else {
            return a.start < b.start;
        }
    });

    std::memset(alive, true, sizeof(alive));

    int left = 0, right = 0;
    for (bus current : vec) {
        if (!alive[current.index]) {
            continue;
        }
        if (left <= current.start && current.end <= right) {
            alive[current.index] = false;
            continue;
        }
        left = current.start;
        right = current.end;
    }

    for (int i = 1; i < M + 1; i++) {
        if (alive[i]) {
            std::cout << i << " ";
        }
    }

    return 0;
}
