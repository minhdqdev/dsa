#include <vector>
using std::vector;

class Solution {
public:
    
    int binary_search(vector<int>& nums, int start, int end, int target){
        if(start > end) return -1;
        
        int mid_index = (end + start) / 2;
        int mid = nums[mid_index];
        
        if(target > mid) return binary_search(nums, mid_index+1, end, target);
        if(target < mid) return binary_search(nums, start, mid_index-1, target);
        return mid_index;
    }
    
    int search(vector<int>& nums, int target) {
        return binary_search(nums, 0, nums.size()-1, target);
    }
};
