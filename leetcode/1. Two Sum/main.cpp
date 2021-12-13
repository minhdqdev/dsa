class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        vector<int> sorted;
        for(int i=0; i<nums.size(); i++) sorted.push_back(nums[i]);
        sort(sorted.begin(), sorted.end());
        int left = 0;
        int right = nums.size() - 1;
        
        vector<int> res = {-1, -1};
        int a, b;
        int curSum = 0;
        while(left != right){
            curSum = sorted[left] + sorted[right];
            if(curSum > target) right -= 1;
            else if(curSum < target) left += 1;
            else{
                a = sorted[left]; b = sorted[right]; break;
            }
        }
        
        for(int i=0; i<nums.size(); i++){
            if(res[0] == -1 && a == nums[i]){
                res[0] = i; continue;
            }
            if(res[1] == -1 && b == nums[i]){
                res[1] = i; continue;
            }
        }
        
        return res;
    }
};