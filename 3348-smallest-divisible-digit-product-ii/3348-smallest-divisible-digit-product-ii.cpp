#include <string>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

class Solution {
private:
    // Safely reduces target factors by trying to greedily pack into single large digits (9 down to 2)
    string getMinSuffixDigits(long long rem_t) {
        if (rem_t <= 1) return "";
        string s = "";
        
        for (int d = 9; d >= 2; --d) {
            while (rem_t % d == 0) {
                s += to_string(d);
                rem_t /= d;
            }
        }
        if (rem_t > 1) return "-1"; // Contains invalid prime factors
        
        sort(s.begin(), s.end());
        return s;
    }

public:
    string smallestNumber(string num, long long t) {
        // Step 1: Pre-verify if t has prime factors other than 2, 3, 5, 7
        long long check_t = t;
        for (int p : {2, 3, 5, 7}) {
            while (check_t % p == 0) check_t /= p;
        }
        if (check_t > 1) return "-1";

        int n = num.length();
        
        // Find the index of the first zero from the left
        int first_zero = -1;
        for (int i = 0; i < n; ++i) {
            if (num[i] == '0') {
                first_zero = i;
                break;
            }
        }
        
        // Step 2: Compute the running factor remainder of t for each prefix state
        vector<long long> rem_t(n + 1, 1);
        rem_t[0] = t;
        for (int i = 0; i < n; ++i) {
            int d = num[i] - '0';
            if (d == 0) {
                rem_t[i + 1] = rem_t[i];
            } else {
                rem_t[i + 1] = rem_t[i] / std::gcd(rem_t[i], (long long)d);
            }
        }

        // Case 1: The number itself contains no zeros and already satisfies t
        if (first_zero == -1 && rem_t[n] == 1) {
            return num;
        }

        // Case 2: Backtrack from the highest safe position to modify
        // If a zero exists, we can at most modify the index where the zero resides
        int max_i = (first_zero != -1) ? first_zero : n - 1;
        
        for (int i = max_i; i >= 0; --i) {
            int curr_d = num[i] - '0';
            for (int next_d = curr_d + 1; next_d <= 9; ++next_d) {
                long long next_rem_t = rem_t[i] / std::gcd(rem_t[i], (long long)next_d);
                
                string required_suffix = getMinSuffixDigits(next_rem_t);
                if (required_suffix == "-1") continue;
                
                int remaining_len = n - 1 - i;
                if ((int)required_suffix.length() <= remaining_len) {
                    // Pad leftover suffix spaces with '1's to keep value minimized
                    string padded_suffix = string(remaining_len - required_suffix.length(), '1') + required_suffix;
                    return num.substr(0, i) + to_string(next_d) + padded_suffix;
                }
            }
        }

        // Case 3: No valid match fits in length n. Expand total string length.
        string total_suffix = getMinSuffixDigits(t);
        int target_len = max(n + 1, (int)total_suffix.length());
        return string(target_len - total_suffix.length(), '1') + total_suffix;
    }
};
