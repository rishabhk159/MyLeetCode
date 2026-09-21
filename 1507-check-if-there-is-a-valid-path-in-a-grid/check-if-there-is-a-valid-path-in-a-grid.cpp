class Solution {
public:
    bool hasValidPath(vector<vector<int>>& grid) {
        // Fast I/O
        ios_base::sync_with_stdio(false);
        cin.tie(nullptr);

        int m = grid.size();
        int n = grid[0].size();

        // Direction bitmasks:
        // Bit 0 (1): UP    (-1, 0)
        // Bit 1 (2): DOWN  (+1, 0)
        // Bit 2 (4): LEFT  ( 0,-1)
        // Bit 3 (8): RIGHT ( 0, +1)
        // Street port connections:
        // 1: left (4) | right (8) = 12
        // 2: up (1) | down (2) = 3
        // 3: left (4) | down (2) = 6
        // 4: right (8) | down (2) = 10
        // 5: left (4) | up (1) = 5
        // 6: right (8) | up (1) = 9
        const int streetDirs[7] = {0, 12, 3, 6, 10, 5, 9};

        // Direction steps: [dr, dc, out_bit, opposite_in_bit]
        const int moves[4][4] = {
            {-1,  0, 1, 2}, // UP: needs DOWN port in next cell
            { 1,  0, 2, 1}, // DOWN: needs UP port in next cell
            { 0, -1, 4, 8}, // LEFT: needs RIGHT port in next cell
            { 0,  1, 8, 4}  // RIGHT: needs LEFT port in next cell
        };

        // Queue-based BFS using a fixed circular buffer / flat array
        int q[300 * 300][2];
        int head = 0, tail = 0;

        // In-place visited tracking by negating visited cells
        q[tail][0] = 0;
        q[tail][1] = 0;
        tail++;

        int startType = grid[0][0];
        grid[0][0] = -startType; // Mark (0, 0) as visited

        while (head < tail) {
            int r = q[head][0];
            int c = q[head][1];
            head++;

            if (r == m - 1 && c == n - 1) return true;

            int currType = -grid[r][c];
            int currMask = streetDirs[currType];

            for (int i = 0; i < 4; ++i) {
                if (!(currMask & moves[i][2])) continue; // Current street has no exit this way

                int nr = r + moves[i][0];
                int nc = c + moves[i][1];

                // Bounds check and unvisited check (unvisited cells have grid > 0)
                if (nr >= 0 && nr < m && nc >= 0 && nc < n && grid[nr][nc] > 0) {
                    int nextType = grid[nr][nc];
                    // Verify if target cell has matching incoming port
                    if (streetDirs[nextType] & moves[i][3]) {
                        grid[nr][nc] = -nextType; // Mark visited in-place
                        q[tail][0] = nr;
                        q[tail][1] = nc;
                        tail++;
                    }
                }
            }
        }

        return false;
    }
};