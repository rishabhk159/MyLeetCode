#include <vector>
#include <numeric>
#include <algorithm>

class Solution {
public:
    int minMoves(vector<int>& nums) {
        int max_val = *max_element(nums.begin(), nums.end());
        int total_moves = 0;
        
        for (int x : nums) {
            total_moves += (max_val - x);
        }
        
        return total_moves;
    }
};