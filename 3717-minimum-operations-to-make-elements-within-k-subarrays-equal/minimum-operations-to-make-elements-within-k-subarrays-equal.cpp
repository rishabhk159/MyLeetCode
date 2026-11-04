
class Solution {
public:
    multiset<long long> low, high;
    long long sumLow = 0, sumHigh = 0;

    void add(long long val) {
        if (low.empty() || val <= *low.rbegin()) {
            low.insert(val);
            sumLow += val;
        } else {
            high.insert(val);
            sumHigh += val;
        }
        balance();
    }

    void remove(long long val) {
        auto it = low.find(val);

        if (it != low.end()) {
            low.erase(it);
            sumLow -= val;
        } else {
            it = high.find(val);
            high.erase(it);
            sumHigh -= val;
        }

        balance();
    }

    void balance() {
        while (low.size() > high.size() + 1) {
            auto it = prev(low.end());
            long long val = *it;

            low.erase(it);
            sumLow -= val;

            high.insert(val);
            sumHigh += val;
        }

        while (low.size() < high.size()) {
            auto it = high.begin();
            long long val = *it;

            high.erase(it);
            sumHigh -= val;

            low.insert(val);
            sumLow += val;
        }
    }

    long long getCost() {
        long long median = *low.rbegin();

        long long leftCost =
            median * (long long)low.size() - sumLow;

        long long rightCost =
            sumHigh - median * (long long)high.size();

        return leftCost + rightCost;
    }

    long long minOperations(vector<int>& nums, int x, int k) {
        int n = nums.size();

        vector<long long> cost(n - x + 1);

        // Calculate minimum cost for every window of size x.
        for (int i = 0; i < n; i++) {
            add(nums[i]);

            if (i >= x) {
                remove(nums[i - x]);
            }

            if (i >= x - 1) {
                cost[i - x + 1] = getCost();
            }
        }

        // DP: minimum cost to select j non-overlapping windows
        // from the first i elements.
        const long long INF = LLONG_MAX / 4;

        vector<vector<long long>> dp(
            k + 1, vector<long long>(n + 1, INF)
        );

        dp[0][0] = 0;

        for (int j = 0; j <= k; j++) {
            for (int i = 0; i <= n; i++) {

                if (dp[j][i] == INF)
                    continue;

                // Skip current element.
                if (i < n) {
                    dp[j][i + 1] = min(
                        dp[j][i + 1],
                        dp[j][i]
                    );
                }

                // Select a window starting at i.
                if (j < k && i + x <= n) {
                    dp[j + 1][i + x] = min(
                        dp[j + 1][i + x],
                        dp[j][i] + cost[i]
                    );
                }
            }
        }

        return dp[k][n];
    }
};
