class Solution {
public:
    string s;
    int pos = 0;

    unordered_set<string> parseExpr() {
        unordered_set<string> res = parseTerm();

        while (pos < s.size() && s[pos] == ',') {
            pos++;
            auto next = parseTerm();

            for (const string& x : next)
                res.insert(x);
        }

        return res;
    }

    unordered_set<string> parseTerm() {
        unordered_set<string> res;
        res.insert("");

        while (pos < s.size() && s[pos] != '}' && s[pos] != ',') {
            auto cur = parseFactor();

            unordered_set<string> temp;

            for (const string& a : res) {
                for (const string& b : cur) {
                    temp.insert(a + b);
                }
            }

            res.swap(temp);
        }

        return res;
    }

    unordered_set<string> parseFactor() {
        if (s[pos] >= 'a' && s[pos] <= 'z') {
            return {string(1, s[pos++])};
        }

        // '{'
        pos++;
        auto res = parseExpr();
        pos++; // '}'

        return res;
    }

public:
    vector<string> braceExpansionII(string expression) {
        s = expression;
        pos = 0;

        unordered_set<string> st = parseExpr();

        vector<string> ans(st.begin(), st.end());
        sort(ans.begin(), ans.end());

        return ans;
    }
};