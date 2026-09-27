class Solution {
public:
    // Returns:
    // first  = number of valid numbers
    // second = total waviness of those numbers
    pair<long long, long long> dp[20][2][2][11][11];
    bool vis[20][2][2][11][11];

    vector<int> digits;

    pair<long long, long long> solve(int pos,
                                     int tight,
                                     int started,
                                     int prevPrev,
                                     int prev) {
        if (pos == digits.size()) {
            return {1, 0};
        }

        if (vis[pos][tight][started][prevPrev][prev]) {
            return dp[pos][tight][started][prevPrev][prev];
        }

        vis[pos][tight][started][prevPrev][prev] = true;

        long long ways = 0;
        long long total = 0;

        int limit = tight ? digits[pos] : 9;

        for (int cur = 0; cur <= limit; cur++) {
            int newTight = tight && (cur == limit);

            // Still skipping leading zeroes
            if (!started && cur == 0) {
                auto res = solve(pos + 1,
                                 newTight,
                                 0,
                                 10,
                                 10);

                ways += res.first;
                total += res.second;
            }
            else if (!started) {
                // First actual digit
                auto res = solve(pos + 1,
                                 newTight,
                                 1,
                                 10,
                                 cur);

                ways += res.first;
                total += res.second;
            }
            else {
                // Check whether prev is a peak or valley
                int add = 0;

                if (prevPrev != 10) {
                    if ((prev > prevPrev && prev > cur) ||
                        (prev < prevPrev && prev < cur)) {
                        add = 1;
                    }
                }

                auto res = solve(pos + 1,
                                 newTight,
                                 1,
                                 prev,
                                 cur);

                ways += res.first;
                total += res.second + res.first * add;
            }
        }

        return dp[pos][tight][started][prevPrev][prev] = {ways, total};
    }

    long long calculate(long long x) {
        if (x <= 0) {
            return 0;
        }

        digits.clear();

        while (x > 0) {
            digits.push_back(x % 10);
            x /= 10;
        }

        reverse(digits.begin(), digits.end());

        memset(vis, false, sizeof(vis));

        return solve(0, 1, 0, 10, 10).second;
    }

    long long totalWaviness(long long num1, long long num2) {
        return calculate(num2) - calculate(num1 - 1);
    }
};