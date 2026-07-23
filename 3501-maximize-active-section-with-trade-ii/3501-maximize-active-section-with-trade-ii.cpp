#include <vector>
#include <string>
#include <algorithm>
#include <cmath>

using namespace std;

class Solution {
private:
    struct ZeroBlock {
        int start, end, len;
    };

    // Sparse Table for O(1) Range Maximum Queries
    vector<vector<int>> st;
    vector<int> lg;

    void buildSparseTable(const vector<int>& arr) {
        int n = arr.size();
        if (n == 0) return;
        int max_log = log2(n) + 1;
        st.assign(max_log, vector<int>(n, 0));
        lg.assign(n + 1, 0);

        for (int i = 2; i <= n; i++) lg[i] = lg[i / 2] + 1;
        for (int i = 0; i < n; i++) st[0][i] = arr[i];

        for (int j = 1; j < max_log; j++) {
            for (int i = 0; i + (1 << j) <= n; i++) {
                st[j][i] = max(st[j - 1][i], st[j - 1][i + (1 << (j - 1))]);
            }
        }
    }

    int queryMax(int L, int R) {
        if (L > R) return 0;
        int j = lg[R - L + 1];
        return max(st[j][L], st[j][R - (1 << j) + 1]);
    }

public:
    vector<int> maxActiveSectionsAfterTrade(string s, vector<vector<int>>& queries) {
        int n = s.length();
        int baseOnes = 0;
        for (char c : s) if (c == '1') baseOnes++;

        // Step 1: Identify all contiguous '0' blocks
        vector<ZeroBlock> blocks;
        int i = 0;
        while (i < n) {
            if (s[i] == '0') {
                int start = i;
                while (i < n && s[i] == '0') i++;
                blocks.push_back({start, i - 1, i - start});
            } else {
                i++;
            }
        }

        int m = blocks.size();
        vector<int> answer;
        answer.reserve(queries.size());

        if (m == 0) {
            // No zero blocks mean no trade can ever happen
            return vector<int>(queries.size(), baseOnes);
        }

        // Step 2: Build adjacent pairs array for the Sparse Table
        vector<int> pairSums(max(0, m - 1), 0);
        for (int j = 0; j < m - 1; j++) {
            pairSums[j] = blocks[j].len + blocks[j + 1].len;
        }
        buildSparseTable(pairSums);

        // Step 3: Extract block starting coordinates for binary search mapping
        vector<int> blockStarts(m);
        for (int j = 0; j < m; j++) blockStarts[j] = blocks[j].start;

        // Step 4: Process each range query independently
        for (const auto& q : queries) {
            int ql = q[0], qr = q[1];

            // Find first block that finishes on or after ql
            int firstIdx = lower_bound(blocks.begin(), blocks.end(), ql, [](const ZeroBlock& b, int val) {
                return b.end < val;
            }) - blocks.begin();

            // Find last block that starts on or before qr
            int lastIdx = upper_bound(blockStarts.begin(), blockStarts.end(), qr) - blockStarts.begin() - 1;

            // If no blocks are enclosed or intersecting with the range
            if (firstIdx > lastIdx) {
                answer.push_back(baseOnes);
                continue;
            }

            // Calculate the actual visible lengths within the window
            int firstLen = min(blocks[firstIdx].end, qr) - max(blocks[firstIdx].start, ql) + 1;
            int lastLen = min(blocks[lastIdx].end, qr) - max(blocks[lastIdx].start, ql) + 1;

            int maxGain = 0;

            if (firstIdx == lastIdx) {
                // If only one zero block exists in range, we can't form an internal trade pair
                maxGain = 0; 
            } else if (firstIdx + 1 == lastIdx) {
                // Exactly two blocks intersect
                maxGain = firstLen + lastLen;
            } else {
                // Case A: Pair using first boundary block + its neighbor
                int gain1 = firstLen + blocks[firstIdx + 1].len;
                // Case B: Pair using last boundary block + its neighbor
                int gain2 = blocks[lastIdx - 1].len + lastLen;
                // Case C: Maximum pair sum entirely inside the middle untouched segments
                int gainMiddle = queryMax(firstIdx + 1, lastIdx - 2);

                maxGain = max({gain1, gain2, gainMiddle});
            }

            answer.push_back(baseOnes + maxGain);
        }

        return answer;
    }
};
