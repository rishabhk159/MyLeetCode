class Solution {
public:
    int maximumLength(vector<int>& nums) {
        unordered_map<long long, int> mp;
        for (int x : nums) mp[x]++;

        int ans = 1;

        // Handle number 1 separately
        if (mp.count(1)) {
            ans = max(ans, mp[1] - (mp[1] % 2 == 0));
        }

        for (auto &[x, f] : mp) {
            if (x == 1) continue;

            long long cur = x;
            int len = 0;

            while (true) {
                if (mp[cur] >= 2) {
                    len += 2;

                    // Prevent overflow
                    if (cur > 1000000000LL / cur) {
                        len--;   // Use one copy as center
                        break;
                    }

                    long long nxt = cur * cur;

                    if (!mp.count(nxt)) {
                        len--;   // Current value becomes center
                        break;
                    }

                    cur = nxt;
                } else if (mp[cur] == 1) {
                    len++;       // Current value is center
                    break;
                } else {
                    break;
                }
            }

            ans = max(ans, len);
        }

        return ans;
    }
};