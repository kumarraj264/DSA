#include <string>
#include <vector>
#include <algorithm>

class Solution {
public:
    string smallestPalindrome(string s) {
        // Step 1: Count character frequencies
        vector<int> counts(26, 0);
        for (char c : s) {
            counts[c - 'a']++;
        }
        
        string left_half = "";
        string middle = "";
        
        // Step 2: Build alphabetical left half
        for (int i = 0; i < 26; i++) {
            if (counts[i] > 0) {
                char c = 'a' + i;
                left_half.append(counts[i] / 2, c);
                if (counts[i] % 2 != 0) {
                    middle = c;
                }
            }
        }
        
        // Step 3: Symmetrically mirror the string
        string right_half = left_half;
        reverse(right_half.begin(), right_half.end());
        
        return left_half + middle + right_half;
    }
};
