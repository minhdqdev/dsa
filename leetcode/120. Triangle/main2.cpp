/*
Not optimal solution

TLE
*/

#include <vector>
#include <iostream>

using namespace std;

class Solution {
public:    
    int minimumTotal(vector<vector<int>>& triangle) {
        int n = triangle.size();
        
        int pos[triangle.size()];
        int l[triangle.size()];
        
        l[0] = triangle[0][0];
        for(int i=1; i<n; i++) l[i] = triangle[i][0] + l[i-1];
        for(int i=0; i<n; i++) pos[i] = 0;    
        
        
        int minCost = l[n-1];
        
        bool found;
        int pointer;
        while(true){
            // get next combination
            found = false;
            pointer = n-1;
            
            while(pointer != 0){
                // check if pos[pointer] can be increased
                if(pos[pointer] < pointer){
                    if(pos[pointer] + 1 - pos[pointer-1] <= 1){ // can be increased
                        pos[pointer] += 1;
                        found = true;
                        for(int i=pointer+1; i<n; i++) pos[i] = pos[pointer];
                        break;
                    }
                }
                
                pointer -= 1;
            }
            
            if(!found) break;
            
            // recalculate lookup table
            for(int i=pointer; i<n; i++){
                l[i] = l[i-1] + triangle[i][pos[i]];
            }
            if(l[n-1] < minCost) minCost = l[n-1];
        }
        
        return minCost;
    }
};

int main(){
    vector<vector<int>> triangle = {{2}, {3,4}, {6,5,7}, {4,1,8,3}};

    for(int i=0; i<triangle.size(); i++){
        for(int j=0; j<triangle[i].size(); j++){
            cout << triangle[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;

    Solution solution = Solution();

    cout << solution.minimumTotal(triangle) << endl;
}