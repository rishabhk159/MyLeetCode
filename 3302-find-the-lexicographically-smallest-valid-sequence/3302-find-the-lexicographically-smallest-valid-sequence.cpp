class Solution {
public:
    vector<int> validSequence(string word1, string word2) {
        int n = word1.size();
        int m = word2.size();

        vector<int> ans(m);

        // last[j] = latest index in word1 where word2[j]
        // can be matched while still matching word2[j...]
        vector<int> last(m, -1);

        int i = n - 1;
        int j = m - 1;

        // Match word2 from right to left.
        while (i >= 0 && j >= 0) {
            if (word1[i] == word2[j]) {
                last[j] = i;
                j--;
            }
            i--;
        }

        // We can use at most one mismatch.
        bool canSkip = true;
        j = 0;

        // Greedily choose the smallest possible indices.
        for (i = 0; i < n; i++) {
            if (j == m)
                break;

            // Case 1: exact match
            if (word1[i] == word2[j]) {
                ans[j] = i;
                j++;
            }

            // Case 2: use our one allowed mismatch
            else if (canSkip &&
                     (j == m - 1 || i < last[j + 1])) {

                ans[j] = i;
                j++;
                canSkip = false;
            }
        }

        if (j == m)
            return ans;

        return {};
    }
};