/*
Recursive approach
*/

#include <vector>
#include <queue>
#include <iostream>

using namespace std;

int calculateMinDistance(vector<vector<int>> & mat, int x, int y, vector<vector<int>>& minDistances, vector<vector<bool>>& visited, int MAX){
    if(minDistances[y][x] < MAX) return minDistances[y][x]; // reuse calculated value
    
    int res = MAX;
    int numCalculated = 0;
    int totalDirection = 0;
    int direction = -1;

    visited[y][x] = true;

    if(y > 0){
        totalDirection += 1;
        if(minDistances[y-1][x] < MAX){
            res = min(res, 1+minDistances[y-1][x]);
            numCalculated += 1;
        }
        else if(!visited[y-1][x]) direction = 0;
    }

    if(x < mat[0].size() - 1){
        totalDirection += 1;
        if(minDistances[y][x+1] < MAX){
            res = min(res, 1+minDistances[y][x+1]);
            numCalculated += 1;
        }
        else if(!visited[y][x+1]) direction = 1;
    }

    if(y < mat.size() - 1){
        totalDirection += 1;
        if(minDistances[y+1][x] < MAX){
            res = min(res, 1+minDistances[y+1][x]);
            numCalculated += 1;
        }
        else if(!visited[x][y+1]) direction = 2;
    }

    if(x > 0){
        totalDirection += 1;
        if(minDistances[y][x-1] < MAX){
            res = min(res, 1+minDistances[y][x-1]);
            numCalculated += 1;
        }
        else if(!visited[y][x-1]) direction = 3;
    }

    if(totalDirection - numCalculated <= 1){ // has enough calculated neighbors for conclusion
        minDistances[y][x] = res;
    }
    else{
        // go in the chosen direction
        if(direction == 0) // go up
            minDistances[y][x] = min(res, calculateMinDistance(mat, x, y-1, minDistances, visited, MAX));
        else if(direction == 1) // go right
            minDistances[y][x] = min(res, calculateMinDistance(mat, x+1, y, minDistances, visited, MAX));
        else if(direction == 2) // go down
            minDistances[y][x] = min(res, calculateMinDistance(mat, x, y+1, minDistances, visited, MAX));
        else if(direction == 3) // go left
            minDistances[y][x] = min(res, calculateMinDistance(mat, x-1, y, minDistances, visited, MAX));
    }
    return minDistances[y][x];
}

vector<vector<int>> updateMatrix(vector<vector<int>>& mat) {
    int m = mat.size();
    int n = mat[0].size();
    const int MAX_DIST = m + n - 2;
    const int MAX = MAX_DIST + 1;
    vector<vector<int>> updatedMatrix(m, vector<int>(n, 0));
    queue<pair<int, int>> q;
    int minDist = MAX_DIST;
    int a, b;
    vector<vector<int>> minDistances(m, vector<int>(n, MAX)); // MAX means uncalculated
    vector<vector<bool>> visited(m, vector<bool>(n, false));

    for(int y=0; y<m; y++){
        for(int x=0; x<n; x++){
            if(mat[y][x] == 0) minDistances[y][x] = 0;
        }
    }

    for(int y=0; y<m; y++){
        for(int x=0; x<n; x++){
            if(minDistances[y][x] == MAX){ // need calculate
                // visited[y][x] = true;
                calculateMinDistance(mat, x, y, minDistances, visited, MAX);

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
