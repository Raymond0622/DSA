//Leetcode 2836

class Solution {
public:
    long long getMaxFunctionValue(vector<int>& receiver, long long k) {
        int maxxy = log2(k);
        int n = receiver.size();
        vector<vector<int>> up(n, vector<int>(maxxy + 1, -1));
        vector<vector<long long>> dp(n, vector<long long>(maxxy + 1, 0));
        for (int j = 0; j < n;j++) {
            up[j][0] = receiver[j];
            dp[j][0] = receiver[j] + j;
        }
        for (int i = 1; i <= maxxy;i++) {
            for (int j = 0; j < n;j++) {
                if (up[j][i - 1] != -1) {
                    dp[j][i] = dp[j][i - 1] + dp[up[j][i - 1]][i - 1] - up[j][i - 1];
                    up[j][i] = up[up[j][i - 1]][i - 1];
                }
            }
        }
        long long ans = 0;
        for (int j = 0; j < n;j++) {
            int node = j;
            long long tot = 0;
            for (long long i = maxxy; i >= 0;i--) {
                if ((k >> i) & 1) {
                    tot += dp[node][i] - up[node][i];
                    node = up[node][i];
                }
            }
            tot += node;
            ans = ans > tot ? ans : tot;
        }
        return ans;
    }
};
