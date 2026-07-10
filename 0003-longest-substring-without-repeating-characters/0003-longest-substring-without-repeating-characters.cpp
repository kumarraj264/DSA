class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        vector<int> lastPos(256, -1);
        int maxLength = 0;
        int start = 0;
        
        for (int i = 0; i < s.size(); i++) {
            if (lastPos[s[i]] >= start) {
                start = lastPos[s[i]] + 1;
            }
            lastPos[s[i]] = i;
            maxLength = max(maxLength, i - start + 1);
        }
        
        return maxLength;
    }
};
