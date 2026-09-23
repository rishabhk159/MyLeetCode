class Solution {
public:
    bool hasValidPath(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();

        // Directions: up, right, down, left
        int dr[] = {-1, 0, 1, 0};
        int dc[] = {0, 1, 0, -1};

        // Connections for each street type
        // 1-indexed: type 1 ... type 6
        vector<vector<int>> dir = {
            {},             // 0
            {1, 3},         // 1: right, left
            {0, 2},         // 2: up, down
            {3, 2},         // 3: left, down
            {1, 2},         // 4: right, down
            {3, 0},         // 5: left, up
            {1, 0}          // 6: right, up
        };

        queue<pair<int, int>> q;
        vector<vector<bool>> visited(m, vector<bool>(n, false));

        q.push({0, 0});
        visited[0][0] = true;

        while (!q.empty()) {
            auto [r, c] = q.front();
            q.pop();

            if (r == m - 1 && c == n - 1) {
                return true;
            }

            int type = grid[r][c];

            for (int d : dir[type]) {
                int nr = r + dr[d];
                int nc = c + dc[d];

                // Check boundaries
                if (nr < 0 || nr >= m || nc < 0 || nc >= n) {
                    continue;
                }

                if (visited[nr][nc]) {
                    continue;
                }

                // Opposite direction
                int opposite = (d + 2) % 4;

                // Check if the next street connects back to us
                bool connected = false;

                for (int nextDir : dir[grid[nr][nc]]) {
                    if (nextDir == opposite) {
                        connected = true;
                        break;
                    }
                }

                if (connected) {
                    visited[nr][nc] = true;
                    q.push({nr, nc});
                }
            }
        }

        return false;
    }
};