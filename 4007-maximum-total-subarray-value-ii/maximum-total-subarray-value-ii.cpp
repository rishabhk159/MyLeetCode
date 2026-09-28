class Solution {
public:
    int n;
    vector<vector<int>> mx, mn;
    vector<int> lg;

    void buildSparseTable(vector<int>& nums) {
        n = nums.size();

        lg.resize(n + 1);
        for (int i = 2; i <= n; i++) {
            lg[i] = lg[i / 2] + 1;
        }

        int LOG = lg[n] + 1;

        mx.assign(n, vector<int>(LOG));
        mn.assign(n, vector<int>(LOG));

        for (int i = 0; i < n; i++) {
            mx[i][0] = nums[i];
            mn[i][0] = nums[i];
        }

        for (int j = 1; j < LOG; j++) {
            for (int i = 0; i + (1 << j) <= n; i++) {
                mx[i][j] = max(
                    mx[i][j - 1],
                    mx[i + (1 << (j - 1))][j - 1]
                );

                mn[i][j] = min(
                    mn[i][j - 1],
                    mn[i + (1 << (j - 1))][j - 1]
                );
            }
        }
    }

    int getValue(int l, int r) {
        int len = r - l + 1;
        int j = lg[len];

        int maximum = max(
            mx[l][j],
            mx[r - (1 << j) + 1][j]
        );

        int minimum = min(
            mn[l][j],
            mn[r - (1 << j) + 1][j]
        );

        return maximum - minimum;
    }

    long long maxTotalValue(vector<int>& nums, int k) {
        n = nums.size();

        buildSparseTable(nums);

        // {value, left, right}
        priority_queue<
            tuple<int, int, int>
        > pq;

        // For every left endpoint, initially take
        // the longest subarray [l, n-1].
        for (int l = 0; l < n; l++) {
            int value = getValue(l, n - 1);
            pq.push({value, l, n - 1});
        }

        long long answer = 0;

        while (k--) {
            auto [value, l, r] = pq.top();
            pq.pop();

            answer += value;

            // For the same left endpoint, the next candidate
            // is [l, r-1].
            if (r > l) {
                int nextValue = getValue(l, r - 1);
                pq.push({nextValue, l, r - 1});
            }
        }

        return answer;
    }
};