class Solution {
public:
    bool rotateString(string s, string goal) {
        // Fast I/O
        ios_base::sync_with_stdio(false);
        cin.tie(nullptr);

        if (s.length() != goal.length()) return false;

        // Any rotation of s is guaranteed to be a substring of s + s
        return (s + s).find(goal) != string::npos;
    }
};