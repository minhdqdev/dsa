class Solution {
public:
    void build_perm(vector<vector<int>>& res, vector<int> perm, set<int> choices){
        if(choices.empty()){
            res.push_back(perm); return;
        }
        set<int, greater<int> >::iterator ptr;
        
        for(ptr = choices.begin(); ptr != choices.end(); ptr++){
            set<int> newChoices(choices.begin(), choices.end());
            vector<int> tempPerm(perm.begin(), perm.end());
            newChoices.erase(*ptr);
            
            tempPerm.push_back(*ptr);
            build_perm(res, tempPerm, newChoices);
        }
    }
    
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>> result;
        vector<int> perm;
        set<int> s;
        for(int i=0; i<nums.size(); i++) s.insert(nums[i]);
        
        build_perm(result, perm, s);
        return result;
    }
};