#include <vector>

class Solution {
public:
    std::vector<std::vector<int>> shiftGrid(std::vector<std::vector<int>>& grid, int k) {
        int m = grid.size();
        int n = grid[0].size();
        int total_elements = m * n;
        
        // Eliminate redundant full loops
        k = k % total_elements;
        
        // Create an empty output grid with the same dimensions
        std::vector<std::vector<int>> result(m, std::vector<int>(n, 0));
        
        for (int r = 0; r < m; ++r) {
            for (int c = 0; c < n; ++c) {
                // Flatten 2D grid coordinates to a 1D index
                int old_1d_index = r * n + c;
                
                // Shift the 1D index and handle wrap-arounds
                int new_1d_index = (old_1d_index + k) % total_elements;
                
                // Map the new 1D index back into 2D coordinates
                int new_r = new_1d_index / n;
                int new_c = new_1d_index % n;
                
                // Place the element into its new location
                result[new_r][new_c] = grid[r][c];
            }
        }
        
        return result;
    }
};
