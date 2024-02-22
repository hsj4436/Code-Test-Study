#include <iostream>
#include <math.h>
#include <algorithm>
#include <vector>
#include <map>

int N;
std::vector<std::string> words;
std::map<char, int> counts;

int main() {
    std::cin >> N;

    words.resize(N);
    for (int i = 0; i < N; i++) {
        std::cin >> words[i];
    }

    std::sort(words.begin(), words.end());

    for (std::string word : words) {
        for (int i = word.size() - 1; i > -1; i--) {
            counts[word[i]] += std::pow(10, word.size() - 1 - i);
        }
    }

    std::vector<std::pair<char, int>> counts_vector(counts.begin(), counts.end());
    std::sort(counts_vector.begin(), counts_vector.end(), [&](std::pair<char, int> a, std::pair<char, int> b) {
        return a.second > b.second;
    });

    int answer = 0;
    int assign = 9;
    for (auto p : counts_vector) {
        answer += p.second * assign;
        assign--;
    }

    std::cout << answer << "\n";

    return 0;
}