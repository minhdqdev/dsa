// The API isBadVersion is defined for you.
bool isBadVersion(int version);

class Solution {
public:
    int binary_search(int start, int end){
        int version = start + (end - start) / 2;
        
        if(isBadVersion(version)){
            if(start == end) return version;
            return binary_search(start, version);
        }
        else return binary_search(version+1, end);
    }
    
    int firstBadVersion(int n) {
        return binary_search(1, n);
    }
};