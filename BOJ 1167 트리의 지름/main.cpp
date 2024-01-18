#include <iostream>
#include <vector>
#include <queue>

int V;
std::vector<std::pair<int, int>> edges[100001];
int dist[100001];

void dijkstra(int start) {
    dist[start] = 0;
    std::priority_queue<std::pair<int, int>> pq;
    pq.push({start, 0});
    
    while (!pq.empty()) {
        int cur = pq.top().first;
        int distance = pq.top().second;
        pq.pop();
        
        for (auto p : edges[cur]) {
            if (distance + p.second < dist[p.first]) {
                dist[p.first] = distance + p.second;
                pq.push({p.first, distance + p.second});
            }
        }
    }
}

int main() {
    std::cin >> V;
    
    for (int i = 0; i < V; i++) {
        int from, to, distance;
        std::cin >> from;
        while (true) {
            std::cin >> to;
            if (to == -1) {
                break;
            }
            std::cin >> distance;
            edges[from].push_back({to, distance});
        }
    }

    std::fill(dist, dist + 100001, 2000000000);
    dijkstra(1);
    int max_distance = 0;
    int first_node = 0;
    for (int i = 1; i < V + 1; i++) {
        if (dist[i] > max_distance) {
            first_node = i;
            max_distance = dist[i];
        }
    }
    
    std::fill(dist, dist + 100001, 2000000000);
    dijkstra(first_node);
    for (int i = 1; i < V + 1; i++) {
        max_distance = std::max(max_distance, dist[i]);
    }

    std::cout << max_distance << "\n";
    
    return 0;
}
