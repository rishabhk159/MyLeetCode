class Solution {
public:
    int findMin(vector<int>& nums) {
        int left = 0;
        int right = nums.size() - 1;

        while (left < right) {
            int mid = left + (right - left) / 2;

            if (nums[mid] > nums[right]) {
                // Minimum lies in the right half
                left = mid + 1;
            } else {
                // Minimum lies in the left half, including mid
                right = mid;
            }
        }

        return nums[left];
    }
};