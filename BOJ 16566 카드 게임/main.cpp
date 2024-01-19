#include <iostream>
#include <vector>
#include <algorithm>

int N, M, K;
int parents[4000001];
std::vector<int> cards;

int find_card(int x) {
    if (parents[x] == x) {
        return parents[x];
    } else {
        return parents[x] = find_card(parents[x]);
    }
}

void union_card(int a, int b) {
    // b = a + 1
    a = find_card(a), b = find_card(b);
    if (a == b) {
        return;
    }
    parents[a] = b;
}

int main() {
    std::cin.tie(NULL);
    std::ios::sync_with_stdio(false);

    std::cin >> N >> M >> K;

    for (int i = 1; i < N + 1; i++) {
        parents[i] = i;
    }

    int card;
    for (int i = 0; i < M; i++) {
        std::cin >> card;
        cards.push_back(card);
        parents[card] = card;
    }

    std::sort(cards.begin(), cards.end());

    for (int i = 0; i < K; i++) {
        std::cin >> card;
        int d = find_card(std::upper_bound(cards.begin(), cards.end(), card) - cards.begin());
        std::cout << cards[d] << "\n";
        union_card(d, d + 1);
    }
    return 0;
}
