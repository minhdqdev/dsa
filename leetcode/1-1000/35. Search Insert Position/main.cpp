class Solution {
public:
    int binary_search(vector<int>& nums, int start, int end, int target){
        if(start > end) return start;
        
        int mid_index = start + (end-start)/2;
        int mid = nums[mid_index];
        
        if(target > mid) return binary_search(nums, mid_index+1, end, target);
        else if(target < mid) return binary_search(nums, start, mid_index-1, target);
        else return mid_index;
    }
    
    int searchInsert(vector<int>& nums, int target) {
        return binary_search(nums, 0, nums.size()-1, target);
    }
};