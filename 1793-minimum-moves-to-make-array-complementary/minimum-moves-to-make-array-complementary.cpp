class Solution {
public:
    int minMoves(vector<int>& nums, int limit) {
        int n = nums.size();

        // We only care about sums from 2 to 2 * limit.
        vector<int> diff(2 * limit + 2, 0);

        for (int i = 0; i < n / 2; i++) {
            int a = nums[i];
            int b = nums[n - 1 - i];

            if (a > b)
                swap(a, b);

            // With 2 moves, we can get any valid sum.
            // So initially every sum costs 2 moves.

            // For sums [a + 1, b + limit],
            // only 1 move is required.
            diff[a + 1]--;
            diff[b + limit + 1]++;

            // For sum a + b, we need 0 moves instead of 1.
            diff[a + b]--;
            diff[a + b + 1]++;
        }

        int moves = n; // Number of pairs * 2
        int answer = n;

        for (int sum = 2; sum <= 2 * limit; sum++) {
            moves += diff[sum];
            answer = min(answer, moves);
        }

        return answer;
    }
};