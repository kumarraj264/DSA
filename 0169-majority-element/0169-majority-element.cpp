class Solution {
public:
    int majorityElement(vector<int>& nums) {
        int i=1;
        int el=nums[0];
        int count=1;
        while(i<nums.size()){
            if(nums[i]==el){
                count++;
            }
            else{
                count--;
            }
            if(count==0){
                el=nums[i];
                count=1;
            }
            i++;
        }
        return el;
    }
};