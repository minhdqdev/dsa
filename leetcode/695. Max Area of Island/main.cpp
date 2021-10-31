#include <vector>
#include <queue>

using namespace std;

class Solution {
public:
    int maxAreaOfIsland(vector<vector<int>>& grid) {
        int maxArea = 0;
        int m = grid.size();
        int n = grid[0].size();
        
        queue<pair<int, int>> q;
        vector<vector<bool>> visited(m, vector<bool>(n, false));
        pair<int, int> p;
        
        int area = 0;
        for(int y=0; y<m; y++){
            for(int x=0; x<n; x++){
                if(grid[y][x] == 1 && !visited[y][x]){
                    area = 0;
                    q.push({x, y});
                    visited[y][x] = true;
                    
                    while(!q.empty()){
                        // pop
                        p.first = q.front().first;
                        p.second = q.front().second;
                        q.pop();
                        
                        area += 1;
                        
                        // search adj
                        if(p.first > 0 && grid[p.second][p.first-1] == 1 && !visited[p.second][p.first-1]){
                            q.push({p.first-1, p.second});
                            visited[p.second][p.first-1] = true;
                        }   
                        if(p.first < n-1 && grid[p.second][p.first+1] == 1  && !visited[p.second][p.first+1]){
                            q.push({p.first+1, p.second});
                            visited[p.second][p.first+1] = true;
                        }
                        if(p.second > 0 && grid[p.second-1][p.first] == 1  && !visited[p.second-1][p.first]){
                            q.push({p.first, p.second-1});
                            visited[p.second-1][p.first] = true;
                        }
                        if(p.second < m-1 && grid[p.second+1][p.first] == 1  && !visited[p.second+1][p.first]){
                            q.push({p.first, p.second+1});
                            visited[p.second+1][p.first] = true;
                        }       
                    }
                    maxArea = max(maxArea, area);
                };
            }
        }
        
        return maxArea;
    }
};