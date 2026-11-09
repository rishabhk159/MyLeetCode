#include <vector>
#include <set>
#include <queue>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<int> busiestServers(int k, vector<int>& arrival, vector<int>& load) {
        int n = arrival.size();
        vector<int> count(k, 0);

        // Stores available server IDs in sorted order
        set<int> available;
        for (int i = 0; i < k; ++i) {
            available.insert(i);
        }

        // Min-heap storing {end_time, server_id}
        priority_queue<pair<long long, int>, 
                       vector<pair<long long, int>>, 
                       greater<pair<long long, int>>> busy;

        for (int i = 0; i < n; ++i) {
            long long cur_time = arrival[i];

            // Free all servers that have finished before or at cur_time
            while (!busy.empty() && busy.top().first <= cur_time) {
                available.insert(busy.top().second);
                busy.pop();
            }

            // If no servers are available, drop the request
            if (available.empty()) {
                continue;
            }

            // Find the first available server >= (i % k)
            int target = i % k;
            auto it = available.lower_bound(target);

            // If no server >= target, wrap around to the smallest available index
            if (it == available.end()) {
                it = available.begin();
            }

            int assigned_server = *it;
            count[assigned_server]++;
            busy.push({cur_time + load[i], assigned_server});
            available.erase(it);
        }

        // Find the maximum number of requests handled
        int max_requests = *max_element(count.begin(), count.end());

        // Collect all servers that handled max_requests
        vector<int> result;
        for (int i = 0; i < k; ++i) {
            if (count[i] == max_requests) {
                result.push_back(i);
            }
        }

        return result;
    }
};