#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    vector<int> sumAndMultiply(string s, vector<vector<int>>& queries) {
        int m = s.length();
        long long MOD = 1e9 + 7;

        // Prefix arrays
        vector<long long> total_sum(m + 1, 0); // Prefix sum of non-zero digits
        vector<int> nz_count(m + 1, 0);        // Prefix count of non-zero digits
        vector<long long> x_hash(m + 1, 0);    // Prefix hash value of the number formed

        // Precompute powers of 10 modulo 10^9 + 7
        vector<long long> pow10(m + 1, 1);
        for (int i = 1; i <= m; ++i) {
            pow10[i] = (pow10[i - 1] * 10) % MOD;
        }

        // Build prefix tables
        for (int i = 0; i < m; ++i) {
            int digit = s[i] - '0';
            
            if (digit != 0) {
                total_sum[i + 1] = total_sum[i] + digit;
                nz_count[i + 1] = nz_count[i] + 1;
                x_hash[i + 1] = (x_hash[i] * 10 + digit) % MOD;
            } else {
                total_sum[i + 1] = total_sum[i];
                nz_count[i + 1] = nz_count[i];
                x_hash[i + 1] = x_hash[i];
            }
        }

        // Process queries
        vector<int> answer;
        answer.reserve(queries.size());

        for (const auto& q : queries) {
            int l = q[0];
            int r = q[1];

            // 1. Get total sum of non-zero digits in s[l..r]
            long long current_sum = total_sum[r + 1] - total_sum[l];

            // 2. Compute concatenated non-zero integer (x) modulo 10^9 + 7
            int count_in_range = nz_count[r + 1] - nz_count[l];
            
            // Isolate x_sub = (x_hash[r+1] - x_hash[l] * 10^(count_in_range)) % MOD
            long long x = (x_hash[r + 1] - (x_hash[l] * pow10[count_in_range]) % MOD + MOD) % MOD;

            // 3. Compute final answer for the query
            long long query_ans = (x * current_sum) % MOD;
            answer.push_back(query_ans);
        }

        return answer;
    }
};
