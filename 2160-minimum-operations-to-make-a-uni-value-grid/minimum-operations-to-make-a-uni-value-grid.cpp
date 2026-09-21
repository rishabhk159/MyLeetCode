class Solution {
public:
    int minOperations(vector<vector<int>>& grid, int x) {
        // Fast I/O
        ios_base::sync_with_stdio(false);
        cin.tie(nullptr);

        int m = grid.size();
        int n = grid[0].size();
        int total = m * n;

        vector<int> nums;
        nums.reserve(total);

        int mod = grid[0][0] % x;
        if (mod < 0) mod += x;

        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                int val = grid[i][j];
                int curMod = val % x;
                if (curMod < 0) curMod += x;

                // All numbers must have the same remainder modulo x
                if (curMod != mod) return -1;

                nums.push_back(val);
            }
        }

        // Quickselect to find the median in O(N) average time
        int mid = total / 2;
        nth_element(nums.begin(), nums.begin() + mid, nums.end());
        int median = nums[mid];

        int operations = 0;
        for (int val : nums) {
            operations += abs(val - median) / x;
        }

        return operations;
    }
};