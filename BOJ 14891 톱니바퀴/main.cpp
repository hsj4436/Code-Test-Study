#include <iostream>
#include <math.h>

int K;
bool wheels[4][8]; // false - N, true - S
int head[4];       // 12시 위치에 있는 톱니의 index

int main() {
    std::string state;
    for (int i = 0; i < 4; i++) {
        std::cin >> state;
        for (int j = 0; j < 8; j++) {
            if (state[j] == '1') {
                wheels[i][j] = true;
            }
        }
    }

    std::cin >> K;

    int index, direction;
    for (int k = 0; k < K; k++) {
        std::cin >> index >> direction;
        if (direction == 1) {
            // clockwise
            bool right = wheels[index - 1][(head[index - 1] + 2) % 8];
            int cur_direction = -1;
            for (int i = index; i < 4; i++) {
                if (wheels[i][(head[i] + 6) % 8] != right) {
                    right = wheels[i][(head[i] + 2) % 8];
                    head[i] = (head[i] + (cur_direction * -1) + 8) % 8;
                    cur_direction *= -1;
                } else {
                    break;
                }
            }
            bool left = wheels[index - 1][(head[index - 1] + 6) % 8];
            cur_direction = -1;
            for (int i = index - 2; i > -1; i--) {
                if (wheels[i][(head[i] + 2) % 8] != left) {
                    left = wheels[i][(head[i] + 6) % 8];
                    head[i] = (head[i] + (cur_direction * -1) + 8) % 8;
                    cur_direction *= -1;
                } else {
                    break;
                }
            }
            head[index - 1] = (head[index - 1] + (direction * -1) + 8) % 8;
        } else {
            bool right = wheels[index - 1][(head[index - 1] + 2) % 8];
            int cur_direction = 1;
            for (int i = index; i < 4; i++) {
                if (wheels[i][(head[i] + 6) % 8] != right) {
                    right = wheels[i][(head[i] + 2) % 8];
                    head[i] = (head[i] + (cur_direction * -1) + 8) % 8;
                    cur_direction *= -1;
                } else {
                    break;
                }
            }
            bool left = wheels[index - 1][(head[index - 1] + 6) % 8];
            cur_direction = 1;
            for (int i = index - 2; i > -1; i--) {
                if (wheels[i][(head[i] + 2) % 8] != left) {
                    left = wheels[i][(head[i] + 6) % 8];
                    head[i] = (head[i] + (cur_direction * -1) + 8) % 8;
                    cur_direction *= -1;
                } else {
                    break;
                }
            }
            head[index - 1] = (head[index - 1] + (direction * -1) + 8) % 8;
        }
    }

    int score = 0;
    for (int i = 0; i < 4; i++) {
        if (wheels[i][head[i]]) {
            score += std::pow(2, i);
        }
    }

    std::cout << score << "\n";

    return 0;
}
