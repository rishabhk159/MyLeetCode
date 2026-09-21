class Solution {
public:
    vector<long long> resultArray(vector<int>& nums, int k) {
        // Fast I/O
        ios_base::sync_with_stdio(false);
        cin.tie(nullptr);

        vector<long long> result(k, 0);
        // dp[r] represents the count of subarrays ending at current index with product % k == r
        long long dp[5] = {0};

        for (int num : nums) {
            int val = num % k;
            long long next_dp[5] = {0};

            // Start a new subarray with the single element 'num'
            next_dp[val]++;

            // Extend previously existing subarrays
            for (int r = 0; r < k; ++r) {
                if (dp[r] > 0) {
                    next_dp[(r * val) % k] += dp[r];
                }
            }

            // Accumulate to the global remainder count
            for (int r = 0; r < k; ++r) {
                result[r] += next_dp[r];
                dp[r] = next_dp[r];
            }
        }

        return result;
    }
};