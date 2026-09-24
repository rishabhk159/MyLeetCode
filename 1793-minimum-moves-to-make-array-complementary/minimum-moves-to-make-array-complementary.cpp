class Solution {
public:
    int minMoves(vector<int>& nums, int limit) {
        int n = nums.size();

        vector<int> diff(2 * limit + 2, 0);

        for (int i = 0; i < n / 2; i++) {
            int a = nums[i];
            int b = nums[n - 1 - i];

            int low = min(a, b);
            int high = max(a, b);
            int sum = a + b;

            // Initially: 2 moves for every possible sum
            diff[2] += 2;

            // low + 1 ... high + limit : reduce by 1
            diff[low + 1] -= 1;
            diff[high + limit + 1] += 1;

            // sum : reduce one more, making it 0 moves
            diff[sum] -= 1;
            diff[sum + 1] += 1;
        }

        int ans = n;
        int moves = 0;

        for (int s = 2; s <= 2 * limit; s++) {
            moves += diff[s];
            ans = min(ans, moves);
        }

        return ans;
    }
};