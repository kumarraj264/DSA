class Solution {
public:
    vector<int> arrayRankTransform(vector<int>& arr) {
        vector<int>copy=arr;
        sort(copy.begin(),copy.end());
        unordered_map<int,int>hash;
        for(int num:copy){
            if(hash.find(num)==hash.end()){
                hash[num]=hash.size()+1;
            }
        }
        for(int& num:arr){
            num=hash[num];
        }
        return arr;
    }
};