// my own answer

class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int m = nums[0];
        int c = nums[0];
        for(int i=1; i<nums.size(); i++){
            c = (c < 0) ? nums[i] : c + nums[i];
            m = max(c, m);
        }
        return m;
    }
};