class Solution {
public:
    int longestCommonPrefix(vector<int>& arr1, vector<int>& arr2) {
        unordered_set<int> prefixes;

        // Store all prefixes of arr1
        for (int x : arr1) {
            while (x > 0) {
                prefixes.insert(x);
                x /= 10;
            }
        }

        int ans = 0;

        // Check all prefixes of arr2
        for (int x : arr2) {
            while (x > 0) {
                if (prefixes.count(x)) {
                    ans = max(ans, (int)to_string(x).size());
                }
                x /= 10;
            }
        }

        return ans;
    }
};