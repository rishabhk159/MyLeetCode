class Solution {
public:
    int maxPathScore(vector<vector<int>>& grid, int k) {
        // Fast I/O
        ios_base::sync_with_stdio(false);
        cin.tie(nullptr);

        int m = grid.size();
        int n = grid[0].size();

        // Any path from (0,0) to (m-1,n-1) visits exactly (m + n - 1) cells.
        // The maximum cost incurred cannot exceed (m + n - 1).
        k = min(k, m + n - 1);

        // dp[j][c] = max score at column j with cost c
        // Rolling 1D array across columns to keep memory cache-friendly
        vector<vector<short>> dp(n, vector<short>(k + 1, -1));

        // Start cell (0, 0)
        int start_val = grid[0][0];
        int start_cost = (start_val == 0 ? 0 : 1);
        int start_score = start_val;

        if (start_cost <= k) {
            dp[0][start_cost] = start_score;
        }

        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (i == 0 && j == 0) continue;

                int val = grid[i][j];
                int cost = (val == 0 ? 0 : 1);
                int score = val;

                vector<short> cur(k + 1, -1);

                for (int c = cost; c <= k; ++c) {
                    short best_prev = -1;

                    // From top: dp[j][c - cost] (which holds row i - 1 values)
                    if (i > 0 && dp[j][c - cost] != -1) {
                        best_prev = max(best_prev, dp[j][c - cost]);
                    }

                    // From left: cur from (j - 1), which is already updated in this row
                    if (j > 0 && dp[j - 1][c - cost] != -1) {
                        best_prev = max(best_prev, dp[j - 1][c - cost]);
                    }

                    if (best_prev != -1) {
                        cur[c] = best_prev + score;
                    }
                }

                dp[j] = move(cur);
            }
        }

        int max_score = -1;
        for (int c = 0; c <= k; ++c) {
            if (dp[n - 1][c] != -1) {
                max_score = max(max_score, (int)dp[n - 1][c]);
            }
        }

        return max_score;
    }
};