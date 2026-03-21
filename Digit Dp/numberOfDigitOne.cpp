class Solution {

    int solve(string &s,int ind, int tight, int cnt, int dp[10][2][10]){

        if(ind == s.size()) return cnt;

        if(dp[ind][tight][cnt] != -1){
            // cout<<ind<<" "<<tight<<" "<<cnt<<endl;
            return dp[ind][tight][cnt];
        } 

        int limit = tight ? s[ind]-'0' : 9; //if tight is 1 : you can put maximum s[ind]-'0' at that ind otherwise 9

        int ans = 0;

        for(int i = 0; i <= limit; i++){

            int updateCnt = cnt + (i == 1 ? 1 : 0);

            ans += solve(s, ind+1, (tight & (i == s[ind]-'0')), updateCnt,dp); 
        }   //if tight is false or i == s[ind]-'0' then all the subproblems will be having tight = false 

         cout<<ind<<" "<<tight<<" "<<cnt<<" : "<<ans<<endl;
        // cout<<cnt<<endl;

        return dp[ind][tight][cnt] = ans;
    }


public:
    int countDigitOne(int n) {
        string s  = to_string(n);
        int dp[10][2][10];
        memset(dp, -1, sizeof(dp)); // (dest, initial value for each byte, size in byte)//( -1 = 1111 1111)
        return solve(s, 0,1,0, dp); //solve(ind, tight, cnt);
    }
};
