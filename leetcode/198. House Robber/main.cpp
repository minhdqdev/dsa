class Solution {
public:
    int rob(vector<int>& nums) {
        int maxMoney = 1;
        
        int n = nums.size();
        
        if(n == 1) return nums[0];
        else if(n == 2) return max(nums[0], nums[1]);
        
        int lookup[nums.size()];
        
        // vector<int> lookup;
        // for(int i=0; i<n; i++) lookup.push_back(-1);
        lookup[0] = nums[0];
        lookup[1] = max(nums[0], nums[1]);
        
        for(int i=3; i<=n; i++){
            lookup[i-1] = max(lookup[i-3] + nums[i-1], lookup[i-2]);
        }
        
        return lookup[n-1];
    }
};
