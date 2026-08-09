class Solution {
public:
    int stoneGameII(std::vector<int>& piles) {
        int n = piles.size();
        
        // suffix_sum[i] stores the total stones from index i to the end
        std::vector<int> suffix_sum(n + 1, 0);
        for (int i = n - 1; i >= 0; --i) {
            suffix_sum[i] = suffix_sum[i + 1] + piles[i];
        }
        
        // Memoization table: memo[i][M] initialization
        // M can grow up to n, so we allocate a size of (n + 1)
        std::vector<std::vector<int>> memo(n, std::vector<int>(n + 1, -1));
        
        return dp(0, 1, n, suffix_sum, memo);
    }

private:
    int dp(int i, int M, int n, const std::vector<int>& suffix_sum, std::vector<std::vector<int>>& memo) {
        // If the current player can take all remaining piles, take them all
        if (i + 2 * M >= n) {
            return suffix_sum[i];
        }
        
        // Return precomputed result if available
        if (memo[i][M] != -1) {
            return memo[i][M];
        }
        
        int opponent_min_score = 1e9; // Initialize with a large value
        
        // Explore taking X piles where 1 <= X <= 2M
        for (int X = 1; X <= 2 * M; ++X) {
            int next_M = std::max(M, X);
            int opponent_score = dp(i + X, next_M, n, suffix_sum, memo);
            opponent_min_score = std::min(opponent_min_score, opponent_score);
        }
        
        // Current player's score is total remaining stones minus the opponent's best score
        memo[i][M] = suffix_sum[i] - opponent_min_score;
        return memo[i][M];
    }
};
