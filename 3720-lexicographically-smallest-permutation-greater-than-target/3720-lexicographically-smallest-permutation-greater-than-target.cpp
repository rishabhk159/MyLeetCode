class Solution {
public:
    string lexGreaterPermutation(string s, string target) {
        int n = s.size();

        // Frequency of characters in s
        vector<int> cnt(26, 0);
        for (char c : s) {
            cnt[c - 'a']++;
        }

        string prefix;

        for (int i = 0; i < n; i++) {
            int t = target[i] - 'a';

            // We cannot continue matching target here.
            if (cnt[t] == 0) {
                // Find the smallest character greater than target[i]
                for (int c = t + 1; c < 26; c++) {
                    if (cnt[c] > 0) {
                        string ans = prefix;
                        ans += char('a' + c);
                        cnt[c]--;

                        // Put all remaining characters in sorted order
                        for (int x = 0; x < 26; x++) {
                            ans += string(cnt[x], char('a' + x));
                        }

                        return ans;
                    }
                }

                // No greater character at this position.
                // Need to backtrack.
                break;
            }

            // Match target[i]
            prefix += target[i];
            cnt[t]--;
        }

        /*
         * We either:
         * 1. Matched the whole target, or
         * 2. Got stuck at some position.
         *
         * Backtrack through the matched prefix.
         */

        for (int i = (int)prefix.size() - 1; i >= 0; i--) {
            // Restore the character used at prefix[i]
            int current = prefix[i] - 'a';
            cnt[current]++;

            // We want the smallest character > prefix[i]
            for (int c = current + 1; c < 26; c++) {
                if (cnt[c] > 0) {
                    string ans = prefix.substr(0, i);
                    ans += char('a' + c);
                    cnt[c]--;

                    // Remaining characters in sorted order
                    for (int x = 0; x < 26; x++) {
                        ans += string(cnt[x], char('a' + x));
                    }

                    return ans;
                }
            }
        }

        return "";
    }
};