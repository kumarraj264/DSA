class Solution {
public:
    int minimumPushes(string word) {
        int ans=0;
        int a=1;
        int n=word.size();
        while(n>=8){
            ans=ans+a*8;
            n=n-8;
            a++;
        }
        ans=ans+a*n;
        return ans;
    }
};