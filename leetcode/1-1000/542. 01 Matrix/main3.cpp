/*
Non DFS solution

Slow but still working
*/

#include <vector>
#include <queue>
#include <iostream>

using namespace std;

vector<vector<int>> updateMatrix(vector<vector<int>>& mat) {
    int m = mat.size();
    int n = mat[0].size();
    const int MAX = m + n;
    vector<vector<int>> updatedMatrix(m, vector<int>(n, 0));
    queue<pair<int, int>> q;
    
    vector<vector<int>> minDistances(m, vector<int>(n, MAX)); // MAX means uncalculated
    // vector<vector<bool>> visited(m, vector<bool>(n, false));

    int total = m * n; // total uncalculated
    int k = 0;

    for(int y=0; y<m; y++){
        for(int x=0; x<n; x++){
            if(mat[y][x] == 0){
                minDistances[y][x] = 0;
                total -= 1;
            }
        }
    }

    while(total != 0){
        for(int y=0; y<m; y++){
            for(int x=0; x<n; x++){
                if(minDistances[y][x] == MAX){ // uncalculated
                    if(y > 0){
                        if(minDistances[y-1][x] == k){
                            total -= 1;
                            minDistances[y][x] = k + 1; continue;
                        }
                    }
                    if(y < m - 1){
                        if(minDistances[y+1][x] == k){
                            total -= 1;
                            minDistances[y][x] = k + 1; continue;
                        }
                    }
                    if(x > 0){
                        if(minDistances[y][x-1] == k){
                            total -= 1;
                            minDistances[y][x] = k + 1; continue;
                        }
                    }
                    if(x < n - 1){
                        if(minDistances[y][x+1] == k){
                            total -= 1;
                            minDistances[y][x] = k + 1; continue;
                        }
                    }
                    
                }
            }
        }
        k += 1;
    }

    return minDistances;
}

int main(){
    // vector<vector<int>> inputMat {{0, 0, 0}, {0, 1, 0}, {0, 0, 0}};
    // vector<vector<int>> inputMat {{1, 1, 1}, {1, 1, 1}, {1, 1, 0}};
    // vector<vector<int>> inputMat {{0, 0, 0}, {0, 1, 0}, {1, 1, 1}};

    vector<vector<int>> inputMat = {{1,0,1,1,0,0,1,0,0,1}, {0,1,1,0,1,0,1,0,1,1}, {0,0,1,0,1,0,0,1,0,0}, {1,0,1,0,1,1,1,1,1,1}, {0,1,0,1,1,0,0,0,0,1}, {0,0,1,0,1,1,1,0,1,0}, {0,1,0,1,0,1,0,0,1,1}, {1,0,0,0,1,1,1,1,0,1}, {1,1,1,1,1,1,1,0,1,0}, {1,1,1,1,0,1,0,0,1,1}};
    vector<vector<int>> correct = {{1,0,1,1,0,0,1,0,0,1}, {0,1,1,0,1,0,1,0,1,1}, {0,0,1,0,1,0,0,1,0,0}, {1,0,1,0,1,1,1,1,1,1}, {0,1,0,1,1,0,0,0,0,1}, {0,0,1,0,1,1,1,0,1,0}, {0,1,0,1,0,1,0,0,1,1}, {1,0,0,0,1,2,1,1,0,1}, {2,1,1,1,1,2,1,0,1,0}, {3,2,2,1,0,1,0,0,1,1}};

    vector<vector<int>> outputMat = updateMatrix(inputMat);

    for(int x=0; x<outputMat.size(); x++){
        for(int y=0; y<outputMat[0].size(); y++){
            cout << outputMat[x][y] << ' ';
        }
        cout << "  "; 
        for(int y=0; y<outputMat[0].size(); y++){
            cout << correct[x][y] << ' ';
        }
        cout << endl;
    }


}
