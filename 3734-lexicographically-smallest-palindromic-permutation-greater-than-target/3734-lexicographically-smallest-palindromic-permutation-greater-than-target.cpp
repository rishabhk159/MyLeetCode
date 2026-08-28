class Solution {
public:
    string lexPalindromicPermutation(string s, string target) {
        int n = s.size();

        // Count characters
        vector<int> freq(26, 0);
        for (char c : s)
            freq[c - 'a']++;

        // A palindrome can have at most one odd-frequency character
        int odd = 0;
        char mid = 0;

        for (int i = 0; i < 26; i++) {
            if (freq[i] % 2) {
                odd++;
                mid = char('a' + i);
            }
        }

        if (odd > 1)
            return "";

        int half = n / 2;

        // Characters available for the left half
        vector<int> cnt(26);
        for (int i = 0; i < 26; i++)
            cnt[i] = freq[i] / 2;

        // Construct complete palindrome from left half
        auto build = [&](const string& left) {
            string ans = left;

            if (n % 2)
                ans += mid;

            for (int i = half - 1; i >= 0; i--)
                ans += left[i];

            return ans;
        };

        /*
         * Try to make the left half equal to target's left half.
         */
        string prefix;
        int pos = 0;

        while (pos < half) {
            int x = target[pos] - 'a';

            if (cnt[x] == 0)
                break;

            prefix += target[pos];
            cnt[x]--;
            pos++;
        }

        /*
         * Case 1:
         * We matched the complete left half.
         *
         * The palindrome formed from it might already be
         * strictly greater than target.
         */
        if (pos == half) {
            string candidate = build(prefix);

            if (candidate > target)
                return candidate;
        }

        /*
         * Case 2:
         *
         * At the current position, try putting the smallest
         * character greater than target[pos].
         */
        if (pos < half) {
            int x = target[pos] - 'a';

            for (int c = x + 1; c < 26; c++) {
                if (cnt[c] > 0) {
                    string left = prefix;
                    left += char('a' + c);

                    cnt[c]--;

                    // Fill remaining positions as small as possible
                    for (int j = 0; j < 26; j++) {
                        left += string(cnt[j], char('a' + j));
                    }

                    return build(left);
                }
            }
        }

        /*
         * If we couldn't increase at the current position,
         * backtrack.
         *
         * Restore characters one by one and try to increase
         * an earlier position.
         */
        for (int i = (int)prefix.size() - 1; i >= 0; i--) {
            int current = prefix[i] - 'a';

            // Restore the character used at position i
            cnt[current]++;

            // Try the smallest character greater than target[i]
            for (int c = current + 1; c < 26; c++) {
                if (cnt[c] > 0) {
                    string left = prefix.substr(0, i);
                    left += char('a' + c);

                    cnt[c]--;

                    // Fill the rest in lexicographically smallest order
                    for (int j = 0; j < 26; j++) {
                        left += string(cnt[j], char('a' + j));
                    }

                    return build(left);
                }
            }
        }

        return "";
    }
};