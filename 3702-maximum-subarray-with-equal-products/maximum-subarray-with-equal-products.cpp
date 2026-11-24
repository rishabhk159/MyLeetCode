#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

class Solution {
public:
    int maxLength(vector<int>& nums) {
        int n = nums.size();
        int maxLen = 1; // Any subarray of length 1 trivially satisfies a == a * a? Wait: a != a*a unless a=1, 
                        // though problem guarantees length >= 2 and any length 2 subarray is valid.
        
        // Max possible lcm(1..10) * max(nums) = 2520 * 10 = 25200
        const long long MAX_LIMIT = 25200;

        for (int i = 0; i < n; ++i) {
            long long prod = 1;
            long long current_gcd = 0;
            long long current_lcm = 1;

            for (int j = i; j < n; ++j) {
                prod *= nums[j];
                
                // If product exceeds the maximum possible value of (lcm * gcd), stop extending
                if (prod > MAX_LIMIT) {
                    break;
                }

                current_gcd = gcd(current_gcd, (long long)nums[j]);
                current_lcm = lcm(current_lcm, (long long)nums[j]);

                if (prod == current_lcm * current_gcd) {
                    maxLen = max(maxLen, j - i + 1);
                }
            }
        }

        return maxLen;
    }
};