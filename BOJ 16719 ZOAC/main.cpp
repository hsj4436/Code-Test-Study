#include <iostream>

std::string input;
bool used[101];

int main() {
    std::cin >> input;

    int count = 0;
    while (count != input.size()) {
        std::string min_string = input;
        int min_index = 0;
        for (int i = 0; i < input.size(); i++) {
            if (used[i]) {
                continue;
            }
            std::string tmp;
            for (int j = 0; j < input.size(); j++) {
                if (i == j || used[j]) {
                    tmp += input[j];
                }
            }
            if (tmp < min_string) {
                min_string = tmp;
                min_index = i;
            }
        }
        used[min_index] = true;
        count++;
        std::cout << min_string << "\n";
    }
    return 0;
}
