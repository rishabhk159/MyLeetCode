class Solution {
public:
    int minOperations(vector<vector<int>>& grid, int x) {
        vector<int> nums;

        int m = grid.size();
        int n = grid[0].size();

        // Flatten the grid
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                nums.push_back(grid[i][j]);
            }
        }

        // Sort the elements
        sort(nums.begin(), nums.end());

        // All elements must have the same remainder modulo x
        int mod = nums[0] % x;

        for (int num : nums) {
            if (num % x != mod) {
                return -1;
            }
        }

        // Median minimizes the sum of absolute differences
        int median = nums[nums.size() / 2];

        int operations = 0;

        for (int num : nums) {
            operations += abs(num - median) / x;
        }

        return operations;
    }
};