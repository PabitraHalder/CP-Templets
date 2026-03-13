#include<bits/stdc++.h>
using namespace std;

//use a frequency arr to store the frequency og each el
//use seg tree to calculate prefix sum 
//now for each element add the sum before that el and update it

class Solution {
    
    private:
    
    void build(int ind, int low, int high, vector<int>&freq, vector<int>&seg){
        
        if(low == high){
            seg[ind] = freq[low];
            return;
        }
        
        int mid = (low+high)/2;
        
        build(ind*2+1, low, mid, freq, seg);
        build(ind*2+2, mid+1, high, freq, seg);
        
        seg[ind] = seg[ind*2+1] + seg[ind*2+2];
    }
    
    void update(int ind, int low, int high, int i, int val,vector<int>&seg){
        
        if(low == high){
            seg[ind] -= val;
            return;
        }
        
        int mid = (low+high)/2;
        
        if(i <= mid) update(ind*2+1, low, mid, i, val,seg);
        else update(ind*2+2, mid+1, high, i, val,seg);
        
        seg[ind] = seg[ind*2+1] + seg[ind*2+2];
    }
    
    int query(int ind, int low, int high, int l, int r, vector<int>&seg){
        if(r < low || high < l) return 0;
        
        if(low >= l && high <= r) return seg[ind];
        
        int mid = (low+high)/2;
        
        return query(ind*2+1, low, mid, l,r,seg) + query(ind*2+2, mid+1, high, l, r, seg);
        
    }
    
    
  public:
    int inversionCount(vector<int> &arr) {
        // Code Here
        int maxi = *max_element(arr.begin(), arr.end());
        // cout<<maxi<<endl;
        vector<int>freq(maxi+1);
        
        for(int i : arr) freq[i]++;
        
        vector<int>seg(4*maxi+1);
        build(0,1,maxi, freq, seg);
        // cout<<seg[0]<<endl;
        int ans = 0;
        
        for(int i : arr){
            ans += query(0, 1, maxi, 1, i-1, seg);
            update(0,1,maxi, i, 1, seg);
        }
        
        return ans;
        
    }
};
