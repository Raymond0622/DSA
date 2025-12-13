class Solution {
public:
    std::unordered_map<int, std::vector<pair<int, int>>> map;
    std::vector<vector<int>> freq;
    std::vector<vector<int>> u;
    std::vector<int> depth;
    vector<int> minOperationsQueries(int n, vector<vector<int>>& edges, vector<vector<int>>& queries) {
        
        for (auto& v : edges) {
            map[v[0]].push_back(make_pair(v[1], v[2]));
            map[v[1]].push_back(make_pair(v[0], v[2]));
        }
        freq.assign(n, vector<int>(27, 0));
        u.assign(n, vector<int>(20, -1));
        vector<int> ans;
        depth.assign(n, 0);
        dfs(0, -1);
        int a, b, l, curr, tot, maxxy;
        for (auto& e : queries) {
            a = e[0], b = e[1];
            l = lca(a, b);
            tot = 0, maxxy = -1;
            for (int i = 0; i < 27;i++) {
                curr = freq[a][i] + freq[b][i] - 2 * freq[l][i];
                tot += curr;
                maxxy = curr > maxxy ? curr : maxxy;
            }
            ans.push_back(tot - maxxy);
        }
        return ans;
        
    }

    int lca(int a, int b) {
        if (depth[a] < depth[b]) {
            swap(a, b);
        }
        int diff = depth[a] - depth[b];
        for (int i = 0; i < 20 && a != -1; i++) {
            if (diff & (1 << i)) {
                a = u[a][i];
            }
        }
        if (a == b) {
            return a;
        }
        for (int i = 19;i >=0 ;i--) {
            if (u[a][i] != u[b][i]) {
                a = u[a][i];
                b = u[b][i];
            }
        }
        return u[a][0];
    }

    void dfs(int node, int prev) {
        u[node][0] = prev;
        for (int i = 1; i < 20;i++) {
            if (u[node][i - 1] != -1) {
                u[node][i] = u[u[node][i - 1]][i - 1];
            }
        }
        int p, w;
        for (auto& e : map[node]) {
            p = e.first;
            w = e.second;
            if (p != prev) {
                if (node != -1) {
                    for (int i = 0; i < 27;i++) {
                        freq[p][i] = freq[node][i] + (w == i);
                    }
                }
                depth[p] = 1 + depth[node];
                dfs(p, node);
            }

        }
    } 
};
