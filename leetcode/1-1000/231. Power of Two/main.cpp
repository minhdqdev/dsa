class Solution {
public:
    bool isPowerOfTwo(int n) {
        if(n == 1) return true;
        else if(n < 1) return false;
        else if(n % 2 != 0) return false;
        
        while(true){
            n = n >> 1;
            if(n == 1) return true;
            else if(n % 2 != 0) return false;
        }
    }
};