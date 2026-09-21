class Solution {
public:
    int maxRotateFunction(vector<int>& nums) {
        // Fast I/O
        ios_base::sync_with_stdio(false);
        cin.tie(nullptr);

        int n = nums.size();
        long long sum = 0;
        long long f = 0;

        // Compute sum of elements and initial F(0)
        for (int i = 0; i < n; ++i) {
            sum += nums[i];
            f += 1LL * i * nums[i];
        }

        long long max_val = f;

        // Relation: F(k) = F(k - 1) + sum - n * nums[n - k]
        for (int i = 1; i < n; ++i) {
            f = f + sum - 1LL * n * nums[n - i];
            if (f > max_val) {
                max_val = f;
            }
        }

        return max_val;
    }
};