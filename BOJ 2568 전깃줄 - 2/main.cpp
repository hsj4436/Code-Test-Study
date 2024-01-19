#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

int N;
std::vector<std::pair<int, int>> vec;
std::vector<int> LIS, idx;

int main() {
    std::cin >> N;

    int a, b;
    for (int i = 0; i < N; i++) {
        std::cin >> a >> b;
        vec.push_back({a, b});
    }

    std::sort(vec.begin(), vec.end());

    LIS.push_back(vec.front().second);
    idx.push_back(0);

    for (int i = 1; i < N; i++) {
        if (LIS.back() < vec[i].second) {
            LIS.push_back(vec[i].second);
            idx.push_back(LIS.size() - 1);
        } else {
            auto it = std::lower_bound(LIS.begin(), LIS.end(), vec[i].second);
            *it = vec[i].second;
            idx.push_back(it - LIS.begin());
        }
    }

    std::cout << N - LIS.size() << "\n";

    int cur = LIS.size() - 1;
    std::vector<int> ans;
    for (int i = idx.size() - 1; i >= 0; i--) {
        if (cur == idx[i]) {
            cur--;
        } else {
            ans.push_back(vec[i].first);
        }
    }

    std::sort(ans.begin(), ans.end());
    for (int i : ans) {
        std::cout << i << "\n";
    }

    return 0;
}
