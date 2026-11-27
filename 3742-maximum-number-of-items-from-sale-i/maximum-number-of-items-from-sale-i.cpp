#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int maximumSaleItems(vector<vector<int>>& items, int budget) {
        const int MAX_VAL = 1500;
        vector<int> freq(MAX_VAL + 1, 0);
        int min_price = MAX_VAL + 1;
        
        // Count frequency of each factor and find the global minimum price
        for (const auto& item : items) {
            freq[item[0]]++;
            min_price = min(min_price, item[1]);
        }
        
        // Precompute number of divisible items for each factor value
        // div_count[f] = total number of items whose factor is a multiple of f
        vector<int> div_count(MAX_VAL + 1, 0);
        for (int f = 1; f <= MAX_VAL; ++f) {
            if (freq[f] == 0) continue;
            for (int multiple = f; multiple <= MAX_VAL; multiple += f) {
                div_count[f] += freq[multiple];
            }
        }
        
        // 0/1 Knapsack for buying at most 1 copy of each item type
        vector<int> dp(budget + 1, -1);
        dp[0] = 0;
        
        for (const auto& item : items) {
            int factor = item[0];
            int price = item[1];
            // Value = 1 (the item itself) + (div_count[factor] - 1) (free items)
            int value = div_count[factor]; 
            
            for (int c = budget; c >= price; --c) {
                if (dp[c - price] != -1) {
                    dp[c] = max(dp[c], dp[c - price] + value);
                }
            }
        }
        
        // Spend any leftover budget on copies of the cheapest item
        int max_items = 0;
        for (int c = 0; c <= budget; ++c) {
            if (dp[c] != -1) {
                int extra_copies = (budget - c) / min_price;
                max_items = max(max_items, dp[c] + extra_copies);
            }
        }
        
        return max_items;
    }
};