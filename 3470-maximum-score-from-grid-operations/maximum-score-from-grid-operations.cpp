class Solution {
public:
    long long maximumScore(vector<vector<int>>& grid) {
        int n = grid.size();

        if (n <= 1)
            return 0;

        // Prefix sums for each column
        vector<vector<long long>> pref(
            n, vector<long long>(n + 1, 0)
        );

        for (int c = 0; c < n; ++c) {
            for (int r = 0; r < n; ++r) {
                pref[c][r + 1] = pref[c][r] + grid[r][c];
            }
        }

        vector<vector<long long>> next_dp(
            n + 1, vector<long long>(n + 1, 0)
        );

        vector<vector<long long>> curr_dp(
            n + 1, vector<long long>(n + 1, 0)
        );

        for (int col = n - 1; col >= 1; --col) {

            for (int prev_h = 0; prev_h <= n; ++prev_h) {

                long long base_max = 0;

                for (int h = 0; h <= prev_h; ++h) {
                    long long score =
                        pref[col][prev_h] - pref[col][h];

                    base_max = max(
                        base_max,
                        score + next_dp[h][prev_h]
                    );
                }

                for (int m = prev_h; m <= n; ++m) {

                    long long max_val = base_max;

                    // Case 1
                    for (int h = prev_h + 1; h <= m; ++h) {
                        max_val = max(
                            max_val,
                            next_dp[h][h]
                        );
                    }

                    // Case 2
                    for (int h = m + 1; h <= n; ++h) {

                        long long score =
                            pref[col - 1][h] -
                            pref[col - 1][m];

                        max_val = max(
                            max_val,
                            score + next_dp[h][h]
                        );
                    }

                    curr_dp[prev_h][m] = max_val;
                }
            }

            next_dp = curr_dp;
        }

        long long ans = 0;

        for (int h0 = 0; h0 <= n; ++h0) {
            ans = max(ans, next_dp[h0][h0]);
        }

        return ans;
    }
};