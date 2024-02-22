#include <iostream>

std::string input;
bool used[101];

void sol(int left, int right) {
    int min_char = 'Z' + 1;
    int index = -1;
    for (int i = left; i < right + 1; i++) {
        if (!used[i] && input[i] < min_char) {
            min_char = input[i];
            index = i;
        }
    }
    if (index == -1) {
        return;
    }
    used[index] = true;
    for (int i = 0; i < input.size(); i++) {
        if (used[i]) {
            std::cout << input[i];
        }
    }
    std::cout << "\n";

    sol(index + 1, right);
    sol(left, index - 1);
}

int main() {
    std::cin >> input;

    sol(0, input.size() - 1);
    return 0;
}
