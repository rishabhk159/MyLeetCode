class Solution {
public:
    int reverseDegree(string s) {
        // Fast I/O
        ios_base::sync_with_stdio(false);
        cin.tie(nullptr);

        int total = 0;
        int n = s.length();

        for (int i = 0; i < n; ++i) {
            // 'a' -> 26, 'b' -> 25, ..., 'z' -> 1
            int rev_char_val = 26 - (s[i] - 'a');
            // 1-indexed position in string is (i + 1)
            total += rev_char_val * (i + 1);
        }

        return total;
    }
};