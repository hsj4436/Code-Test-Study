#include <string>
#include <math.h>
#include <algorithm>
#include <vector>

using namespace std;

vector<long long> weight;
bool visited[300001];
long long dp[300001];
vector<int> graph[300001];

long long sol(int cur) {
    for (int next : graph[cur]) {
        if (visited[next]) {
            continue;
        }
        visited[next] = true;
        weight[cur] += sol(next);
        dp[cur] += dp[next];
    }
    
    dp[cur] += abs(weight[cur]);
    return weight[cur];
}

long long solution(vector<int> a, vector<vector<int>> edges) {
    long long answer = -2;
    int u, v;
    for (int i = 0; i < edges.size(); i++) {
        u = edges[i][0];
        v = edges[i][1];
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    for (int i = 0; i < a.size(); i++) {
        weight.push_back(a[i]);
    }
    
    visited[0] = true;
    sol(0);
    
    if (weight[0] != 0) {
        answer = -1;
    } else {
        answer = dp[0];
    }
    
    
    return answer;
}