#include <string>
#include <algorithm>

using namespace std;

class Solution {
public:
    int minOperations(string s) {
        int n = s.size();

        // Check if already sorted
        if (is_sorted(s.begin(), s.end())) {
            return 0;
        }

        // A length-2 unsorted string cannot be modified by proper substrings
        if (n == 2) {
            return -1;
        }

        char mn = *min_element(s.begin(), s.end());
        char mx = *max_element(s.begin(), s.end());

        // Can be sorted in 1 operation
        if (s[0] == mn || s[n - 1] == mx) {
            return 1;
        }

        // Can be sorted in 2 operations if an extreme element lies in the interior
        for (int i = 1; i < n - 1; ++i) {
            if (s[i] == mn || s[i] == mx) {
                return 2;
            }
        }

        // Otherwise, 3 operations are required
        return 3;
    }
};