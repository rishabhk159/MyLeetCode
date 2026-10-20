#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

class Solution {
public:
    int sortableIntegers(vector<int>& nums) {
        int n = nums.size();
        if (n <= 1) return n;

        // prefMax[i] = max(nums[0..i-1])
        vector<int> prefMax(n + 1, 0);
        for (int i = 0; i < n; i++) {
            prefMax[i + 1] = max(prefMax[i], nums[i]);
        }

        // suffMin[i] = min(nums[i..n-1])
        vector<int> suffMin(n + 1, 1e9);
        for (int i = n - 1; i >= 0; i--) {
            suffMin[i] = min(suffMin[i + 1], nums[i]);
        }

        // prefDrop[i] = number of adjacent drops in nums[0..i]
        vector<int> prefDrop(n, 0);
        for (int i = 1; i < n; i++) {
            prefDrop[i] = prefDrop[i - 1] + (nums[i - 1] > nums[i] ? 1 : 0);
        }

        int totalSortableSum = 0;

        // Check each possible divisor k of n
        for (int k = 1; k <= n; k++) {
            if (n % k != 0) continue;

            bool valid = true;

            // Check each block of size k
            for (int start = 0; start < n; start += k) {
                int end = start + k;

                // 1. Check boundary with next block
                if (end < n && prefMax[end] > suffMin[end]) {
                    valid = false;
                    break;
                }

                // 2. Check if the block has at most 1 cyclic descent
                if (k > 1) {
                    // Drops inside nums[start .. end-1]
                    int internalDrops = prefDrop[end - 1] - prefDrop[start];
                    // Drop wrapping from end-1 to start
                    int wrapDrop = (nums[end - 1] > nums[start] ? 1 : 0);
                    
                    if (internalDrops + wrapDrop > 1) {
                        valid = false;
                        break;
                    }
                }
            }

            if (valid) {
                totalSortableSum += k;
            }
        }

        return totalSortableSum;
    }
};