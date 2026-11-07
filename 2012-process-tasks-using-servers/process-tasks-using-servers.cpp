#include <vector>
#include <queue>
#include <tuple>

using namespace std;

class Solution {
public:
    vector<int> assignTasks(vector<int>& servers, vector<int>& tasks) {
        int n = servers.size();
        int m = tasks.size();
        
        // Element: (weight, server_index)
        using FreeServer = pair<int, int>;
        priority_queue<FreeServer, vector<FreeServer>, greater<FreeServer>> free_servers;
        
        for (int i = 0; i < n; ++i) {
            free_servers.emplace(servers[i], i);
        }
        
        // Element: (free_time, weight, server_index)
        using BusyServer = tuple<long long, int, int>;
        priority_queue<BusyServer, vector<BusyServer>, greater<BusyServer>> busy_servers;
        
        vector<int> ans(m);
        long long cur_time = 0;
        
        for (int j = 0; j < m; ++j) {
            // Task j arrives at second j
            cur_time = max(cur_time, (long long)j);
            
            // If no servers are available, jump time to when the next server frees up
            if (free_servers.empty()) {
                cur_time = max(cur_time, get<0>(busy_servers.top()));
            }
            
            // Release all servers that finish on or before cur_time
            while (!busy_servers.empty() && get<0>(busy_servers.top()) <= cur_time) {
                auto [finish_time, weight, idx] = busy_servers.top();
                busy_servers.pop();
                free_servers.emplace(weight, idx);
            }
            
            // Assign the task to the highest-priority free server
            auto [weight, idx] = free_servers.top();
            free_servers.pop();
            
            ans[j] = idx;
            busy_servers.emplace(cur_time + tasks[j], weight, idx);
        }
        
        return ans;
    }
};