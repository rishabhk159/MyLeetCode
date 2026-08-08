class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        vector<int> last(256, -1);

        int left = 0;
        int ans = 0;

        for (int right = 0; right < s.size(); right++) {
            // If character was already seen inside
            // the current window, move left.
            if (last[s[right]] >= left) {
                left = last[s[right]] + 1;
            }

            last[s[right]] = right;

            ans = max(ans, right - left + 1);
        }

        return ans;
    }
};