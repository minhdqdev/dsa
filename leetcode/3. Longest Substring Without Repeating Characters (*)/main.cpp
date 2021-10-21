class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int n = s.size();
        if(n == 0) return 0;
        int left = 0;
        int maxLength = 1;

        bool isUnique = false;
        int m; // index of s where the matching happens
        for(int i=1; i<n; i++){
            // there is no point to continue searching for a greater length.
            if(n - left < maxLength) break; 
            
            
            // check if s[left:i+1] is unique
            isUnique = true;
            for(int j=left; j<i; j++){
                if(s[i] == s[j]){
                    isUnique = false;
                    m = j;
                    break;
                }
            }
            
            if(isUnique){
                maxLength = max(maxLength, i-left+1);
            }
            else{
                // increase the left pointer until it is unique
                left = m + 1;
            }
        }
        
        return maxLength;
    }
};
