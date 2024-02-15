#include <iostream>
#include <vector>
#include <queue>

#define PII std::pair<int, int>
#define RED 3
#define GREEN 4

int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, -1, 0, 1};

int N, M, G, R;
int garden[51][51];
std::vector<PII > can_spread;
std::vector<PII > selected;
std::vector<PII > reds;
std::vector<PII > greens;
int answer = 0;

void bfs() {
    // 3 - red, 4 - green
    PII garden_copy[N][M];
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            garden_copy[i][j] = {garden[i][j], 0};
        }
    }
    std::queue<std::pair<PII, PII>> q; // {color, time}, {x, y}
    for (PII red: reds) {
        garden_copy[red.first][red.second] = {RED, 0};
        q.push({{RED, 0}, red});
    }
    for (PII green: greens) {
        garden_copy[green.first][green.second] = {GREEN, 0};
        q.push({{GREEN, 0}, green});
    }

    int flowers = 0;
    while (!q.empty()) {
        int color = q.front().first.first;
        int t = q.front().first.second;
        int x = q.front().second.first;
        int y = q.front().second.second;
        q.pop();

        if (garden_copy[x][y].first == RED + GREEN) {
            continue;
        }

        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if (nx < 0 || nx > N - 1 || ny < 0 || ny > M - 1) {
                continue;
            }

            if (garden_copy[nx][ny].first == 0 || garden_copy[nx][ny].first == RED + GREEN) {
                continue;
            }

            if (garden_copy[nx][ny].first == 1 || garden_copy[nx][ny].first == 2) {
                garden_copy[nx][ny] = {color, t + 1};
                q.push({{color, t + 1}, {nx, ny}});
            } else if (garden_copy[nx][ny].first == RED && garden_copy[nx][ny].second == t + 1 && color == GREEN) {
                flowers++;
                garden_copy[nx][ny].first = RED + GREEN;
            } else if (garden_copy[nx][ny].first == GREEN && garden_copy[nx][ny].second == t + 1 && color == RED) {
                flowers++;
                garden_copy[nx][ny].first = RED + GREEN;
            }
        }
    }

    answer = std::max(answer, flowers);
}

void select_red_green(int index, int red, int green) {
    if (index == selected.size()) {
        bfs();
        return;
    }

    if (red + 1 <= R) {
        reds.push_back(selected[index]);
        select_red_green(index + 1, red + 1, green);
        reds.pop_back();
    }
    if (green + 1 <= G) {
        greens.push_back(selected[index]);
        select_red_green(index + 1, red, green + 1);
        greens.pop_back();
    }
}

void select_grounds(int index) {
    if (selected.size() == G + R) {
        select_red_green(0, 0, 0);
        return;
    }

    if (index == can_spread.size()) {
        return;
    }

    selected.push_back(can_spread[index]);
    select_grounds(index + 1);
    selected.pop_back();
    select_grounds(index + 1);
}

int main() {
    std::cin >> N >> M >> G >> R;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            std::cin >> garden[i][j];
            if (garden[i][j] == 2) {
                can_spread.push_back({i, j});
            }
        }
    }

    if (can_spread.size() == G + R) {
        selected = can_spread;
        select_red_green(0, 0, 0);
    } else {
        select_grounds(0);
    }

    std::cout << answer << "\n";

    return 0;
}
