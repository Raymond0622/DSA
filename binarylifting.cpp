class TreeAncestor {
public:
    TreeAncestor(int n, vector<int>& parent) {
        up.assign(n, vector<int>(20, -1));
        for (int i = 0; i < n;i++) {
            up[i][0] = parent[i];
        }
        for (int j = 1;j < 20;j++) {
            for (int i = 0; i < n;i++) {
                if (up[i][j - 1] != -1)
                    up[i][j] = up[up[i][j - 1]][j - 1];
                else
                    up[i][j] = -1;
            }
        }
    }
    int getKthAncestor(int node, int k) {
        for (int i = 0;i < 20;i++) {
            if (node == -1) {
                return -1;
            }
            if (k & (1 << i)) {
                node = up[node][i];
            }
        }
        return node;
        
    }
    vector<vector<int>> up;
};
