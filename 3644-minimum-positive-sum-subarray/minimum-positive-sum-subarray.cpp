#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

class Solution {
public:
    int minimumSumSubarray(vector<int>& nums, int l, int r) {
        int n = nums.size();
        int min_sum = INT_MAX;

        for (int i = 0; i < n; ++i) {
            int current_sum = 0;
            // Expand subarray up to maximum allowed length r or end of array
            for (int j = i; j < n && j - i + 1 <= r; ++j) {
                current_sum += nums[j];
                int len = j - i + 1;
                
                // Check if length is at least l and sum is strictly positive
                if (len >= l && current_sum > 0) {
                    min_sum = min(min_sum, current_sum);
                }
            }
        }

        return (min_sum == INT_MAX) ? -1 : min_sum;
    }
};
