class Solution {
public:
    vector<int> leftRightDifference(vector<int>& nums) {
        int n = nums.size();

        vector<int> answer(n);

        int totalSum = 0;
        for (int x : nums) {
            totalSum += x;
        }

        int leftSum = 0;

        for (int i = 0; i < n; i++) {
            // Right sum = total - left sum - current element
            int rightSum = totalSum - leftSum - nums[i];

            answer[i] = abs(leftSum - rightSum);

            // Add current element for the next index
            leftSum += nums[i];
        }

        return answer;
    }
};