class Solution {
    // Array of string views/literals avoids vector allocation overhead
    const string mapping[10] = {
        "",     "",     "abc",  "def",
        "ghi",  "jkl",  "mno",  "pqrs",
        "tuv",  "wxyz"
    };

    void backtrack(int index, const string& digits, string& current, vector<string>& result) {
        if (index == digits.size()) {
            result.push_back(current);
            return;
        }

        const string& letters = mapping[digits[index] - '0'];
        for (char ch : letters) {
            current[index] = ch; // In-place overwrite avoids push_back/pop_back
            backtrack(index + 1, digits, current, result);
        }
    }

public:
    vector<string> letterCombinations(string digits) {
        if (digits.empty()) return {};

        // Fast I/O to shave off LeetCode harness overhead
        ios_base::sync_with_stdio(false);
        cin.tie(nullptr);

        int total = 1;
        for (char d : digits) {
            total *= mapping[d - '0'].size();
        }

        vector<string> result;
        result.reserve(total); // Pre-allocate exact capacity to avoid reallocations

        string current(digits.size(), ' ');
        backtrack(0, digits, current, result);
        return result;
    }
};