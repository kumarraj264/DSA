#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<int> gcdValues(vector<int>& nums, vector<long long>& queries) {
        int max_num = *max_element(nums.begin(), nums.end());
        
        // Step 1: Count frequency of each number
        vector<long long> counts(max_num + 1, 0);
        for (int num : nums) {
            counts[num]++;
        }
        
        // Step 2: Compute number of pairs with GCD exactly equal to i
        vector<long long> gcd_pairs(max_num + 1, 0);
        
        // Loop backwards to use Inclusion-Exclusion principle
        for (int i = max_num; i >= 1; --i) {
            long long total_multiples = 0;
            for (int j = i; j <= max_num; j += i) {
                total_multiples += counts[j];
            }
            
            // Total combinations of pairs formed by these multiples
            long long pairs_count = (total_multiples * (total_multiples - 1)) / 2;
            
            // Subtract pairs that have a strictly larger GCD multiple (2i, 3i, etc.)
            for (int j = 2 * i; j <= max_num; j += i) {
                pairs_count -= gcd_pairs[j];
            }
            
            gcd_pairs[i] = pairs_count;
        }
        
        // Step 3: Build prefix sums for tracking positioning
        vector<long long> prefix_sums(max_num + 1, 0);
        for (int i = 1; i <= max_num; ++i) {
            prefix_sums[i] = prefix_sums[i - 1] + gcd_pairs[i];
        }
        
        // Step 4: Answer each query using binary search (upper_bound)
        vector<int> ans;
        ans.reserve(queries.size());
        
        for (long long q : queries) {
            // upper_bound finds the first position where prefix_sums[idx] > q
            auto it = upper_bound(prefix_sums.begin(), prefix_sums.end(), q);
            int idx = distance(prefix_sums.begin(), it);
            ans.push_back(idx);
        }
        
        return ans;
    }
};
