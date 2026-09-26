class Solution {
public:
    int getWaviness(int num) {
        string s = to_string(num);

        // Less than 3 digits -> waviness is 0
        if (s.size() < 3) {
            return 0;
        }

        int count = 0;

        // First and last digits cannot be peaks/valleys
        for (int i = 1; i < s.size() - 1; i++) {
            int left = s[i - 1] - '0';
            int current = s[i] - '0';
            int right = s[i + 1] - '0';

            // Peak
            if (current > left && current > right) {
                count++;
            }
            // Valley
            else if (current < left && current < right) {
                count++;
            }
        }

        return count;
    }

    int totalWaviness(int num1, int num2) {
        int ans = 0;

        for (int num = num1; num <= num2; num++) {
            ans += getWaviness(num);
        }

        return ans;
    }
};