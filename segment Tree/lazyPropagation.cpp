#include<bits/stdc++.h>
using namespace std;

class SG{
    vector<int>st, lazy;

    public:
    SG(int n){
        st.resize(4*n);
        lazy.resize(4*n);
    }

    int getter(){
        return st[0];
    }

    void build(int ind, int low, int high, int arr[]){
        if(low == high){
            st[ind] = arr[low];
            return;
        }

        int mid = (low+high)>>1;

        build(ind*2+1, low, mid, arr);
        build(ind*2+2, mid+1, high, arr);

        st[ind] = st[ind*2+1] + st[ind*2+2];
    }

    void update(int ind, int low, int high, int l, int r,int val){
        //update the ind if it has lazy[ind] != 0 first
        //and then send the lazy update to down wards

        if(lazy[ind] != 0){
            st[ind] += lazy[ind];

            if(low != high){
                lazy[ind*2+1] += lazy[ind];
                lazy[ind*2+2] += lazy[ind];
            }

            lazy[ind] = 0;
        }

        //if no overlap return
        // l r low high || low high l r
        if(r < low || high < l) return;

        //if complete overlap

        if(l <= low && high <= r){
            st[ind] += val*(high-low+1);
            if(low != high){
                lazy[ind*2+1] += val;
                lazy[ind*2+2] += val;
            }
            return;
        }

        //partial overlap

        int mid = (low+high)>>1;

        update(ind*2+1, low, mid, l,r,val);
        update(ind*2+2, mid+1, high, l,r,val);

        st[ind] = st[ind*2+1] + st[ind*2+2];

    }

    int query(int ind, int low, int high, int l, int r){
        if(lazy[ind] != 0){
            st[ind] += lazy[ind];

            if(low != high){
                lazy[ind*2+1] += lazy[ind];
                lazy[ind*2+2] += lazy[ind];
            }

            lazy[ind] = 0;
        }
         //if no overlap return
        // l r low high || low high l r
        if(r < low || high < l) return 0;

        //if complete overlap

        if(l <= low && high <= r){
            return st[ind];
        }

        //partial overlap

        int mid = (low+high)>>1;

        return query(ind*2+1, low, mid, l,r) + query(ind*2+2, mid+1, high, l,r);


    }
};
