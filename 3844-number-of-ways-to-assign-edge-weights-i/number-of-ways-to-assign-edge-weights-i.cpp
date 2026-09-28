class Solution {
public:
    int assignEdgeWeights(vector<vector<int>>& edges) {
        const long long MOD = 1000000007;

        int n = edges.size() + 1;

        vector<vector<int>> graph(n + 1);

        for (auto& edge : edges) {
            int u = edge[0];
            int v = edge[1];

            graph[u].push_back(v);
            graph[v].push_back(u);
        }

        // Find maximum depth from node 1
        vector<int> depth(n + 1, -1);
        queue<int> q;

        q.push(1);
        depth[1] = 0;

        int maxDepth = 0;

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            for (int v : graph[u]) {
                if (depth[v] != -1) {
                    continue;
                }

                depth[v] = depth[u] + 1;
                maxDepth = max(maxDepth, depth[v]);

                q.push(v);
            }
        }

        // Number of assignments with odd total cost = 2^(maxDepth - 1)
        long long answer = 1;

        for (int i = 0; i < maxDepth - 1; i++) {
            answer = (answer * 2) % MOD;
        }

        return answer;
    }
};