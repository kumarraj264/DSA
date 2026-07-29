#include <string>
#include <vector>
#include <map>
#include <numeric>
#include <algorithm>

using namespace std;

class Solution {
private:
    const long long INF = 1e16; // A safe threshold to cap values well below long long overflow

    // Helper to calculate combinations (n Cr) safely capped at INF
    long long math_comb(int n, int r) {
        if (r < 0 || r > n) return 0;
        if (r == 0 || r == n) return 1;
        if (r > n / 2) r = n - r; // Optimize calculations
        
        long long res = 1;
        for (int i = 1; i <= r; ++i) {
            // Check for potential multiplication overflow
            if (res > (INF + i - 1) / (n - i + 1)) {
                return INF;
            }
            res = res * (n - i + 1) / i;
        }
        return min(res, INF);
    }

    // Computes unique multinomial arrangements safely capped at INF
    long long count_permutations(const vector<int>& half_counts) {
        int total_len = 0;
        for (int freq : half_counts) {
            total_len += freq;
        }
        
        long long ans = 1;
        int current_len = total_len;
        
        for (int freq : half_counts) {
            if (freq > 0) {
                long long combinations = math_comb(current_len, freq);
                if (combinations == 0) return 0;
                
                // Safe multiplication to avoid long long overflow
                if (ans > INF / combinations) {
                    return INF;
                }
                ans *= combinations;
                current_len -= freq;
            }
        }
        return min(ans, INF);
    }

public:
    string smallestPalindrome(string s, long long k) {
        // Step 1: Count character frequencies using a fixed 26-element array
        vector<int> counts(26, 0);
        for (char c : s) {
            counts[c - 'a']++;
        }
        
        string mid_char = "";
        vector<int> half_counts(26, 0);
        
        for (int i = 0; i < 26; ++i) {
            if (counts[i] % 2 == 1) {
                mid_char = string(1, (char)('a' + i));
            }
            half_counts[i] = counts[i] / 2;
        }

        // Validate if k-th permutation is within total possible permutations
        if (count_permutations(half_counts) < k) {
            return "";
        }

        // Step 2: Greedily build the left half of the palindrome position-by-position
        string left_half = "";
        int total_half_len = 0;
        for (int freq : half_counts) total_half_len += freq;

        for (int pos = 0; pos < total_half_len; ++pos) {
            for (int i = 0; i < 26; ++i) {
                if (half_counts[i] > 0) {
                    // Tentatively pick character i
                    half_counts[i]--;
                    
                    // Count how many arrangements can be made with the REMAINING characters
                    long long perms = count_permutations(half_counts);
                    
                    if (k <= perms) {
                        // This character belongs at the current position
                        left_half += (char)('a' + i);
                        break; // Move to the next position
                    } else {
                        // Skip all permutations that would start with character i
                        k -= perms;
                        // Backtrack character count
                        half_counts[i]++;
                    }
                }
            }
        }

        // Step 3: Reconstruct full palindrome
        string right_half = left_half;
        reverse(right_half.begin(), right_half.end());
        
        return left_half + mid_char + right_half;
    }
};
