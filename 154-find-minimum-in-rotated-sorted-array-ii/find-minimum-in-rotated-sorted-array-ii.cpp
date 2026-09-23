class Solution {
public:
    int findMin(vector<int>& nums) {
        int left = 0;
        int right = nums.size() - 1;

        while (left < right) {
            int mid = left + (right - left) / 2;

            if (nums[mid] > nums[right]) {
                // Minimum must be on the right
                left = mid + 1;
            }
            else if (nums[mid] < nums[right]) {
                // Minimum is at mid or on the left
                right = mid;
            }
            else {
                // nums[mid] == nums[right]
                // We cannot determine the side,
                // so safely discard nums[right].
                right--;
            }
        }

        return nums[left];
    }
};