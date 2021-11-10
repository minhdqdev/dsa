class Solution {
public:
    vector<vector<int>> combine(int n, int k) {
        vector<vector<int>> result;
        vector<int> com;
        for(int i=1; i<=k; i++) com.push_back(i);
        
        int pointer = k-1;
        bool valid = false;
        while(true){
            // add to result
            result.push_back(com);
            
            // get the next combination
            pointer = k-1;
            valid = false;
            while(pointer != -1){
                if(com[pointer] < n - (k - 1 - pointer)){ // can be increased
                    valid = true;
                    com[pointer] += 1;
                    
                    for(int i=pointer+1; i<k; i++) com[i] = com[i-1] + 1; // reset all elements after pointer
                    break; // have a new combination
                }
                else pointer -= 1;
            }
            if(!valid) break;
        }
        
        return result;
    }
};