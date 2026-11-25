#pragma GCC optimize("O3,unroll-loops")
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

class Solution {
private:
    static constexpr long long MOD1 = 1e9 + 7;
    static constexpr long long MOD2 = 1e9 + 9;
    static constexpr long long BASE1 = 1315423911LL % MOD1;
    static constexpr long long BASE2 = 2654435761LL % MOD2;

    struct PairHash {
        size_t operator()(const pair<long long, long long>& p) const {
            return (size_t(p.first) << 32) ^ size_t(p.second);
        }
    };

public:
    int smallestUniqueSubarray(vector<int>& nums) {
        int n = nums.size();
        
        // Precompute powers and prefix hashes for double hashing
        vector<long long> pow1(n + 1, 1), pow2(n + 1, 1);
        vector<long long> pref1(n + 1, 0), pref2(n + 1, 0);
        
        for (int i = 0; i < n; ++i) {
            pow1[i + 1] = (pow1[i] * BASE1) % MOD1;
            pow2[i + 1] = (pow2[i] * BASE2) % MOD2;
            pref1[i + 1] = (pref1[i] * BASE1 + nums[i]) % MOD1;
            pref2[i + 1] = (pref2[i] * BASE2 + nums[i]) % MOD2;
        }
        
        auto getHash = [&](int l, int r) -> pair<long long, long long> {
            int len = r - l + 1;
            long long h1 = (pref1[r + 1] - (pref1[l] * pow1[len]) % MOD1 + MOD1) % MOD1;
            long long h2 = (pref2[r + 1] - (pref2[l] * pow2[len]) % MOD2 + MOD2) % MOD2;
            return {h1, h2};
        };
        
        auto hasUniqueOfLength = [&](int len) -> bool {
            unordered_map<pair<long long, long long>, int, PairHash> freq;
            freq.reserve(n - len + 1);
            
            for (int i = 0; i <= n - len; ++i) {
                freq[getHash(i, i + len - 1)]++;
            }
            
            for (const auto& [hashVal, count] : freq) {
                if (count == 1) return true;
            }
            return false;
        };
        
        int low = 1, high = n, ans = n;
        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (hasUniqueOfLength(mid)) {
                ans = mid;
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }
        
        return ans;
    }
};