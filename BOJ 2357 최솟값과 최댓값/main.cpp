#include <iostream>

#define PII std::pair<int, int> // {min, max}
#define INF {1000000001, 0}

int N, M;
int arr[100001];
PII tree[400004];

PII init(int start, int end, int node) {
    if (start == end) {
        return tree[node] = {arr[start], arr[start]};
    }
    int mid = (start + end) / 2;
    PII left = init(start, mid, node * 2);
    PII right = init(mid + 1, end, node * 2 + 1);
    return tree[node] = {std::min(left.first, right.first), std::max(left.second, right.second)};
}

PII query(int start, int end, int node, int left, int right) {
    if (right < start || end < left) {
        return INF;
    }
    if (left <= start && end <= right) {
        return tree[node];
    }

    int mid = (start + end) / 2;
    PII left_tree = query(start, mid, node * 2, left, right);
    PII right_tree = query(mid + 1, end, node * 2 + 1, left, right);
    return {std::min(left_tree.first, right_tree.first), std::max(left_tree.second, right_tree.second)};
}

int main() {
    std::cin.tie(NULL);
    std::ios::sync_with_stdio(false);

    std::cin >> N >> M;

    for (int i = 1; i < N + 1; i++) {
        std::cin >> arr[i];
    }

    init(1, N, 1);

    int A, B;
    for (int i = 0; i < M; i++) {
        std::cin >> A >> B;
        PII result = query(1, N, 1, A, B);
        std::cout << result.first << " " << result.second << "\n";
    }
}