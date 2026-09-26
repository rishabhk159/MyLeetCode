class Solution {
public:
    int minimumCost(vector<int>& cost) {
        // Sort from highest to lowest
        sort(cost.rbegin(), cost.rend());

        int ans = 0;

        for (int i = 0; i < cost.size(); i++) {
            // Every 3rd candy is free
            if (i % 3 != 2) {
                ans += cost[i];
            }
        }

        return ans;
    }
};