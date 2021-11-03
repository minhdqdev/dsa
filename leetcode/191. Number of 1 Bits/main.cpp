class Solution {
public:
    int hammingWeight(uint32_t n) {
        int count = 0;
        
        while(true){
            if(n == 1) return count += 1;
            else if(n == 0) return count;
            
            if(n % 2 == 1) count += 1;
            n = n >> 1;
        }
    }
};