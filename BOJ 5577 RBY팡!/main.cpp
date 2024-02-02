#include <iostream>
#include <vector>
#include <cstring>

int N;
std::vector<int> balls;
std::vector<int> balls_copy;
bool exploded[10001];
int answer = 10001;

void explode(int start, int end, int c) {
    std::memset(exploded, false, sizeof(exploded));
    while (end < N) {
        if (balls_copy[end] == c) {
            end++;
        } else {
            break;
        }
    }
    while (start > -1) {
        if (balls_copy[start] == c) {
            start--;
        } else {
            break;
        }
    }
    for (int i = start + 1; i < end; i++) {
        exploded[i] = true;
    }
    if (end == N || start == -1) {
        int cnt = 0;
        for (int i = 0; i < N; i++) {
            if (!exploded[i]) {
                cnt++;
            }
        }
        answer = std::min(answer, cnt);
        return;
    }
    if (balls_copy[start] != balls_copy[end]) {
        int cnt = 0;
        for (int i = 0; i < N; i++) {
            if (!exploded[i]) {
                cnt++;
            }
        }
        answer = std::min(answer, cnt);
        return;
    }
    int length = 2;
    int color = balls_copy[start];
    std::vector<int> to_explode;
    to_explode.push_back(start);
    to_explode.push_back(end);
    while (true) {
        bool moved = false;
        if (start - 1 > -1 && balls_copy[start - 1] == color) {
            start--;
            to_explode.push_back(start);
            length++;
            moved = true;
        }
        if (end + 1 < N && balls_copy[end + 1] == color) {
            end++;
            to_explode.push_back(end);
            length++;
            moved = true;
        }
        if (!moved) {
            if (length >= 4) {
                for (auto i : to_explode) {
                    exploded[i] = true;
                }
                to_explode.clear();
                if (start - 1 > -1 && end + 1 < N) {
                    start--;
                    end++;
                    if (balls_copy[start] != balls_copy[end]) {
                        int cnt = 0;
                        for (int i = 0; i < N; i++) {
                            if (!exploded[i]) {
                                cnt++;
                            }
                        }
                        answer = std::min(answer, cnt);
                        return;
                    }
                    to_explode.push_back(start);
                    to_explode.push_back(end);
                    length = 2;
                    color = balls_copy[start];
                } else {
                    int cnt = 0;
                    for (int i = 0; i < N; i++) {
                        if (!exploded[i]) {
                            cnt++;
                        }
                    }
                    answer = std::min(answer, cnt);
                    return;
                }
            } else {
                int cnt = 0;
                for (int i = 0; i < N; i++) {
                    if (!exploded[i]) {
                        cnt++;
                    }
                }
                answer = std::min(answer, cnt);
                return;
            }
        }
    }

    return;
}

int main() {
    std::cin >> N;

    int color;
    for (int i = 0; i < N; i++) {
        std::cin >> color;
        balls.push_back(color);
    }

    for (int i = 0; i < N - 3; i++) {
        int colors[4] = {0, };
        for (int j = i; j < i + 4; j++) {
            colors[balls[j]]++;
        }
        if (colors[1] == 3 && colors[2] == 1) {
            balls_copy = balls;
            for (int j = i; j < i + 4; j++) {
                if (balls_copy[j] == 2) {
                    balls_copy[j] = 1;
                }
            }
            explode(i, i + 3, 1);
        } else if (colors[1] == 3 && colors[3] == 1) {
            balls_copy = balls;
            for (int j = i; j < i + 4; j++) {
                if (balls_copy[j] == 3) {
                    balls_copy[j] = 1;
                }
            }
            explode(i, i + 3, 1);
        } else if (colors[2] == 3 && colors[1] == 1) {
            balls_copy = balls;
            for (int j = i; j < i + 4; j++) {
                if (balls_copy[j] == 1) {
                    balls_copy[j] = 2;
                }
            }
            explode(i, i + 3, 2);
        } else if (colors[2] == 3 && colors[3] == 1) {
            balls_copy = balls;
            for (int j = i; j < i + 4; j++) {
                if (balls_copy[j] == 3) {
                    balls_copy[j] = 2;
                }
            }
            explode(i, i + 3, 2);
        } else if (colors[3] == 3 && colors[1] == 1) {
            balls_copy = balls;
            for (int j = i; j < i + 4; j++) {
                if (balls_copy[j] == 1) {
                    balls_copy[j] = 3;
                }
            }
            explode(i, i + 3, 3);
        } else if (colors[3] == 3 && colors[2] == 1) {
            balls_copy = balls;
            for (int j = i; j < i + 4; j++) {
                if (balls_copy[j] == 2) {
                    balls_copy[j] = 3;
                }
            }
            explode(i, i + 3, 3);
        }
    }

    if (answer == 10001) {
        std::cout << N << "\n";
    } else {
        std::cout << answer << "\n";
    }

    return 0;
}