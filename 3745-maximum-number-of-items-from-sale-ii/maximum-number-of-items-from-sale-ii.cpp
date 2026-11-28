#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int maximumSaleItems(vector<vector<int>>& items, int budget) {
        int n = items.size();
        vector<int> freq(n + 1, 0);
        for (const auto& item : items) {
            freq[item[0]]++;
        }
        
        // mult_count[f] = total number of items whose factor is divisible by f
        vector<int> mult_count(n + 1, 0);
        for (int f = 1; f <= n; ++f) {
            if (freq[f] == 0) continue;
            for (int m = f; m <= n; m += f) {
                mult_count[f] += freq[m];
            }
        }
        
        struct Bundle {
            long long price;
            long long limit;
            int gain;
        };
        
        vector<Bundle> bundles;
        bundles.reserve(2 * n);
        
        for (const auto& item : items) {
            int f = item[0];
            long long p = item[1];
            int max_free = mult_count[f] - 1;
            
            if (max_free > 0) {
                bundles.push_back({p, max_free, 2});
            }
            // Unlimited copies yielding 1 item each (bounded by budget / p)
            if (budget >= p) {
                bundles.push_back({p, budget / p, 1});
            }
        }
        
        // Sort by price / gain ascending -> p1 / g1 < p2 / g2  <=>  p1 * g2 < p2 * g1
        sort(bundles.begin(), bundles.end(), [](const Bundle& a, const Bundle& b) {
            return a.price * b.gain < b.price * a.gain;
        });
        
        long long rem_budget = budget;
        long long total_items = 0;
        
        for (const auto& b : bundles) {
            if (rem_budget < b.price) continue;
            long long can_buy = min(b.limit, rem_budget / b.price);
            total_items += can_buy * b.gain;
            rem_budget -= can_buy * b.price;
        }
        
        return static_cast<int>(total_items);
    }
};