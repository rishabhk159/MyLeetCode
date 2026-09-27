class Solution {
public:
    string reverseParentheses(string s) {
        stack<string> st;
        st.push("");

        for (char ch : s) {
            if (ch == '(') {
                // Start a new substring
                st.push("");
            }
            else if (ch == ')') {
                // Get the substring inside parentheses
                string temp = st.top();
                st.pop();

                // Reverse it
                reverse(temp.begin(), temp.end());

                // Add it to the previous level
                st.top() += temp;
            }
            else {
                // Add normal character
                st.top() += ch;
            }
        }

        return st.top();
    }
};