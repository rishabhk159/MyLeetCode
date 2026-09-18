class Solution {
public:
    bool isValid(string s) {
        // Fast I/O
        ios_base::sync_with_stdio(false);
        cin.tie(nullptr);

        // An odd-length string cannot be valid
        if (s.length() % 2 != 0) return false;

        // Use a fixed-size stack to avoid dynamic allocations
        char st[10005];
        int top = -1;

        for (char c : s) {
            switch (c) {
                case '(': st[++top] = ')'; break;
                case '{': st[++top] = '}'; break;
                case '[': st[++top] = ']'; break;
                default:
                    if (top == -1 || st[top] != c) return false;
                    --top;
            }
        }

        return top == -1;
    }
};