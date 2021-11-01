/*
Recursive approach
*/

#include <vector>
#include <queue>
#include <iostream>

using namespace std;

int minDistance(vector<vector<int>> & mat, int x, int y, vector<vector<int>>& minDistances, vector<vector<bool>>& visited, int MAX_DIST, int MAX){
    if(mat[y][x] == 0){
        minDistances[y][x] = 0;
        return 0;
    }
    if(minDistances[y][x] < MAX) return minDistances[y][x]; // reuse calculated value
    else{
        int res = MAX_DIST;

        if(y > 0){
            if(minDistances[y-1][x] != MAX)
                res = min(res, 1+minDistances[y-1][x]);
            else if(!visited[y-1][x]){
                visited[y-1][x] = true;
                res = min(res, 1+minDistance(mat, x, y-1, minDistances, visited, MAX_DIST, MAX));
            }
        }

        if(x > 0){
            if(minDistances[y][x-1] != MAX) // already calculated
                res = min(res, 1+minDistances[y][x-1]);
            else if(!visited[y][x-1]){
                visited[y][x-1] = true;
                res = min(res, 1+minDistance(mat, x-1, y, minDistances, visited, MAX_DIST, MAX));
            }   
        }

        if(x < mat[0].size() - 1){
            if(minDistances[y][x+1] != MAX)
                res = min(res, 1+minDistances[y][x+1]);
            else if(!visited[y][x+1]){
                visited[y][x+1] = true;
                res = min(res, 1+minDistance(mat, x+1, y, minDistances, visited, MAX_DIST, MAX));
            }
        }

        if(y < mat.size() - 1){
            if(minDistances[y+1][x] != MAX)
                res = min(res, 1+minDistances[y+1][x]);
            else if(!visited[y+1][x]){
                visited[y+1][x] = true;
                res = min(res, 1+minDistance(mat, x, y+1, minDistances, visited, MAX_DIST, MAX));
            }
        }

        minDistances[y][x] = res;
        return res;
    }
}

vector<vector<int>> updateMatrix(vector<vector<int>>& mat) {
    int m = mat.size();
    int n = mat[0].size();
    const int MAX_DIST = m + n - 2;
    const int MAX = MAX_DIST + 12;
    vector<vector<int>> updatedMatrix(m, vector<int>(n, 0));
    queue<pair<int, int>> q;
    int minDist = MAX_DIST;
    int a, b;
    vector<vector<int>> minDistances(m, vector<int>(n, MAX)); // MAX means uncalculated
    vector<vector<bool>> visited(m, vector<bool>(n, false));

    for(int y=0; y<m; y++){
        for(int x=0; x<n; x++){
            if(mat[y][x] == 0){
                if(minDistances[y][x] == MAX) minDistances[y][x] = 0;
                continue;
            }
            
            if(minDistances[y][x] == MAX){
                visited[y][x] = true;
                updatedMatrix[y][x] = minDistance(mat, x, y, minDistances, visited, MAX_DIST, MAX);

                for(int b=0; b<minDistances.size(); b++){
                    for(int a=0; a<minDistances[0].size(); a++){
                        if(minDistances[b][a] < MAX) cout << ' ' << minDistances[b][a] << ' ';
                        else cout << "XX" << ' ';
                    }
                    cout << endl;
                }
                cout << endl;
            }
        }
    }

    return minDistances;
}

int main(){
    // vector<vector<int>> inputMat {{0, 0, 0}, {0, 1, 0}, {0, 0, 0}};
    // vector<vector<int>> inputMat {{1, 1, 1}, {1, 1, 1}, {1, 1, 0}};
    // vector<vector<int>> inputMat {{0, 0, 0}, {0, 1, 0}, {1, 1, 1}};

    vector<vector<int>> inputMat = {{1,0,1,1,0,0,1,0,0,1}, {0,1,1,0,1,0,1,0,1,1}, {0,0,1,0,1,0,0,1,0,0}, {1,0,1,0,1,1,1,1,1,1}, {0,1,0,1,1,0,0,0,0,1}, {0,0,1,0,1,1,1,0,1,0}, {0,1,0,1,0,1,0,0,1,1}, {1,0,0,0,1,1,1,1,0,1}, {1,1,1,1,1,1,1,0,1,0}, {1,1,1,1,0,1,0,0,1,1}};
    vector<vector<int>> correct = {{1,0,1,1,0,0,1,0,0,1}, {0,1,1,0,1,0,1,0,1,1}, {0,0,1,0,1,0,0,1,0,0}, {1,0,1,0,1,1,1,1,1,1}, {0,1,0,1,1,0,0,0,0,1}, {0,0,1,0,1,1,1,0,1,0}, {0,1,0,1,0,1,0,0,1,1}, {1,0,0,0,1,2,1,1,0,1}, {2,1,1,1,1,2,1,0,1,0}, {3,2,2,1,0,1,0,0,1,1}};

    // for(int x=0; x<inputMat.size(); x++){
    //     for(int y=0; y<inputMat[0].size(); y++){
    //         cout << inputMat[x][y] << ' ';
    //     }
    //     cout << endl;
    // }
    // cout << endl;

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
