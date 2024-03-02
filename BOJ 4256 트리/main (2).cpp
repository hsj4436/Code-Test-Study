#include <iostream>

int T, N;
int pre_order[1001];
int in_order[1001];
int in_order_index[1001];

void post_order(int in_start, int in_end, int pre_start, int pre_end) {
    if (in_start > in_end || pre_start > pre_end) {
        return;
    }
    int root_index = in_order_index[pre_order[pre_start]];
    int left_size = root_index - in_start;

    post_order(in_start, root_index - 1, pre_start + 1, pre_start + left_size);
    post_order(root_index + 1, in_end, pre_start + left_size + 1, pre_end);
    std::cout << in_order[root_index] << " ";
}

int main() {
    std::cin >> T;

    while (T--) {
        std::cin >> N;

        for (int i = 0; i < N; i++) {
            std::cin >> pre_order[i];
        }
        for (int i = 0; i < N; i++) {
            std::cin >> in_order[i];
            in_order_index[in_order[i]] = i;
        }
        post_order(0, N - 1, 0, N - 1);
        std::cout << "\n";
    }
    return 0;
}
