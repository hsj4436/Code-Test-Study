#include <string>
#include <vector>
#include <math.h>
#include <queue>

#define INF 987654321

using namespace std;

int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, -1, 0, 1};

int parent[90001];
int parentLand[301][301];

int findParent(int x) {
    if (parent[x] < 0) {
        return x;
    } else {
        return parent[x] = findParent(parent[x]);
    }
}

int solution(vector<vector<int>> land, int height) {
    int answer = 0;
    int N = land.size();

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            parent[i * N + j] = -1;
            parentLand[i][j] = i * N + j;
        }
    }
    
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < 4; k++) {
                int nx = i + dx[k];
                int ny = j + dy[k];
                if (nx < 0 || nx > N - 1 || ny < 0 || ny > N - 1) {
                    continue;
                }
                
                if (abs(land[i][j] - land[nx][ny]) <= height) {
                    int currentParent = findParent(i * N + j);
                    int nextParent = findParent(nx * N + ny);
                    if (currentParent != nextParent) {
                        if (currentParent < nextParent) {
                            parent[currentParent] += parent[nextParent];
                            parent[nextParent] = currentParent;
                        } else {
                            parent[nextParent] += parent[currentParent];
                            parent[currentParent] = nextParent;
                        }
                    }
                }
            }
        }
    }
    
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            parentLand[i][j] = findParent(i * N + j);
        }
    }
    
    priority_queue<pair<int, pair<int, int>>> pq;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < 4; k++) {
                int nx = i + dx[k];
                int ny = j + dy[k];
                if (nx < 0 || nx > N - 1 || ny < 0 || ny > N - 1) {
                    continue;
                }
                if (parentLand[i][j] == parentLand[nx][ny]) {
                    continue;
                }
                pq.push({-abs(land[i][j] - land[nx][ny]), {min(parentLand[i][j], parentLand[nx][ny]), max(parentLand[i][j], parentLand[nx][ny])}});
            }
        }
    }
    
    while (!pq.empty()) {
        int cost = -pq.top().first;
        int minParent = findParent(pq.top().second.first);
        int maxParent = findParent(pq.top().second.second);
        pq.pop();
        
        if (minParent == maxParent) {
            continue;
        }
        
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (parentLand[i][j] == maxParent) {
                    parent[i * N + j] = minParent;
                    parentLand[i][j] = minParent;
                }
            }
        }
        answer += cost;
    }
    
    return answer;
}