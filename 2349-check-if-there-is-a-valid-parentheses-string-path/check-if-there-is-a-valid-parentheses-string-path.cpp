class Solution {
public:
    bool hasValidPath(vector<vector<char>>& grid) {
        int m = grid.size();
        int n = grid[0].size();

        // A valid parentheses string must have even length.
        int len = m + n - 1;
        if (len % 2 == 1) {
            return false;
        }

        // dp[j][balance] = can we reach current row's cell (i,j)
        // with this balance?
        vector<vector<bool>> dp(n, vector<bool>(len + 1, false));

        // Starting cell must be '('.
        if (grid[0][0] == ')') {
            return false;
        }

        dp[0][1] = true;

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {

                if (i == 0 && j == 0) {
                    continue;
                }

                int change = (grid[i][j] == '(') ? 1 : -1;

                vector<bool> current(len + 1, false);

                // From the cell above
                if (i > 0) {
                    for (int balance = 0; balance <= len; balance++) {
                        if (!dp[j][balance]) {
                            continue;
                        }

                        int newBalance = balance + change;

                        if (newBalance >= 0 && newBalance <= len) {
                            current[newBalance] = true;
                        }
                    }
                }

                // From the cell on the left
                if (j > 0) {
                    for (int balance = 0; balance <= len; balance++) {
                        if (!dp[j - 1][balance]) {
                            continue;
                        }

                        int newBalance = balance + change;

                        if (newBalance >= 0 && newBalance <= len) {
                            current[newBalance] = true;
                        }
                    }
                }

                dp[j] = current;
            }
        }

        // Valid parentheses string must finish with balance 0.
        return dp[n - 1][0];
    }
};