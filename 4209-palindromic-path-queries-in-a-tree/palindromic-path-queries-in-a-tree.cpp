#include <vector>
#include <string>
#include <sstream>

using namespace std;

class Solution {
    int n;
    vector<vector<int>> adj;
    vector<int> tin, tout, depth, init_mask;
    vector<vector<int>> up;
    vector<int> bit;
    int timer = 0;
    int LOG = 17;

    void dfs(int u, int p, int d, const string& s, int current_mask) {
        depth[u] = d;
        up[u][0] = p;
        for (int j = 1; j < LOG; ++j) {
            up[u][j] = up[up[u][j - 1]][j - 1];
        }

        tin[u] = ++timer;
        current_mask ^= (1 << (s[u] - 'a'));
        init_mask[u] = current_mask;

        for (int v : adj[u]) {
            if (v != p) {
                dfs(v, u, d + 1, s, current_mask);
            }
        }
        tout[u] = timer;
    }

    void add_point(int idx, int val) {
        for (; idx <= n; idx += idx & -idx) {
            bit[idx] ^= val;
        }
    }

    // Range XOR update on [l, r]
    void range_update(int l, int r, int val) {
        add_point(l, val);
        add_point(r + 1, val);
    }

    // Point query for delta at index
    int point_query(int idx) {
        int res = 0;
        for (; idx > 0; idx -= idx & -idx) {
            res ^= bit[idx];
        }
        return res;
    }

    int get_lca(int u, int v) {
        if (depth[u] < depth[v]) swap(u, v);
        for (int j = LOG - 1; j >= 0; --j) {
            if (depth[u] - (1 << j) >= depth[v]) {
                u = up[u][j];
            }
        }
        if (u == v) return u;
        for (int j = LOG - 1; j >= 0; --j) {
            if (up[u][j] != up[v][j]) {
                u = up[u][j];
                v = up[v][j];
            }
        }
        return up[u][0];
    }

public:
    vector<bool> palindromePath(int n, vector<vector<int>>& edges, string s, vector<string>& queries) {
        this->n = n;
        adj.assign(n, vector<int>());
        for (const auto& e : edges) {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }

        tin.resize(n);
        tout.resize(n);
        depth.resize(n);
        init_mask.resize(n);
        
        LOG = 1;
        while ((1 << LOG) <= n) LOG++;
        up.assign(n, vector<int>(LOG, 0));
        bit.assign(n + 2, 0);
        timer = 0;

        // DFS to compute LCA tables, discovery intervals, and initial prefix XOR masks
        dfs(0, 0, 0, s, 0);

        vector<bool> ans;
        for (const string& q : queries) {
            stringstream ss(q);
            string type;
            ss >> type;
            if (type == "update") {
                int u;
                char c;
                ss >> u >> c;
                if (s[u] != c) {
                    int diff = (1 << (s[u] - 'a')) ^ (1 << (c - 'a'));
                    s[u] = c;
                    range_update(tin[u], tout[u], diff);
                }
            } else {
                int u, v;
                ss >> u >> v;
                int lca = get_lca(u, v);
                
                // Current path mask from root = initial_mask ^ accumulated_delta
                int p_u = init_mask[u] ^ point_query(tin[u]);
                int p_v = init_mask[v] ^ point_query(tin[v]);
                int val_lca = (1 << (s[lca] - 'a'));

                int path_mask = p_u ^ p_v ^ val_lca;
                // At most one odd frequency character
                ans.push_back((path_mask & (path_mask - 1)) == 0);
            }
        }

        return ans;
    }
};