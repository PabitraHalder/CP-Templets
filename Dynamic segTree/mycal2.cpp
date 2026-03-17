// using LL long long;
struct node{
    int val, lazy;
    node*left,*right;
    node(){
        lazy = 0;
        val = 0;
        left = NULL;
        right = NULL;
    }
};

class SegmentTree {
    public :
    node *root;
    int low, high;

    SegmentTree(){
        low = 0;
        high = 1e9-1;
        root = new node();
    }

    void propagateDown(node* root){
        if(!root->left) root->left = new node();
        if(!root->right) root->right = new node();

        root->left->val += root->lazy;
        root->left->lazy += root->lazy;

        root->right->val += root->lazy;
        root->right->lazy += root->lazy;

        root->lazy = 0;
    }

    void update(node* root, int currL, int currH, int l, int r){


        if(currL > r || currH < l) return;

        if(currL >= l && currH <= r){
            root->val += 1;
            root->lazy += 1;
            return;
        }
        propagateDown(root);

        int mid = currL + (currH - currL)/2;

        if(!root->left) root->left = new node();
        if(!root->right) root->right = new node();

        update(root->left, currL, mid, l, r);
        update(root->right, mid+1, currH, l , r);

        root->val = max(root->left->val, root->right->val);
    }

    int query(node *root, int currL, int currH, int l, int r){
        if(currL > r || currH < l) return 0;

        if(currL >= l && currH <= r){
            return root->val;
        }
        propagateDown(root);

        int mid = currL + (currH - currL)/2;

        return max(query(root->left, currL, mid, l, r),
        query(root->right, mid+1, currH, l , r));
    }

};

class MyCalendarTwo {
public:
SegmentTree segT;
    MyCalendarTwo() {
        
    }
    
    bool book(int startTime, int endTime) {
        if(segT.query(segT.root, segT.low, segT.high, startTime, endTime-1) >= 2) return false;

        segT.update(segT.root, segT.low, segT.high, startTime, endTime-1);
        return true;
    }
};

/**
 * Your MyCalendarTwo object will be instantiated and called as such:
 * MyCalendarTwo* obj = new MyCalendarTwo();
 * bool param_1 = obj->book(startTime,endTime);
 */
