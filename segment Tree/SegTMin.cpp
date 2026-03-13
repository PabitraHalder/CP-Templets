#include<bits/stdc++.h>
using namespace std;
// int N = 4*n;


class SEGTree{
    vector<int>segT;

    public:
    SEGTree(int n){
        segT.resize(n);
    }
    void build(int low, int high,int ind, int arr[]){
        // if (ind >= N) cout << "Out of bounds access at index: " << ind << endl;
        if(low == high){
            segT[ind] = arr[low];
            return;
        }
        int mid = (low+high)>>1;
        int ind1 = ind*2+1;
        int ind2 = ind*2+2;
        build(low, mid, ind1, arr);
        build(mid+1, high, ind2, arr);

        segT[ind] = min(segT[ind1], segT[ind2]);

        return;
}


//TC = O(logN)


int query(int low, int high, int ind, int x,int y){

    if(x > high || y < low) return INT_MAX; //no overlap

    if(x <= low && y >= high) return segT[ind]; //complete overlap

    //Partial overlap

    int ind1 = ind*2+1;
    int ind2 = ind*2+2;
    int mid = (low+high)>>1;
    int a1 = query(low, mid, ind1, x,y);
    int a2 = query(mid+1, high, ind2, x,y);

    return min(a1,a2);
}

//TC = O(logN)

void update(int i, int val, int ind, int low, int high){
    if(low == high){
        segT[ind] = val;
        return;
    }

    int mid = (low+high)>>1;
    if(i <= mid) update(i, val, ind*2+1, low, mid);
    else update(i, val, ind*2+2, mid+1, high);

    segT[ind] = min(segT[ind*2+1], segT[ind*2+2]);
}

};

//TC = O(N)


void solve(){
    int n;
    cin>>n;
    int arr[n];

    for(int i = 0; i < n; i++){
        cin>>arr[i];
    }

    SEGTree sg(4*n);

    sg.build(0, n-1, 0, arr);

    int q;
    cin>>q;
    while(q--){
        int type;
        cin>>type;
        if(type == 1){

            int l, r;
            cin>>l>>r;
    
            cout<<sg.query(0,n-1,0,l,r)<<endl;
        }
        else{
            int ind, val;
            cin>>ind>>val;
            sg.update(ind, val, 0,0,n-1);
            cout<<"updated"<<endl;
        }
    }
    
}

int main(){

    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif
 solve();
}
