class Solution {
public:
    bool isValidSudoku(vector<vector<char>>& board) {
        
        bool row[9][9] = {};
        bool col[9][9] = {};
        bool box[9][9] = {};

        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                
                if (board[i][j] == '.') {
                    continue;
                }

                int digit = board[i][j] - '1';

                // Find the 3x3 box number
                int boxIndex = (i / 3) * 3 + (j / 3);

                // Check duplicate
                if (row[i][digit] ||
                    col[j][digit] ||
                    box[boxIndex][digit]) {
                    return false;
                }

                // Mark as used
                row[i][digit] = true;
                col[j][digit] = true;
                box[boxIndex][digit] = true;
            }
        }

        return true;
    }
};