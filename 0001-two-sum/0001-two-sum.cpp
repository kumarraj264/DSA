class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        int n=nums.size();
        vector<int> res;
        map<int,int> mpp;
        for(int i=0;i<n;i++){
            int a=nums[i];
            int more=target-a;
            if(mpp.find(more)!=mpp.end()){
                res={i,mpp[more]};
                break;
            }
            mpp[a]=i;
        }
        return res;
    }
};