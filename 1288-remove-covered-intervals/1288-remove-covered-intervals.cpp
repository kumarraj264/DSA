class Solution {
public:
    int removeCoveredIntervals(std::vector<std::vector<int>>& intervals) {
        // Sort by start ascending, then by end descending
        std::sort(intervals.begin(), intervals.end(), [](const std::vector<int>& a, const std::vector<int>& b) {
            return a[0] == b[0] ? a[1] > b[1] : a[0] < b[0];
        });
        
        int remainingCount = 0;
        int prevEnd = 0;
        
        for (const auto& interval : intervals) {
            // If current end extends further, it's not covered
            if (interval[1] > prevEnd) {
                remainingCount++;
                prevEnd = interval[1];
            }
        }
        return remainingCount;
    }
};
