class Solution {
public:
    bool isGood(vector<int>& nums) {
        int n = *max_element(nums.begin(), nums.end());

        if (nums.size() != n + 1)
            return false;

        sort(nums.begin(), nums.end());

        for (int i = 1; i < n; i++) {
            if (nums[i - 1] != i)
                return false;
        }

        return nums[n - 1] == n && nums[n] == n;
    }
};