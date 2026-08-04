class Solution {
public:
    std::vector<int> findMissingElements(std::vector<int>& nums) {
        int min_num = *std::min_element(nums.begin(), nums.end());
        int max_num = *std::max_element(nums.begin(), nums.end());
        std::unordered_set<int> num_set(nums.begin(), nums.end());
        
        std::vector<int> missing;
        for (int i = min_num; i <= max_num; ++i) {
            if (num_set.find(i) == num_set.end()) {
                missing.push_back(i);
            }
        }
        return missing;
    }
};
