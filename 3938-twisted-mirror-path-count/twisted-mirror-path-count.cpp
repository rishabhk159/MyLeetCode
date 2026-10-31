#include <vector>

using namespace std;

class Solution {
public:
    int uniquePaths(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        const int MOD = 1'000'000'007;

        // dp[i][j][0]: ways entering (i, j) moving RIGHT
        // dp[i][j][1]: ways entering (i, j) moving DOWN
        vector<vector<vector<int>>> dp(m, vector<vector<int>>(n, vector<int>(2, 0)));

        // Base case: from (0, 0)
        if (n > 1) {
            dp[0][1][0] = 1; // Moving right to (0, 1)
        }
        if (m > 1) {
            dp[1][0][1] = 1; // Moving down to (1, 0)
        }

        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (i == 0 && j == 0) continue;
                if (i == m - 1 && j == n - 1) continue; // Destination reached

                if (grid[i][j] == 0) {
                    long long total = (dp[i][j][0] + dp[i][j][1]) % MOD;
                    if (total == 0) continue;

                    // Can move right
                    if (j + 1 < n) {
                        dp[i][j + 1][0] = (dp[i][j + 1][0] + total) % MOD;
                    }
                    // Can move down
                    if (i + 1 < m) {
                        dp[i + 1][j][1] = (dp[i + 1][j][1] + total) % MOD;
                    }
                } else {
                    // Mirror reflection:
                    // 1. Moving right -> deflected down
                    if (dp[i][j][0] > 0 && i + 1 < m) {
                        dp[i + 1][j][1] = (dp[i + 1][j][1] + dp[i][j][0]) % MOD;
                    }
                    // 2. Moving down -> deflected right
                    if (dp[i][j][1] > 0 && j + 1 < n) {
                        dp[i][j + 1][0] = (dp[i][j + 1][0] + dp[i][j][1]) % MOD;
                    }
                }
            }
        }

        return (dp[m - 1][n - 1][0] + dp[m - 1][n - 1][1]) % MOD;
    }
};