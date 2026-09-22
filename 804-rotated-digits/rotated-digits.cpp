class Solution {
public:
    int rotatedDigits(int n) {
        int ans = 0;

        for (int x = 1; x <= n; x++) {
            int num = x;
            bool valid = true;
            bool changed = false;

            while (num > 0) {
                int d = num % 10;

                if (d == 2 || d == 5 || d == 6 || d == 9) {
                    changed = true;
                }
                else if (d == 0 || d == 1 || d == 8) {
                    // Valid but unchanged
                }
                else {
                    valid = false;
                    break;
                }

                num /= 10;
            }

            if (valid && changed)
                ans++;
        }

        return ans;
    }
};