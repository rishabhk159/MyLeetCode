#include <vector>
#include <queue>
#include <string>

using namespace std;

class Solution {
public:
    int shortestPath(int n, vector<vector<int>>& edges, string labels, int k) {
        if (n == 1) return 0;

        // Build the adjacency list: adj[u] = list of {v, weight}
        vector<vector<pair<int, int>>> adj(n);
        for (const auto& edge : edges) {
            adj[edge[0]].push_back({edge[1], edge[2]});
        }

        // dist[u][count] = minimum weight to reach node u with `count` consecutive identical characters
        const int INF = 1e9 + 7;
        vector<vector<int>> dist(n, vector<int>(k + 1, INF));

        // Priority queue stores tuples: {current_dist, u, count}
        // Min-heap ordered by distance
        using State = tuple<int, int, int>;
        priority_queue<State, vector<State>, greater<State>> pq;

        // Base case: starting at node 0 with 1 instance of labels[0]
        dist[0][1] = 0;
        pq.push({0, 0, 1});

        while (!pq.empty()) {
            auto [d, u, count] = pq.top();
            pq.pop();

            // Destination reached with minimum distance
            if (u == n - 1) {
                return d;
            }

            if (d > dist[u][count]) continue;

            for (const auto& [v, weight] : adj[u]) {
                int next_count = (labels[v] == labels[u]) ? count + 1 : 1;

                // Path is valid only if consecutive identical characters do not exceed k
                if (next_count <= k) {
                    if (d + weight < dist[v][next_count]) {
                        dist[v][next_count] = d + weight;
                        pq.push({dist[v][next_count], v, next_count});
                    }
                }
            }
        }

        return -1;
    }
};