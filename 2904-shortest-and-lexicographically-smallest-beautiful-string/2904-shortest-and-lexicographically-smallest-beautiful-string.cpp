#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    string shortestBeautifulSubstring(string s, int k) {
        vector<int> ones;
        for (int i = 0; i < s.length(); ++i) {
            if (s[i] == '1') {
                ones.push_back(i);
            }
        }
        
        if (ones.size() < k) return "";
        
        string result = "";
        
        for (int i = 0; i + k - 1 < ones.size(); ++i) {
            int start = ones[i];
            int end = ones[i + k - 1];
            string sub = s.substr(start, end - start + 1);
            
            if (result.empty() || sub.length() < result.length() || 
               (sub.length() == result.length() && sub < result)) {
                result = sub;
            }
        }
        
        return result;
    }
};