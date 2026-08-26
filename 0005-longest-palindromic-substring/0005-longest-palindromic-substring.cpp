#include <string>
#include <algorithm>

using namespace std;

class Solution {
public:
    string longestPalindrome(string s) {
        if (s.empty()) return "";
        
        int start = 0;
        int max_len = 1;
        
        // Helper lambda to expand around the center
        auto expandAroundCenter = [&](int left, int right) {
            while (left >= 0 && right < s.length() && s[left] == s[right]) {
                int current_len = right - left + 1;
                if (current_len > max_len) {
                    max_len = current_len;
                    start = left;
                }
                left--;
                right++;
            }
        };
        
        for (int i = 0; i < s.length(); ++i) {
            expandAroundCenter(i, i);     // Odd-length palindromes
            expandAroundCenter(i, i + 1); // Even-length palindromes
        }
        
        return s.substr(start, max_len);
    }
};