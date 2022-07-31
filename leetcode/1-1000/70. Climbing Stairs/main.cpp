class Solution {
public:
    int climbStairs(int n) {
        if(n == 1) return 1;
        else if(n == 2) return 2;
        
        int lookup[n];
        lookup[0] = 1;
        lookup[1] = 2;
        
        for(int i=3; i<=n; i++){
            lookup[i-1] = lookup[i-2] + lookup[i-3];
        }
        
        return lookup[n-1];
    }
};