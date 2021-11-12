/*
DP

*/

class Solution {
public:
    int minimumTotal(vector<vector<int>>& triangle) {
        int n = triangle.size();
        
        if(n == 1) return triangle[0][0];
        
        vector<vector<int>> l;
        for(int i=0; i<n; i++){
            vector<int> row;
            for(int j=0; j<i+1; j++) row.push_back(0);
            l.push_back(row);
        }
        l[0][0] = triangle[0][0];

        for(int k=1; k<n; k++){
            l[k][0] = triangle[k][0] + l[k-1][0];
            l[k][k] = triangle[k][k] + l[k-1][k-1];
            for(int j=1; j<k; j++){
                l[k][j] = triangle[k][j] + min(l[k-1][j], l[k-1][j-1]);
            }
        }
        
        int minCost = l[n-1][0];
        for(int j=1; j<n; j++){
            if(l[n-1][j] < minCost) minCost = l[n-1][j];
        }
        
        return minCost;
    }
};
