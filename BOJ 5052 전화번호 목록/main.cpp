#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

int T, N;
std::map<int, std::vector<std::string>> phone_numbers;

int main() {
    std::cin.tie(NULL);
    std::ios::sync_with_stdio(false);

    std::cin >> T;

    for (int tc = 0; tc < T; tc++) {
        std::cin >> N;

        std::string phone_number;
        for (int i = 0; i < N; i++) {
            std::cin >> phone_number;
            phone_numbers[phone_number[0] - '0'].push_back(phone_number);
        }

        bool is_right = true;
        for (auto p: phone_numbers) {
            std::sort(p.second.begin(), p.second.end());
            for (int i = 0; i < p.second.size(); i++) {
                for (int j = i + 1; j < p.second.size(); j++) {
                    if (p.second[j].substr(0, p.second[i].size()) == p.second[i]) {
                        is_right = false;
                        break;
                    }
                }
                if (!is_right) {
                    break;
                }
            }
            if (!is_right) {
                break;
            }
        }
        if (is_right) {
            std::cout << "YES\n";
        } else {
            std::cout << "NO\n";
        }

        phone_numbers.clear();
    }
    return 0;
}
