#include <iostream>

int T, N;
int pre_order[1001];
bool pre_visited[1001];
int in_order[1001];
bool in_visited[1001];
int post_order[1001];

void inOrder(int left, int center, int right, int pre_index) {
    pre_visited[pre_index] = true;
    in_visited[center] = true;
    if (center != left) {
        for (int i = left; i < center; i++) {
            if (in_order[i] == pre_order[pre_index + 1]) {
                inOrder(left, i, center - 1, pre_index + 1);
                break;
            }
        }
    }
    if (center != right) {
        int right_index = 0;
        for (int i = 1; i < N + 1; i++) {
            if (!pre_visited[i]) {
                right_index = i;
                break;
            }
        }
        for (int i = center + 1; i < right + 1; i++) {
            if (in_order[i] == pre_order[right_index]) {
                inOrder(center + 1, i, right, right_index);
            }
        }
    }
    std::cout << in_order[center] << " ";
}

int main() {
    std::cin >> T;

    while (T--) {
        std::cin >> N;

        std::fill(pre_order, pre_order + 1001, 0);
        std::fill(in_order, in_order + 1001, 0);
        std::fill(post_order, post_order + 1001, 0);
        std::fill(pre_visited, pre_visited + 1001, false);
        std::fill(in_visited, in_visited + 1001, false);

        for (int i = 1; i < N + 1; i++) {
            std::cin >> pre_order[i];
        }
        int root = pre_order[1];
        int root_index = 0;
        for (int i = 1; i < N + 1; i++) {
            std::cin >> in_order[i];
            if (in_order[i] == root) {
                root_index = i;
            }
        }
        in_visited[root_index] = true;
        pre_visited[1] = true;
        inOrder(1, root_index, N, 1);
        std::cout << "\n";
    }
    return 0;
}
