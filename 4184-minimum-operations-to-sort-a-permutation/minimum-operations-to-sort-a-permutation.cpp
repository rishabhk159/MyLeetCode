class Solution {
public:
    int minOperations(vector<int>& nums) {
        int n = nums.size();
        if (n <= 1) return 0;

        // Locate the position of 0
        int zero = 0;
        for (int i = 0; i < n; ++i) {
            if (nums[i] == 0) {
                zero = i;
                break;
            }
        }

        // Helper to verify cyclic order starting at 'zero'
        auto check = [&](int step) {
            for (int i = 1; i < n; ++i) {
                int prev = (zero + (i - 1) * step % n + n) % n;
                int curr = (zero + i * step % n + n) % n;
                if (nums[prev] > nums[curr]) {
                    return false;
                }
            }
            return true;
        };

        int ans = INT_MAX;

        // Case 1: Cyclically Ascending
        if (check(1)) {
            ans = min(ans, zero);
            if (zero > 0) {
                ans = min(ans, n - zero + 2);
            }
        }

        // Case 2: Cyclically Descending
        if (check(-1)) {
            ans = min(ans, (zero + 1) % n + 1);
            ans = min(ans, n - zero);
        }

        return ans == INT_MAX ? -1 : ans;
    }
};