class Solution {
public:
    vector<int> maxValue(vector<int>& nums) {
        int n = nums.size();

        // suffixMin[i] = minimum value from i to n-1
        vector<int> suffixMin(n);
        suffixMin[n - 1] = nums[n - 1];

        for (int i = n - 2; i >= 0; i--) {
            suffixMin[i] = min(nums[i], suffixMin[i + 1]);
        }

        vector<int> ans(n);

        int prefixMax = nums[0];
        int start = 0;

        for (int i = 0; i < n - 1; i++) {
            prefixMax = max(prefixMax, nums[i]);

            // No inversion crosses this boundary.
            if (prefixMax <= suffixMin[i + 1]) {
                // [start ... i] is one connected component.
                int mx = prefixMax;

                for (int j = start; j <= i; j++) {
                    ans[j] = mx;
                }

                start = i + 1;
                prefixMax = nums[start];
            }
        }

        // Last component
        int mx = prefixMax;

        for (int i = start; i < n; i++) {
            mx = max(mx, nums[i]);
        }

        for (int i = start; i < n; i++) {
            ans[i] = mx;
        }

        return ans;
    }
};