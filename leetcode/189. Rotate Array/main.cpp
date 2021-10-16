#include <vector>
using namespace std;

class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        int n = nums.size();
        int steps = k % n;
        
        if(steps == 0) return;
        
        int a[steps];
        
        for(int i=0; i<steps; i++){
            a[i] = nums[n-steps+i];
        }
        
        for(int i=n-steps-1; i>-1; i--){
            nums[i+steps] = nums[i];
        }
        
        for(int i=0; i<steps; i++){
            nums[i] = a[i];
        }
    }
};

