#include <iostream>
#include <vector>
#include <algorithm>

int N, M, K;
std::vector<int> cards;
int parent[4000001];

int find_parent(int x) {
    if (parent[x] == x) {
        return x;
    } else {
        return parent[x] = find_parent(parent[x]);
    }
}

int main() {
    std::cin.tie(NULL);
    std::ios::sync_with_stdio(false);

    std::cin >> N >> M >> K;

    cards.resize(M);

    for (int i = 0; i < M; i++) {
        std::cin >> cards[i];
    }

    std::sort(cards.begin(), cards.end());

    // 이전에 답 보고 풀때는 지나쳤는데,
    // 카드 인덱스를 유니온 파인드로 관리할 것이기 때문에 가지는 카드 개수만큼만 부로를 설정
    for (int i = 0; i < M; i++) {
        parent[i] = i;
    }

    int card;
    for (int i = 0; i < K; i++) {
        std::cin >> card;
        int index = std::upper_bound(cards.begin(), cards.end(), card) - cards.begin();
        int p = find_parent(index);
        std::cout << cards[p] << "\n";
        parent[p] = p + 1;
    }

    return 0;
}