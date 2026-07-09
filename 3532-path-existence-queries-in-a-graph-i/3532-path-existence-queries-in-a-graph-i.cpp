class Solution {
public:
    std::vector<bool> pathExistenceQueries(int n, std::vector<int>& nums, int maxDiff, std::vector<std::vector<int>>& queries) {
        // Step 1: Assign a component ID to each node
        std::vector<int> component_id(n, 0);
        int current_id = 0;
        
        for (int i = 1; i < n; ++i) {
            // Since nums is sorted, nums[i] >= nums[i-1]
            if (nums[i] - nums[i - 1] > maxDiff) {
                current_id++; // Start a new component group
            }
            component_id[i] = current_id;
        }
        
        // Step 2: Process each query in O(1) time
        std::vector<bool> answer;
        answer.reserve(queries.size());
        
        for (const auto& query : queries) {
            int u = query[0];
            int v = query[1];
            // If they share the same component ID, a valid path exists
            answer.push_back(component_id[u] == component_id[v]);
        }
        
        return answer;
    }
};
