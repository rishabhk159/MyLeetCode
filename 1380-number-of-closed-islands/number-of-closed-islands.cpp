#include <vector>

using namespace std;

class Solution {
private:
    void dfs(vector<vector<int>>& grid, int r, int c, int rows, int cols) {
        if (r < 0 || r >= rows || c < 0 || c >= cols || grid[r][c] == 1) {
            return;
        }
        
        // Mark as visited by sinking it into water
        grid[r][c] = 1;
        
        dfs(grid, r + 1, c, rows, cols);
        dfs(grid, r - 1, c, rows, cols);
        dfs(grid, r, c + 1, rows, cols);
        dfs(grid, r, c - 1, rows, cols);
    }

public:
    int closedIsland(vector<vector<int>>& grid) {
        int rows = grid.size();
        int cols = grid[0].size();
        
        // Step 1: Remove all islands connected to the boundary
        for (int r = 0; r < rows; ++r) {
            if (grid[r][0] == 0) dfs(grid, r, 0, rows, cols);
            if (grid[r][cols - 1] == 0) dfs(grid, r, cols - 1, rows, cols);
        }
        
        for (int c = 0; c < cols; ++c) {
            if (grid[0][c] == 0) dfs(grid, 0, c, rows, cols);
            if (grid[rows - 1][c] == 0) dfs(grid, rows - 1, c, rows, cols);
        }
        
        // Step 2: Count the remaining interior islands
        int closedCount = 0;
        for (int r = 1; r < rows - 1; ++r) {
            for (int c = 1; c < cols - 1; ++c) {
                if (grid[r][c] == 0) {
                    closedCount++;
                    dfs(grid, r, c, rows, cols);
                }
            }
        }
        
        return closedCount;
    }
};