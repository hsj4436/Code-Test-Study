#include <iostream>
#include <queue>

int N, M;
int parents[100001];
long long set_size[100001];
std::priority_queue<std::pair<int, std::pair<int, int>>> pq;

long long MOD = 1000000000;

//U   V                                                             Cost(U, V)
//1   2   (2, 3), (4, 5), (3, 5), (3, 4), (2, 6), (1, 2)            30
//1   3   (2, 3), (4, 5), (3, 5), (3, 4), (2, 6)                    20
//1   4   (2, 3), (4, 5), (3, 5), (3, 4)                            14
//1   5   (2, 3), (4, 5), (3, 5)                                    9
//1   6   (2, 3), (4, 5), (3, 5), (3, 4), (2, 6)                    20
//2   3   (2, 3), (4, 5), (3, 5), (3, 4), (2, 6)                    20
//2   4   (2, 3), (4, 5), (3, 5), (3, 4)                            14
//2   5   (2, 3), (4, 5), (3, 5)                                    9
//2   6   (2, 3), (4, 5), (3, 5), (3, 4), (2, 6)                    20
//3   4   (2, 3), (4, 5), (3, 5), (3, 4)                            14
//3   5   (2, 3), (4, 5), (3, 5)                                    9
//3   6   (2, 3), (4, 5), (3, 5), (3, 4), (2, 6), (1, 2), (3, 6)    45
//4   5   (2, 3), (4, 5), (3, 5)                                    9
//4   6   (2, 3), (4, 5), (3, 5), (3, 4)                            14
//5   6   (2, 3), (4, 5), (3, 5)                                    9

int find_parent(int x) {
    if (parents[x] == x) {
        return parents[x];
    } else {
        return parents[x] = find_parent(parents[x]);
    }
}

int main() {
    std::cin.tie(NULL);
    std::ios::sync_with_stdio(false);

    std::cin >> N >> M;

    for (int i = 1; i < N + 1; i++) {
        parents[i] = i;
        set_size[i] = 1;
    }

    int x, y, w;
    long long sum_of_weight = 0;
    for (int i = 0; i < M; i++) {
        std::cin >> x >> y >> w;
        pq.push({w, {x, y}});
        sum_of_weight += w;
    }

    long long answer = 0;
    while (!pq.empty()) {
        int from = pq.top().second.first;
        int to = pq.top().second.second;
        int cost = pq.top().first;
        pq.pop();

        int px = find_parent(from);
        int py = find_parent(to);

        if (px != py) {
            answer += (((1L * set_size[px] * set_size[py]) % MOD) * sum_of_weight) % MOD;
            answer %= MOD;

            parents[py] = px;
            set_size[px] += set_size[py];
            set_size[py] = 1;
        }

        sum_of_weight -= cost;
    }

    std::cout << answer % MOD << "\n";

    return 0;
}