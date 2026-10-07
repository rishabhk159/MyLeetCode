class Solution {
public:
    bool isValid(string s) {
        int count = 0;

        for (char c : s) {
            if (c == '(') {
                count++;
            }
            else if (c == ')') {
                count--;

                // More ')' than '('
                if (count < 0)
                    return false;
            }
        }

        // All '(' must be matched
        return count == 0;
    }

    vector<string> removeInvalidParentheses(string s) {
        vector<string> ans;

        queue<string> q;
        unordered_set<string> visited;

        q.push(s);
        visited.insert(s);

        bool found = false;

        while (!q.empty()) {
            int size = q.size();

            while (size--) {
                string current = q.front();
                q.pop();

                // If valid, add it to answer
                if (isValid(current)) {
                    ans.push_back(current);
                    found = true;
                }

                // If valid strings are found at this level,
                // don't generate the next level.
                if (found)
                    continue;

                // Remove one parenthesis
                for (int i = 0; i < current.size(); i++) {

                    // We only remove parentheses
                    if (current[i] != '(' && current[i] != ')')
                        continue;

                    string next = current.substr(0, i) +
                                  current.substr(i + 1);

                    if (visited.find(next) == visited.end()) {
                        visited.insert(next);
                        q.push(next);
                    }
                }
            }

            // First valid level = minimum removals
            if (found)
                break;
        }

        return ans;
    }
};