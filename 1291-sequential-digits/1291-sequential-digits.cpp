class Solution {
public:
    vector<int> sequentialDigits(int low, int high) {
        string sample = "123456789";
        vector<int> res;
        
        int lowLen = to_string(low).length();
        int highLen = to_string(high).length();
        
        for (int len = lowLen; len <= highLen; ++len) {
            for (int start = 0; start <= 9 - len; ++start) {
                string sub = sample.substr(start, len);
                int num = stoi(sub);
                
                if (num >= low && num <= high) {
                    res.push_back(num);
                }
            }
        }
        return res;
    }
};
