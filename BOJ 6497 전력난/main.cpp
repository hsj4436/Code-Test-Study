#include <iostream>
#include <queue>

int M, N;
int parent[200001];

int find_parent(int x) {
    if (parent[x] == x) {
        return x;
    } else {
        return parent[x] = find_parent(parent[x]);
    }
}

int main() {
    while (true) {
        std::cin >> M >> N;
        if (M == 0 && N == 0) {
            break;
        }

        for (int i = 1; i < M + 1; i++) {
            parent[i] = i;
        }

        int total_cost = 0;
        std::priority_queue<std::pair<int, std::pair<int, int>>> pq;
        for (int i = 0; i < N; i++) {
            int x, y, z;
            std::cin >> x >> y >> z;
            total_cost += z;
            pq.push({-z, {x, y}});
        }

        int cnt = 0;
        int min_cost = 0;
        while (cnt != M - 1) {
            int distance = -pq.top().first;
            int from = pq.top().second.first;
            int to = pq.top().second.second;
            pq.pop();

            if (parent[from] == parent[to]) {
                continue;
            }

            int parent_from = find_parent(from);
            int parent_to = find_parent(to);

            if (parent_from == parent_to) {
                continue;
            }

            if (parent_from < parent_to) {
                parent[parent_to] = parent_from;
            } else {
                parent[parent_from] = parent_to;
            }
            cnt++;
            min_cost += distance;
        }

        std::cout << total_cost - min_cost << "\n";
    }
    return 0;
}
