#include <iostream>
#include <vector>

int N;
std::vector<int> ports;
std::vector<int> LIS;

int main() {
    std::cin >> N;

    int port;
    for (int i = 0; i < N; i++) {
        std::cin >> port;
        ports.push_back(port);
    }

    LIS.push_back(ports[0]);

    for (int i = 1; i < N; i++) {
        if (LIS.back() < ports[i]) {
            LIS.push_back(ports[i]);
        } else {
            int left = 0, right = LIS.size() - 1;
            while (left < right) {
                int mid = (left + right) / 2;
                if (LIS[mid] < ports[i]) {
                    left = mid + 1;
                } else {
                    right = mid;
                }
            }
            LIS[right] = ports[i];
        }
    }

    std::cout << LIS.size() << "\n";

    return 0;
}
