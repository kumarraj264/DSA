class Solution {
public:
    long long sumAndMultiply(int n) {
        string s = to_string(n);
        string filtered = "";
        long long sum = 0;
        
        for (char c : s) {
            if (c != '0') {
                filtered += c;
                sum += (c - '0');
            }
        }
        
        if (filtered.empty()) {
            return 0;
        }
        
        long long x = stoll(filtered);
        return x * sum;
    }
};
