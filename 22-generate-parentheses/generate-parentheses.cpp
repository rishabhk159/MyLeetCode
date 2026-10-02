class Solution {
public:

    void backtrack(int open, int close, int n,
                   string& current, vector<string>& result) {

        // If we used all parentheses
        if (current.size() == 2 * n) {
            result.push_back(current);
            return;
        }

        // Add opening bracket
        if (open < n) {
            current.push_back('(');

            backtrack(open + 1, close, n, current, result);

            // Undo the choice
            current.pop_back();
        }

        // Add closing bracket
        if (close < open) {
            current.push_back(')');

            backtrack(open, close + 1, n, current, result);

            // Undo the choice
            current.pop_back();
        }
    }

    vector<string> generateParenthesis(int n) {
        vector<string> result;
        string current;

        backtrack(0, 0, n, current, result);

        return result;
    }
};