#include <vector>
#include <bitset>
#include <algorithm>

class Solution {
public:
    int minCost(std::vector<std::vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        
        // dp[i][j][v] indicates if XOR sum 'v' is reachable at (i, j)
        std::vector<std::vector<std::bitset<1024>>> dp(m, std::vector<std::bitset<1024>>(n));
        
        // Base case: starting point
        dp[0][0].set(grid[0][0]);
        
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (i == 0 && j == 0) continue;
                
                int val = grid[i][j];
                
                // Transition from top cell (i - 1, j)
                if (i > 0) {
                    for (int k = 0; k < 1024; ++k) {
                        if (dp[i - 1][j].test(k)) {
                            dp[i][j].set(k ^ val);
                        }
                    }
                }
                
                // Transition from left cell (i, j - 1)
                if (j > 0) {
                    for (int k = 0; k < 1024; ++k) {
                        if (dp[i][j - 1].test(k)) {
                            dp[i][j].set(k ^ val);
                        }
                    }
                }
            }
        }
        
        // Find the minimum XOR sum reachable at (m - 1, n - 1)
        for (int k = 0; k < 1024; ++k) {
            if (dp[m - 1][n - 1].test(k)) {
                return k;
            }
        }
        
        return 0;
    }
};