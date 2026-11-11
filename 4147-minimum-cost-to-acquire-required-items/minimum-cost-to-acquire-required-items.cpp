
class Solution {
public:
    long long minimumCost(int cost1, int cost2, int costBoth, int need1, int need2) {
        
        long long a = need1;
        long long b = need2;

        // Option 1: Buy individual items only
        long long costA = a * cost1 + b * cost2;

        // Option 2: Buy common items using type 3
        long long common = min(a, b);

        long long costB = common * costBoth
                        + (a - common) * cost1
                        + (b - common) * cost2;

        // Option 3: Buy only type 3 items
        long long costC = max(a, b) * costBoth;

        return min({costA, costB, costC});
    }
};
