#include <vector>
#include <deque>

using namespace std;

class Solution {
public:
    long long countNonDecreasingSubarrays(vector<int>& nums, int k) {
        int n = nums.size();
        long long ans = 0;
        long long cost = 0;
        
        // Monotonic decreasing deque storing {running_max_value, block_length}
        deque<pair<long long, int>> dq;
        
        int r = n - 1;
        for (int l = n - 1; l >= 0; --l) {
            long long val = nums[l];
            int cnt = 1;
            
            // Merge all smaller or equal blocks on the left into the new running max
            while (!dq.empty() && dq.back().first <= val) {
                auto [prev_val, prev_cnt] = dq.back();
                dq.pop_back();
                cost += (val - prev_val) * prev_cnt;
                cnt += prev_cnt;
            }
            dq.push_back({val, cnt});
            
            // Shrink window from the right until cost <= k
            while (cost > k) {
                cost -= (dq.front().first - nums[r]);
                dq.front().second--;
                if (dq.front().second == 0) {
                    dq.pop_front();
                }
                --r;
            }
            
            // All subarrays starting at l and ending at any index in [l, r] are valid
            ans += (r - l + 1);
        }
        
        return ans;
    }
};