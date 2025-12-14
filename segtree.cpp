// Range Query Sum Leetcode 307

class NumArray {
public:
    int n;
    vector<int> tree;
    NumArray(vector<int>& nums) {
        n = nums.size();
        tree.resize(4 * n);
        build(1, 0, n - 1, nums);
    
    }
    void build(int node, int l, int r, vector<int>& nums) {
        if (l == r) {
            tree[node] = nums[l];
            return;
        }
        int mid = (l + r) / 2;
        build(node * 2, l, mid, nums);
        build(node* 2 + 1, mid + 1, r, nums);
        tree[node] = tree[node * 2] + tree[node * 2 + 1];
    }
    void update(int index, int val) {
        update(index, 1, 0, n - 1, val);
    }
    void update(int idx, int node, int l, int r, int val) {
        if (l == r) {
            tree[node] = val;
            return;
        }
        int mid = (l + r) / 2;
        if (idx <= mid) {
            update(idx, node * 2, l, mid, val);
        }
        else {
            update(idx, node *2 + 1, mid + 1, r, val);
        }
        tree[node] = tree[node * 2] + tree[node*2 + 1];
    }
    
    int sumRange(int left, int right) {
        return sumRange(1, 0, n - 1, left, right);
    }
    int sumRange(int node, int l, int r, int left, int right) {
        if (l >= left && r <= right) {
            return tree[node];
        }
        if (right < l || left > r) {
            return 0;
        }
        int mid = (l + r) / 2;
        return sumRange(node * 2, l, mid, left, right) + 
            sumRange(node * 2 + 1, mid + 1, r, left, right);
    }
};

/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray* obj = new NumArray(nums);
 * obj->update(index,val);
 * int param_2 = obj->sumRange(left,right);
 */
