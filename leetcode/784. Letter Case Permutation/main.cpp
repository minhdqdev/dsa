class Solution {
public:
    void buildPerm(vector<string>& res, string perm, int pos, string& s){
        bool found = false;
        while(pos < s.size()){
            if(isalpha(s[pos])){
                found = true; break;
            }
            else{
                perm.push_back(s[pos]);
            }
            pos++;
        }
        if(!found){
            res.push_back(perm); return;
        }
        
        string perm1(perm.begin(), perm.end());
        perm1.push_back(tolower(s[pos]));
        string perm2(perm.begin(), perm.end());
        perm2.push_back(toupper(s[pos]));
        
        buildPerm(res, perm1, pos+1, s);
        buildPerm(res, perm2, pos+1, s);
    }
    
    vector<string> letterCasePermutation(string s) {
        vector<string> result;
        string perm = "";
        
        buildPerm(result, perm, 0, s);
        
        return result;
    }
};