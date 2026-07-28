class Solution {
public:
    int maxArea(vector<int>& height) {
        int maxwater=0;
        int i=0;
        int j=height.size()-1;
        while(i!=j){
            int length=min(height[i],height[j]);
            int volume=(j-i)*length;
            maxwater=max(maxwater, volume);
            if(height[i]<=height[j]){
                i++;
            }
            else{
                j--;
            }
        }
        return maxwater;
    }
};