// Leetcode question 3479
// Using maximum segment tree
// Create tree in which each node contains the maximum of a given range

class Solution {
public:
    vector<int> tree;
    int numOfUnplacedFruits(vector<int>& fruits, vector<int>& baskets) {
        int n = fruits.size();
        tree.resize(4*n);
        int ans = 0;
        build(1, 0, n - 1, baskets);
        for (auto& f : fruits) {
            int idx = findpos(1, 0, n-1, f);
            if (idx != -1) {
                update(1, idx, 0, n - 1);
            }
            else {
                ans++;
            }
        }
        return ans;

    }
    void build(int node, int l, int r, vector<int>& fruits) {
        if (l == r) {
            tree[node] = fruits[l];
            return;
        }
        int mid = (l + r) / 2;
        build(2 * node, l, mid, fruits);
        build(2* node + 1, mid + 1, r, fruits);
        tree[node] = max(tree[2*node], tree[2*node + 1]);
    }
    int findpos(int node, int l, int r, int val) {
        if (tree[node] < val) {
            return -1;
        }
        if (l == r) {
            return l;
        }
        int mid = (l + r) /2;
        if (tree[2*node] >= val) {
            return findpos(2*node, l, mid, val);
        }
        return findpos(2*node + 1, mid + 1, r, val);
    }
    void update(int node, int idx, int l, int r) {
        if (l == r) {
            tree[node] = 0;
            return;
        }
        int mid = (l + r) /2;
        if (idx <= mid)
            update(2*node, idx, l, mid);
        else
            update(2*node + 1, idx, mid + 1, r);
        tree[node] = max(tree[2*node], tree[2*node + 1]);
    }
};
