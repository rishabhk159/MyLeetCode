class Solution {
public:
    string evaluate(string s, vector<vector<string>>& knowledge) {
        unordered_map<string, string> mp;

        // Store key-value pairs
        for (auto& k : knowledge) {
            mp[k[0]] = k[1];
        }

        string ans;

        for (int i = 0; i < s.size(); i++) {
            if (s[i] == '(') {
                int j = i + 1;

                // Find closing bracket
                while (s[j] != ')') {
                    j++;
                }

                // Extract key
                string key = s.substr(i + 1, j - i - 1);

                // Add value if key exists, otherwise '?'
                if (mp.count(key)) {
                    ans += mp[key];
                } else {
                    ans += "?";
                }

                // Move past ')'
                i = j;
            } 
            else {
                ans += s[i];
            }
        }

        return ans;
    }
};