#include <vector>

class Solution {
public:
    int countCompleteComponents(int n, std::vector<std::vector<int>>& edges) {
        // Build the adjacency list
        std::vector<std::vector<int>> adj(n);
        for (const auto& edge : edges) {
            adj[edge[0]].push_back(edge[1]);
            adj[edge[1]].push_back(edge[0]);
        }

        std::vector<bool> visited(n, false);
        int completeComponentsCount = 0;

        for (int i = 0; i < n; ++i) {
            if (!visited[i]) {
                std::vector<int> componentNodes;
                std::vector<int> stack;

                // Standard DFS traversal
                stack.push_back(i);
                visited[i] = true;

                while (!stack.empty()) {
                    int curr = stack.back();
                    stack.pop_back();
                    componentNodes.push_back(curr);

                    for (int neighbor : adj[curr]) {
                        if (!visited[neighbor]) {
                            visited[neighbor] = true;
                            stack.push_back(neighbor);
                        }
                    }
                }

                // Verify completeness: each node needs exactly (V - 1) neighbors
                int numNodes = componentNodes.size();
                bool isComplete = true;

                for (int node : componentNodes) {
                    if (adj[node].size() != numNodes - 1) {
                        isComplete = false;
                        break;
                    }
                }

                if (isComplete) {
                    completeComponentsCount++;
                }
            }
        }

        return completeComponentsCount;
    }
};
