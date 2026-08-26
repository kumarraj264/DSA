class Solution {
public:
    std::string shortestBeautifulSubstring(std::string s, int k) {
        std::vector<int> ones;
        for (int i = 0; i < s.length(); ++i) {
            if (s[i] == '1') {
                ones.push_back(i);
            }
        }
        if (ones.size() < k) {
            return "";
        }
        std::string res = "";
        int min_len = INT_MAX;
        for (size_t i = 0; i <= ones.size() - k; ++i) {
            int left = ones[i];
            int right = ones[i + k - 1];
            int curr_len = right - left + 1;
            std::string substring = s.substr(left, curr_len);
            if (curr_len < min_len) {
                min_len = curr_len;
                res = substring;
            } else if (curr_len == min_len) {
                if (substring < res) {
                    res = substring;
                }
            }
        }
        return res;
    }
};