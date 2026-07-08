class Solution {
public:
    static const int MOD = 1000000007;

    vector<int> sumAndMultiply(string s, vector<vector<int>>& queries) {
        int n = s.size();

        vector<int> nzPos;
        vector<long long> preSum(1, 0);

        for (int i = 0; i < n; i++) {
            if (s[i] != '0') {
                nzPos.push_back(i);
                preSum.push_back(preSum.back() + (s[i] - '0'));
            }
        }

        int m = nzPos.size();

        vector<long long> pow10(m + 1, 1);
        for (int i = 1; i <= m; i++)
            pow10[i] = (pow10[i - 1] * 10) % MOD;

        vector<long long> preValue(m + 1, 0);
        for (int i = 0; i < m; i++) {
            preValue[i + 1] = (preValue[i] * 10 + (s[nzPos[i]] - '0')) % MOD;
        }

        vector<int> ans;

        for (auto &q : queries) {
            int l = q[0], r = q[1];

            int L = lower_bound(nzPos.begin(), nzPos.end(), l) - nzPos.begin();
            int R = upper_bound(nzPos.begin(), nzPos.end(), r) - nzPos.begin();

            if (L == R) {
                ans.push_back(0);
                continue;
            }

            long long sum = preSum[R] - preSum[L];

            long long x =
                (preValue[R] -
                 preValue[L] * pow10[R - L] % MOD +
                 MOD) % MOD;

            ans.push_back((x * (sum % MOD)) % MOD);
        }

        return ans;
    }
};