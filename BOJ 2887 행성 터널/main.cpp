#include <iostream>
#include <algorithm>
#include <queue>

#define LL long long
#define PLL std::pair<LL, LL>

struct planet {
    int index;
    LL x;
    LL y;
    LL z;
    planet() {}
    planet(int index, LL x, LL y, LL z) : index(index), x(x), y(y), z(z) {}
};

int N;
planet planets[100001];
LL parents[100001];

LL find_parent(LL x) {
    if (parents[x] == x) {
        return x;
    } else {
        return parents[x] = find_parent(parents[x]);
    }
}

int main() {
    std::cin.tie(NULL);
    std::ios::sync_with_stdio(false);

    std::cin >> N;

    LL X, Y, Z;
    for (int i = 0; i < N; i++) {
        std::cin >> X >> Y >> Z;
        planets[i] = planet(i, X, Y, Z);
        parents[i] = i;
    }

    std::priority_queue<std::pair<LL, PLL>> pq;

    std::sort(planets, planets + N, [&](planet a, planet b) {
        return a.x < b.x;
    });
    for (int i = 0; i < N - 1; i++) {
        pq.push({-std::abs(planets[i].x - planets[i + 1].x), {planets[i].index, planets[i + 1].index}});
    }

    std::sort(planets, planets + N, [&](planet a, planet b) {
        return a.y < b.y;
    });
    for (int i = 0; i < N - 1; i++) {
        pq.push({-std::abs(planets[i].y - planets[i + 1].y), {planets[i].index, planets[i + 1].index}});
    }

    std::sort(planets, planets + N, [&](planet a, planet b) {
        return a.z < b.z;
    });
    for (int i = 0; i < N - 1; i++) {
        pq.push({-std::abs(planets[i].z - planets[i + 1].z), {planets[i].index, planets[i + 1].index}});
    }

    int cnt = 0;
    LL answer = 0;
    while (cnt != N - 1) {
        LL distance = -pq.top().first;
        LL x = pq.top().second.first;
        LL y = pq.top().second.second;
        pq.pop();

        LL px = find_parent(x);
        LL py = find_parent(y);

        if (px == py) {
            continue;
        }

        if (px < py) {
            parents[py] = px;
        } else {
            parents[px] = py;
        }
        answer += distance;
        cnt++;
    }

    std::cout << answer << "\n";

    return 0;
}