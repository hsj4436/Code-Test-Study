#include <iostream>

int N, M;
long long times[10001];

long long get_ridden_child_at_T(long long t) {
    long long ret = M;
    for (int i = 1; i < M + 1; i++) {
        ret += t / times[i];
    }

    return ret;
}

int main() {
    std::cin.tie(NULL);
    std::ios::sync_with_stdio(false);

    std::cin >> N >> M;

    long long max_time = 0;
    for (int i = 1; i < M + 1; i++) {
        std::cin >> times[i];
        max_time = std::max(max_time, times[i]);
    }

    if (N <= M) {
        std::cout << N << "\n";
        return 0;
    }

    long long left = 0, right = 2000000000LL / 30LL;
    long long T = 0;
    while (left <= right) {
        long long mid = (left + right) / 2;
        if (get_ridden_child_at_T(mid) >= N) {
            T = mid;
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }

    long long ans = 0;
    long long already_ride = get_ridden_child_at_T(T - 1);

    for (int i = 1; i < M + 1; i++) {
        if (T % times[i] == 0) {
            ans = i;
            already_ride++;
        }
        if (already_ride == N) {
            break;
        }
    }

    std::cout << ans << "\n";

    return 0;
}