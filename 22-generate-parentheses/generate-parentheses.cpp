class Solution {
    void backtrack(int open, int close, int n, string& current, vector<string>& result) {
        if (current.size() == 2 * n) {
            result.push_back(current);
            return;
        }

        if (open < n) {
            current.push_back('(');
            backtrack(open + 1, close, n, current, result);
            current.pop_back();
        }

        if (close < open) {
            current.push_back(')');
            backtrack(open, close + 1, n, current, result);
            current.pop_back();
        }
    }

public:
    vector<string> generateParenthesis(int n) {
        // Fast I/O
        ios_base::sync_with_stdio(false);
        cin.tie(nullptr);

        // Pre-allocate Catalan number capacity to eliminate vector reallocations
        // C_n for n = 1..8: {1, 2, 5, 14, 42, 132, 429, 1430}
        const int catalan[] = {0, 1, 2, 5, 14, 42, 132, 429, 1430};

        vector<string> result;
        result.reserve(catalan[n]);

        string current = "";
        current.reserve(2 * n);

        backtrack(0, 0, n, current, result);
        return result;
    }
};