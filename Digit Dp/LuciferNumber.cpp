#include<bits/stdc++.h>
using namespace std;

using LL = long long;

int dp[11][2][90][90];

bool isPrime(int n){
    if(n < 2) return 0;
    if(n == 2) return 1;
    
    for(int i = 2; i*i <= n; i++){
        if(n%i == 0) return 0;
    }
    return 1;
}

LL digitDp(int ind, int tight, int evenSum, int oddSum, string&s){
    
    if(ind == 0){
        if(isPrime(evenSum-oddSum)) return 1;

        // if((evenSum-oddSum) == 1) return 1; //RA-ONE problem
        return 0;
    }
    
    if(dp[s.size()-ind][tight][evenSum][oddSum] != -1) return dp[s.size()-ind][tight][evenSum][oddSum];

    int limit = tight ? s[s.size()-ind]-'0' : 9;

    int res = 0;
    for(int i = 0; i <= limit; i++){
        
        if(ind&1) oddSum += i;
        else evenSum += i;
        
        res += digitDp(ind-1, tight & (i == s[s.size()-ind]-'0'), evenSum, oddSum, s);
        if(ind&1) oddSum -= i;
        else evenSum -= i;
    }
    
    return dp[s.size()-ind][tight][evenSum][oddSum] = res;
}


void solve()
{
    int tt;
    cin>>tt;
    while(tt--){
        int low, high;
        cin>>low>>high;

        string s1 = to_string(high);
        string s2 = to_string(low-1);

        memset(dp, -1, sizeof(dp));

        int a = digitDp(s1.size(),1,0,0,s1);

        memset(dp, -1, sizeof(dp));

        int b = digitDp(s2.size(),1,0,0,s2);

        cout<<a-b<<'\n';        

    }   
}

int main()
{
#ifndef ONLINE_JUDGE
freopen("input.txt", "r", stdin);
freopen("output.txt", "w", stdout);
#endif
solve();
    return 0;
}
