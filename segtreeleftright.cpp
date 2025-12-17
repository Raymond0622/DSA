// Leetcode question 2921
// Take left and right direction to take care of the 
// i < j condition, and use Seg tree for price[i] < price[j] condition
//where each node contains the value of maximum profit of a given range

class Solution {
public:
    
    int maxProfit(vector<int>& prices, vector<int>& profits) {
        vector<int> tree(4* 5001, 0);
        vector<int> tree2(4* 5001, 0);
        int n = prices.size();
        vector<int> left(n, -1), right(n, -1);
        for (int i = 0; i < n;i++) {
            left[i] = query(1, 0, 5000, 0, prices[i] - 1, tree);
            update(1, prices[i], 0, 5000, profits[i], tree);
        }
        for (int i = n - 1; i >=0;i--) {
            right[i] = query(1, 0, 5000, prices[i] + 1, 5000, tree2);
            update(1, prices[i], 0, 5000, profits[i], tree2);
        }
        int ans = -1;
        for (int i = 0;i < n;i++) {
            printf("%d %d\n", left[i], right[i]);
            if (left[i] != 0 && right[i] != 0) {
                ans = max(ans, profits[i] + left[i] + right[i]);
            }
        }
        return ans;
        
    }

    void update(int node, int x, int l, int r, int val, vector<int>& tree) {
        if (l == r) {
            tree[node] = max(tree[node], val);
            return;
        }
        int mid= (l + r) / 2;
        if (x <= mid) {
            update(2 *node, x, l, mid, val, tree);
        }
        else {
            update(2*node + 1, x, mid + 1, r, val, tree);
        }
        tree[node] = max(tree[node* 2], tree[node*2 +1 ]);
    }
    int query(int node, int l, int r, int ql, int qr, vector<int>& tree) {
        if (ql <= l && r <= qr) {
            return tree[node];
        }
        if (r < ql || l > qr ) {
            return 0;
        }
        int mid = (l + r) / 2;
        return max(query(2* node, l, mid, ql, qr, tree), 
            query(2 * node + 1, mid + 1, r, ql, qr, tree));
    }
};
