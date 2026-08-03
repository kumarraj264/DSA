#include <vector>
#include <string>
#include <algorithm>
#include <climits>

class Solution {
public:
    std::string stoneGameIII(std::vector<int>& stoneValue) {
        int n = stoneValue.size();
        // dp[i] stores the max relative score difference from index i to n
        // Initialize with a large negative number, size n + 1 to handle base case dp[n] = 0
        std::vector<int> dp(n + 1, INT_MIN);
        dp[n] = 0; // Base case: no stones left, difference is 0

        for (int i = n - 1; i >= 0; --i) {
            int current_stones_sum = 0;
            // A player can take 1, 2, or 3 stones
            for (int x = 1; x <= 3; ++x) {
                if (i + x <= n) {
                    current_stones_sum += stoneValue[i + x - 1];
                    dp[i] = std::max(dp[i], current_stones_sum - dp[i + x]);
                }
            }
        }

        int alice_relative_score = dp[0];

        if (alice_relative_score > 0) return "Alice";
        if (alice_relative_score < 0) return "Bob";
        return "Tie";
    }
};
