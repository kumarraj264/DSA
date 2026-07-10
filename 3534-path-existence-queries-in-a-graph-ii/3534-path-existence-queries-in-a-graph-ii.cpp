#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

class Solution {
public:
    vector<int> pathExistenceQueries(int n, vector<int>& nums, int maxDiff, vector<vector<int>>& queries) {
        // Step 1: Pair values with original indices and sort by value
        vector<pair<int, int>> sorted_nodes(n);
        for (int i = 0; i < n; ++i) {
            sorted_nodes[i] = {nums[i], i};
        }
        sort(sorted_nodes.begin(), sorted_nodes.end());

        // Map original node index to its position in the sorted array
        vector<int> orig_to_sorted(n);
        for (int i = 0; i < n; ++i) {
            orig_to_sorted[sorted_nodes[i].second] = i;
        }

        // LOG = 18 is sufficient since 2^17 > 10^5
        const int LOG = 18;
        vector<vector<int>> st(n, vector<int>(LOG));

        // Step 2: Use two pointers to find the farthest right jump from each sorted position
        int r = 0;
        for (int i = 0; i < n; ++i) {
            while (r + 1 < n && sorted_nodes[r + 1].first - sorted_nodes[i].first <= maxDiff) {
                r++;
            }
            st[i][0] = max(r, i);
        }

        // Step 3: Populate the binary lifting table
        for (int j = 1; j < LOG; ++j) {
            for (int i = 0; i < n; ++i) {
                st[i][j] = st[st[i][j - 1]][j - 1];
            }
        }

        // Step 4: Process queries
        vector<int> ans;
        ans.reserve(queries.size());

        for (const auto& q : queries) {
            int u = q[0];
            int v = q[1];

            if (u == v) {
                ans.push_back(0);
                continue;
            }

            // Convert original indices to sorted positions
            int a = orig_to_sorted[u];
            int b = orig_to_sorted[v];
            
            // Ensure we always jump from left-to-right (lower value to higher value)
            if (a > b) {
                swap(a, b);
            }

            int steps = 0;
            int curr = a;

            // Lift up as far right as possible without landing on or exceeding b
            for (int j = LOG - 1; j >= 0; --j) {
                if (st[curr][j] < b) {
                    curr = st[curr][j];
                    steps += (1 << j);
                }
            }

            // Check if one final single-hop can bridge onto or past b
            if (st[curr][0] >= b) {
                ans.push_back(steps + 1);
            } else {
                ans.push_back(-1); // Destination unreachable
            }
        }

        return ans;
    }
};
