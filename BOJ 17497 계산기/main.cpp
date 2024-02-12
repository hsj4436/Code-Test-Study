#include <iostream>
#include <vector>

long long N;
std::vector<char> operators;

int main() {
    std::cin >> N;

    while (N) {
        if (N & 1) {
            N *= 2;
            operators.push_back('/');
        } else if (N & 2) {
            N -= 2;
            operators.push_back('+');
        } else {
            N /= 2;
            operators.push_back('*');
        }
    }

    if (operators.size() > 99) {
        std::cout << "-1\n";
    } else {
        std::cout << operators.size() << "\n";
        while (!operators.empty()) {
            std::cout << "[" << operators.back() << "] ";
            operators.pop_back();
        }
    }

    return 0;
}
