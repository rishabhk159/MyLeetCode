class Solution {
public:
    int uniqueXorTriplets(vector<int>& nums) {
        const int MAXX = 2048;

        vector<vector<bool>> dp(4, vector<bool>(MAXX, false));
        dp[0][0] = true;

        for (int x : nums) {
            for (int k = 2; k >= 0; k--) {
                for (int v = 0; v < MAXX; v++) {
                    if (dp[k][v])
                        dp[k + 1][v ^ x] = true;
                }
            }
        }

        vector<bool> ans(MAXX, false);

        // x^x^x = x and x^x^y = y
        for (int x : nums)
            ans[x] = true;

        // XOR of three distinct elements
        for (int v = 0; v < MAXX; v++)
            if (dp[3][v])
                ans[v] = true;

        int res = 0;
        for (bool x : ans)
            if (x) res++;

        return res;
    }
};