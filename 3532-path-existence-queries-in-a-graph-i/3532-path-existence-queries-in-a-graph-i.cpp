#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

class Solution {
public:
    vector<bool> pathExistenceQueries(int n, vector<int>& nums, int maxDiff, vector<vector<int>>& queries) {
        // Step 1: Group nodes into connected components
        vector<int> component(n, 0);
        int current_id = 0;
        
        for (int i = 1; i < n; ++i) {
            // Since nums is sorted, nums[i] >= nums[i-1]
            if (nums[i] - nums[i - 1] > maxDiff) {
                current_id++; // Found a gap; start a new connected component
            }
            component[i] = current_id;
        }
        
        // Step 2: Answer each query in O(1) time
        vector<bool> answer;
        answer.reserve(queries.size());
        
        for (const auto& query : queries) {
            int u = query[0];
            int v = query[1];
            answer.push_back(component[u] == component[v]);
        }
        
        return answer;
    }
};