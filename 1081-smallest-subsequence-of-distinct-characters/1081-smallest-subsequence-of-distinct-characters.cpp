class Solution {
public:
    string smallestSubsequence(string s) {
        vector<int> last_occ(26, 0);
        for (int i = 0; i < s.length(); i++) {
            last_occ[s[i] - 'a'] = i;
        }
        
        string result = "";
        vector<bool> visited(26, false);
        
        for (int i = 0; i < s.length(); i++) {
            char curr = s[i];
            if (visited[curr - 'a']) continue;
            
            while (!result.empty() && result.back() > curr && last_occ[result.back() - 'a'] > i) {
                visited[result.back() - 'a'] = false;
                result.pop_back();
            }
            
            result.push_back(curr);
            visited[curr - 'a'] = true;
        }
        
        return result;
    }
};
