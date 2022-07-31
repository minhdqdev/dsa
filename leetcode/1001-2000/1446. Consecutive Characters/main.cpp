class Solution {
public:
    int maxPower(string s) {
        int res = 1;
        
        char a = s[0];
        
        int cur = 1;
        for(int i=1; i<s.size(); i++){
            if(s[i] == a){
                cur += 1;
                
                if(cur > res) res = cur;
            }
            else{
                cur = 1;
                a = s[i];
            }
        }
        
        return res;
    }
};