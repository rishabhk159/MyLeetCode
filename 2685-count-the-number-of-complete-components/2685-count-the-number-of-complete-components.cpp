class Solution {
public:
    vector<vector<int>> adj;
    vector<int> vis;

    void dfs(int u, vector<int>& comp) {
        vis[u] = 1;
        comp.push_back(u);

        for (int v : adj[u]) {
            if (!vis[v])
                dfs(v, comp);
        }
    }

    int countCompleteComponents(int n, vector<vector<int>>& edges) {
        adj.assign(n, {});
        vis.assign(n, 0);

        for (auto &e : edges) {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }

        int ans = 0;

        for (int i = 0; i < n; i++) {
            if (!vis[i]) {
                vector<int> comp;
                dfs(i, comp);

                int vertices = comp.size();
                int edgeCount = 0;

                for (int node : comp)
                    edgeCount += adj[node].size();

                edgeCount /= 2;

                if (edgeCount == vertices * (vertices - 1) / 2)
                    ans++;
            }
        }

        return ans;
    }
};