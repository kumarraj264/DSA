#include <vector>
#include <algorithm>

class Solution {
public:
    bool predictTheWinner(std::vector<int>& nums) {
        int n = nums.size();
        // Base case: when i == j, the player must pick the only available number
        std::vector<int> dp(nums.begin(), nums.end());
        
        // Build the table bottom-up
        for (int i = n - 2; i >= 0; --i) {
            for (int j = i + 1; j < n; ++j) {
                dp[j] = std::max(nums[i] - dp[j], nums[j] - dp[j - 1]);
            }
        }
        
        // If Player 1's score advantage is >= 0, Player 1 wins
        return dp[n - 1] >= 0;
    }
};
