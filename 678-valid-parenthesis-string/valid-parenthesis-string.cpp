class Solution {
public:
    bool checkValidString(string s) {
        int low = 0;
        int high = 0;

        for (char c : s) {
            if (c == '(') {
                low++;
                high++;
            }
            else if (c == ')') {
                low--;
                high--;
            }
            else { // '*'
                low--;   // '*' acts as ')'
                high++;  // '*' acts as '('
            }

            // Even the maximum possible '(' count is negative
            if (high < 0)
                return false;

            // '*' can be empty, so low cannot be negative
            low = max(0, low);
        }

        // Valid only if we can have exactly 0 unmatched '('
        return low == 0;
    }
};