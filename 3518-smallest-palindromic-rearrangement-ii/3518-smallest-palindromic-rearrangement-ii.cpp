class Solution {
public:
    static const int LIMIT = 1000001;
    vector<vector<int>> C;

    void build(int n) {
        C.assign(n + 1, vector<int>());
        for (int i = 0; i <= n; i++) {
            C[i].resize(i + 1);
            C[i][0] = C[i][i] = 1;
            for (int j = 1; j < i; j++) {
                long long val = (long long)C[i - 1][j - 1] + C[i - 1][j];
                C[i][j] = min((long long)LIMIT, val);
            }
        }
    }

    long long countWays(vector<int> &cnt, int len) {
        long long ways = 1;
        int rem = len;

        for (int i = 0; i < 26; i++) {
            if (cnt[i] == 0) continue;
            ways *= C[rem][cnt[i]];
            if (ways > LIMIT) ways = LIMIT;
            rem -= cnt[i];
        }

        return ways;
    }

    string smallestPalindrome(string s, int k) {
        vector<int> freq(26, 0);

        for (char c : s)
            freq[c - 'a']++;

        vector<int> half(26, 0);
        string mid = "";

        int len = 0;

        for (int i = 0; i < 26; i++) {
            half[i] = freq[i] / 2;
            len += half[i];

            if (freq[i] & 1)
                mid.push_back(char('a' + i));
        }

        build(len);

        if (countWays(half, len) < k)
            return "";

        string first = "";

        while (len) {

            for (int c = 0; c < 26; c++) {

                if (half[c] == 0)
                    continue;

                half[c]--;

                long long ways = countWays(half, len - 1);

                if (ways >= k) {
                    first.push_back(char('a' + c));
                    len--;
                    break;
                }

                k -= ways;
                half[c]++;
            }
        }

        string second = first;
        reverse(second.begin(), second.end());

        return first + mid + second;
    }
};