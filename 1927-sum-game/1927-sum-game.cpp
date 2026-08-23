class Solution {
public:
    bool sumGame(string num) {
        int n = num.size();
        
        int diff = 0;
        int leftQ = 0, rightQ = 0;

        // First half
        for (int i = 0; i < n / 2; i++) {
            if (num[i] == '?')
                leftQ++;
            else
                diff += num[i] - '0';
        }

        // Second half
        for (int i = n / 2; i < n; i++) {
            if (num[i] == '?')
                rightQ++;
            else
                diff -= num[i] - '0';
        }

        int totalQ = leftQ + rightQ;

        // Odd number of '?' means Alice makes the last move.
        if (totalQ % 2 == 1)
            return true;

        // Only even number of '?' remains.
        // Bob can win only if the difference can be exactly balanced.
        return diff != 9 * (rightQ - leftQ) / 2;
    }
};