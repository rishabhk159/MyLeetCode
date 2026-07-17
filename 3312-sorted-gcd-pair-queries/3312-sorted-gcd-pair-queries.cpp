class Solution {
public:
    vector<int> gcdValues(vector<int>& nums, vector<long long>& queries) {
        int mx = *max_element(nums.begin(), nums.end());

        vector<int> freq(mx + 1, 0);
        for (int x : nums) freq[x]++;

        vector<long long> divisible(mx + 1, 0);

        // divisible[g] = count of numbers divisible by g
        for (int g = 1; g <= mx; g++) {
            for (int multiple = g; multiple <= mx; multiple += g) {
                divisible[g] += freq[multiple];
            }
        }

        vector<long long> exact(mx + 1, 0);

        // exact[g] = number of pairs whose gcd is exactly g
        for (int g = mx; g >= 1; g--) {
            long long cnt = divisible[g];
            long long pairs = cnt * (cnt - 1) / 2;

            for (int multiple = 2 * g; multiple <= mx; multiple += g) {
                pairs -= exact[multiple];
            }

            exact[g] = pairs;
        }

        // Prefix counts of gcd values in sorted order
        vector<long long> pref(mx + 1, 0);
        for (int g = 1; g <= mx; g++) {
            pref[g] = pref[g - 1] + exact[g];
        }

        vector<int> ans;
        ans.reserve(queries.size());

        for (long long q : queries) {
            // Need smallest gcd value with prefix > q
            int g = lower_bound(pref.begin() + 1, pref.end(), q + 1) - pref.begin();
            ans.push_back(g);
        }

        return ans;
    }
};