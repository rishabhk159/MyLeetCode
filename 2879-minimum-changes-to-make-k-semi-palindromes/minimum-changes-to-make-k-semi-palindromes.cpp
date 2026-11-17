class Solution {
public:
    int minimumChanges(string s, int k) {
        int n = s.length();
        
        // Precompute proper divisors for all possible substring lengths
        vector<vector<int>> divisors(n + 1);
        for (int len = 2; len <= n; ++len) {
            for (int d = 1; d * d <= len; ++d) {
                if (len % d == 0) {
                    divisors[len].push_back(d);
                    if (d != 1 && d * d != len) {
                        divisors[len].push_back(len / d);
                    }
                }
            }
        }
        
        // cost[i][j] = min changes to make s[i..j] a semi-palindrome
        vector<vector<int>> cost(n, vector<int>(n, 1e9));
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                int len = j - i + 1;
                for (int d : divisors[len]) {
                    int changes = 0;
                    int group_len = len / d;
                    // Check each of the d groups
                    for (int rem = 0; rem < d; ++rem) {
                        int left = i + rem;
                        int right = i + rem + (group_len - 1) * d;
                        while (left < right) {
                            if (s[left] != s[right]) {
                                ++changes;
                            }
                            left += d;
                            right -= d;
                        }
                    }
                    cost[i][j] = min(cost[i][j], changes);
                }
            }
        }
        
        // dp[p][i] = min changes to partition prefix of length i into p semi-palindromes
        vector<vector<int>> dp(k + 1, vector<int>(n + 1, 1e9));
        dp[0][0] = 0;
        
        for (int p = 1; p <= k; ++p) {
            for (int i = 2 * p; i <= n; ++i) {
                for (int j = 2 * (p - 1); j <= i - 2; ++j) {
                    dp[p][i] = min(dp[p][i], dp[p - 1][j] + cost[j][i - 1]);
                }
            }
        }
        
        return dp[k][n];
    }
};