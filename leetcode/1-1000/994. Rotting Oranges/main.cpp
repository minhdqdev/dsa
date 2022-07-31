#include <vector>
#include <iostream>

using namespace std;

int orangesRotting(vector<vector<int>>& grid) {
    int m = grid.size();
    int n = grid[0].size();
    int minutes = 0;
    
    bool haveRotten = false; // true if there is at least 1 orange is rotten in a single minute
    bool stillHaveFresh = false; // true if there is at least 1 orange is still fresh after a single minute
    while(true){
        haveRotten = false;
        stillHaveFresh = false;
        for(int y=0; y<m; y++){
            for(int x=0; x<n; x++){
                
                if(grid[y][x] == 1){
                    // update to 3 if it will be rotten after this minute

                    if(x > 0){
                        if(grid[y][x-1] == 2){
                            grid[y][x] = 3; haveRotten = true; continue;
                        }
                    }
                    if(x < n-1){
                        if(grid[y][x+1] == 2){
                            grid[y][x] = 3; haveRotten = true; continue;
                        }
                    }
                    if(y > 0){
                        if(grid[y-1][x] == 2){
                            grid[y][x] = 3; haveRotten = true; continue;
                        }
                    }
                    if(y < m-1){
                        if(grid[y+1][x] == 2){
                            grid[y][x] = 3; haveRotten = true; continue;
                        }
                    }
                }
            }
        }
        
        for(int y=0; y<m; y++){
            for(int x=0; x<n; x++){
                if(grid[y][x] == 3) grid[y][x] = 2;
                else if(grid[y][x] == 1) stillHaveFresh = true;
            }
        }
        
        if(!haveRotten) break;
        minutes += 1;        
    }
    
    if(stillHaveFresh) return -1;
    return minutes;
}


int main(){
    vector<vector<int>> grid = {{2,1,1}, {1,1,0}, {0,1,1}};
    cout << orangesRotting(grid) << endl;

    grid = {{2,1,1}, {0,1,1}, {1,0,1}};
    cout << orangesRotting(grid) << endl;

    grid = {{0, 2}};
    cout << orangesRotting(grid) << endl;
}