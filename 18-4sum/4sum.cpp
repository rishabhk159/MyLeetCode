class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        // Fast I/O
        ios_base::sync_with_stdio(false);
        cin.tie(nullptr);

        int n = nums.size();
        if (n < 4) return {};

        sort(nums.begin(), nums.end());
        vector<vector<int>> result;

        for (int i = 0; i < n - 3; ++i) {
            // Skip duplicates for the first element
            if (i > 0 && nums[i] == nums[i - 1]) continue;

            // Early pruning: minimum possible sum with nums[i] exceeds target
            long long min1 = (long long)nums[i] + nums[i + 1] + nums[i + 2] + nums[i + 3];
            if (min1 > target) break;

            // Early pruning: maximum possible sum with nums[i] is less than target
            long long max1 = (long long)nums[i] + nums[n - 1] + nums[n - 2] + nums[n - 3];
            if (max1 < target) continue;

            for (int j = i + 1; j < n - 2; ++j) {
                // Skip duplicates for the second element
                if (j > i + 1 && nums[j] == nums[j - 1]) continue;

                // Early pruning for the second element
                long long min2 = (long long)nums[i] + nums[j] + nums[j + 1] + nums[j + 2];
                if (min2 > target) break;

                long long max2 = (long long)nums[i] + nums[j] + nums[n - 1] + nums[n - 2];
                if (max2 < target) continue;

                int left = j + 1;
                int right = n - 1;
                long long rem = (long long)target - nums[i] - nums[j];

                while (left < right) {
                    int sum = nums[left] + nums[right];
                    if (sum == rem) {
                        result.push_back({nums[i], nums[j], nums[left], nums[right]});

                        // Skip duplicates for two-pointer window
                        while (left < right && nums[left] == nums[left + 1]) ++left;
                        while (left < right && nums[right] == nums[right - 1]) --right;

                        ++left;
                        --right;
                    } else if (sum < rem) {
                        ++left;
                    } else {
                        --right;
                    }
                }
            }
        }

        return result;
    }
};