class Solution {
public:
    int maxPathScore(vector<vector<int>>& grid, int k) {
        int m = grid.size();
        int n = grid[0].size();

        const int NEG = -1e9;

        // dp[j][c] = max score reaching current cell (i,j)
        // with exactly c cost
        vector<vector<int>> dp(n, vector<int>(k + 1, NEG));

        // Starting cell is always 0
        dp[0][0] = 0;

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {

                // Starting cell
                if (i == 0 && j == 0)
                    continue;

                int cost = (grid[i][j] == 0 ? 0 : 1);
                int score = grid[i][j];

                vector<int> cur(k + 1, NEG);

                // From top
                if (i > 0) {
                    for (int c = cost; c <= k; c++) {
                        if (dp[j][c - cost] != NEG) {
                            cur[c] = max(cur[c],
                                         dp[j][c - cost] + score);
                        }
                    }
                }

                // From left
                if (j > 0) {
                    for (int c = cost; c <= k; c++) {
                        if (dp[j - 1][c - cost] != NEG) {
                            cur[c] = max(cur[c],
                                         dp[j - 1][c - cost] + score);
                        }
                    }
                }

                dp[j] = move(cur);
            }
        }

        int ans = -1;

        // We can use any cost <= k
        for (int c = 0; c <= k; c++) {
            ans = max(ans, dp[n - 1][c]);
        }

        return ans == NEG ? -1 : ans;
    }
};