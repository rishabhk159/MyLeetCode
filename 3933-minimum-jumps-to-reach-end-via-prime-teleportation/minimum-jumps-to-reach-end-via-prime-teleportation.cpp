class Solution {
public:
    int minJumps(vector<int>& nums) {
        int n = nums.size();
        if (n == 1) return 0;

        int MAX = *max_element(nums.begin(), nums.end());

        // Smallest Prime Factor
        vector<int> spf(MAX + 1);
        for (int i = 0; i <= MAX; i++)
            spf[i] = i;

        for (int i = 2; 1LL * i * i <= MAX; i++) {
            if (spf[i] == i) {
                for (long long j = 1LL * i * i; j <= MAX; j += i) {
                    if (spf[j] == j)
                        spf[j] = i;
                }
            }
        }

        // prime -> indices whose nums[index] is divisible by prime
        vector<vector<int>> indices(MAX + 1);

        for (int i = 0; i < n; i++) {
            int x = nums[i];

            while (x > 1) {
                int p = spf[x];
                indices[p].push_back(i);

                // Remove all occurrences of p
                while (x % p == 0)
                    x /= p;
            }
        }

        vector<int> dist(n, -1);
        vector<bool> usedPrime(MAX + 1, false);

        queue<int> q;
        q.push(0);
        dist[0] = 0;

        while (!q.empty()) {
            int i = q.front();
            q.pop();

            if (i == n - 1)
                return dist[i];

            // Adjacent step: i - 1
            if (i - 1 >= 0 && dist[i - 1] == -1) {
                dist[i - 1] = dist[i] + 1;
                q.push(i - 1);
            }

            // Adjacent step: i + 1
            if (i + 1 < n && dist[i + 1] == -1) {
                dist[i + 1] = dist[i] + 1;
                q.push(i + 1);
            }

            // Prime teleportation
            int x = nums[i];

            // Teleportation is possible only when nums[i] itself is prime
            if (x >= 2 && spf[x] == x && !usedPrime[x]) {
                usedPrime[x] = true;

                for (int j : indices[x]) {
                    if (dist[j] == -1) {
                        dist[j] = dist[i] + 1;
                        q.push(j);
                    }
                }
            }
        }

        return -1;
    }
};