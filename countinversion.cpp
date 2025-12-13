// Leetcode 3739, Count # of Subarrays with majority elements of target
// Use prefix sums 

class Solution {
public:
    long long ans = 0;
    long long countMajoritySubarrays(vector<int>& nums, int target) {
        vector<int> prefix = {0};
        for (auto& n : nums) {
            prefix.push_back(prefix.back() + (n == target ? 1 : -1));
        }
        merge(0, nums.size(), prefix);
        return ans;
    }
    void merge(int l, int r, vector<int>& prefix) {
        if (l >= r) {
            return;
        }
        vector<int> store;
        int mid = (l + r) / 2;
        merge(l, mid, prefix);
        merge(mid + 1, r, prefix);
        long long j = l, i = mid + 1, curr = 0;
        while (j <= mid && i <= r) {
            if (prefix[i] > prefix[j]) {
                store.push_back(prefix[j]);
                curr++;
                j++;
            }
            else {
                store.push_back(prefix[i]);
                i++;
                ans += curr;
            }
        }
        while (i <= r) {
            store.push_back(prefix[i]);
            ans += curr;
            i++;
        }
        while (j <=mid) {
            store.push_back(prefix[j]);
            j++;
        }
        for (int i = l; i <= r;i++) {
            prefix[i] = store[i - l];
        }
    }
};
