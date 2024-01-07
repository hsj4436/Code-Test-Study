#include <iostream>
#include <math.h>
#include <queue>

int N;
std::pair<float, float> stars[101];
int parent[101];

int find_parent(int x) {
    if (parent[x] == x) {
        return x;
    } else {
        return parent[x] = find_parent(parent[x]);
    }
}

int main() {
    std::cin >> N;

    for (int i = 1; i < N + 1; i++) {
        std::cin >> stars[i].first >> stars[i].second;
        parent[i] = i;
    }

    std::priority_queue<std::pair<float, std::pair<int, int>>> pq;
    for (int i = 1; i < N + 1; i++) {
        for (int j = i + 1; j < N + 1; j++) {
            float distance = std::sqrt(std::pow(stars[i].first - stars[j].first, 2) + std::pow(stars[i].second - stars[j].second, 2));
            pq.push({-distance, {i, j}});
        }
    }

    int cnt = 0;
    float answer = 0.0f;
    while (cnt != N - 1) {
        float distance = -pq.top().first;
        int from = pq.top().second.first;
        int to = pq.top().second.second;
        pq.pop();

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
        answer += distance;
        cnt++;
    }

    std::cout << answer << "\n";
    return 0;
}
