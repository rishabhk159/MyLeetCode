class Solution {
public:
    long long findKthSmallest(vector<int>& coins, int k) {
        // Remove coins that are multiples of another smaller coin.
        sort(coins.begin(), coins.end());

        vector<int> c;

        for (int x : coins) {
            bool redundant = false;

            for (int y : c) {
                if (x % y == 0) {
                    redundant = true;
                    break;
                }
            }

            if (!redundant)
                c.push_back(x);
        }

        int n = c.size();

        // Count how many numbers <= x are divisible by
        // at least one coin.
        auto count = [&](long long x) -> long long {
            long long ans = 0;

            for (int mask = 1; mask < (1 << n); mask++) {
                long long lcm = 1;
                int bits = 0;
                bool overflow = false;

                for (int i = 0; i < n; i++) {
                    if (mask & (1 << i)) {
                        bits++;

                        long long g = std::gcd(lcm, (long long)c[i]);

                        // lcm = lcm / gcd * c[i]
                        lcm = lcm / g * c[i];

                        if (lcm > x) {
                            overflow = true;
                            break;
                        }
                    }
                }

                if (overflow)
                    continue;

                long long contribution = x / lcm;

                if (bits % 2 == 1)
                    ans += contribution;
                else
                    ans -= contribution;
            }

            return ans;
        };

        // The answer cannot be larger than k * minimum coin.
        long long low = 1;
        long long high = 1LL * (*min_element(c.begin(), c.end())) * k;

        while (low < high) {
            long long mid = low + (high - low) / 2;

            if (count(mid) >= k)
                high = mid;
            else
                low = mid + 1;
        }

        return low;
    }
};