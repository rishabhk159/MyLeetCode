#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

class Solution {
public:
    int maxSelectedElements(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        
        // dp[v] stores the max length of a consecutive sequence ending at v
        // Since nums[i] <= 10^6, a vector of size 10^6 + 2 is faster than unordered_map
        int max_val = nums.back();
        vector<int> dp(max_val + 2, 0);
        
        int ans = 0;
        for (int x : nums) {
            // Update x + 1 first so it doesn't reuse the current x's update for dp[x]
            dp[x + 1] = dp[x] + 1;
            dp[x] = dp[x - 1] + 1;
            
            ans = max({ans, dp[x], dp[x + 1]});
        }
        
        return ans;
    }
};