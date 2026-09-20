#include <string>

class Solution {
public:
    int reverseDegree(std::string s) {
        int totalDegree = 0;
        
        for (int i = 0; i < s.length(); ++i) {
            int charValue = 26 - (s[i] - 'a');
            int position = i + 1;
            totalDegree += charValue * position;
        }
        
        return totalDegree;
    }
};