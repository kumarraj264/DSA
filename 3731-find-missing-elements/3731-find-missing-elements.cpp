class Solution {
public:
    std::vector<int> findMissingElements(std::vector<int>& nums) {
        bool present[101] = {false};
        int min_num = 101;
        int max_num = 0;
        for (int num : nums) {
            if (num < min_num) min_num = num;
            if (num > max_num) max_num = num;
            present[num] = true;
        }
        std::vector<int> missing;
        for (int i = min_num + 1; i < max_num; ++i) {
            if (!present[i]) {
                missing.push_back(i);
            }
        }
        
        return missing;
    }
};