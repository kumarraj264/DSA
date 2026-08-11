#include <vector>
#include <unordered_set>

class Solution {
public:
    int missingInteger(std::vector<int>& nums) {
        int prefix_sum = nums[0];
        for (size_t i = 1; i < nums.size(); ++i) {
            if (nums[i] == nums[i - 1] + 1) {
                prefix_sum += nums[i];
            } else {
                break;
            }
        }
        
        std::unordered_set<int> nums_set(nums.begin(), nums.end());
        while (nums_set.count(prefix_sum)) {
            prefix_sum++;
        }
        
        return prefix_sum;
    }
};
