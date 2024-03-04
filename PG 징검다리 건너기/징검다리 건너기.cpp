#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int solution(vector<int> stones, int k) {
    int answer = 0;
    
    int left = 1;
    int right = 200000000;
    
    while (left <= right) {
        int mid = (left + right) / 2;
        int K_streak = 0;
        bool possible = true;
        for (int i = 0; i < stones.size(); i++) {
            if (stones[i] - mid <= 0) {
                K_streak++;
                if (K_streak >= k) {
                    possible = false;
                    break;
                }
            } else {
                K_streak = 0;
            }
        }
        if (possible) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    answer = left;
    
    return answer;
}