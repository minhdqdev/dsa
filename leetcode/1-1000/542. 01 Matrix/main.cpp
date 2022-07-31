#include <vector>
#include <queue>
#include <iostream>

using namespace std;

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
    for(int y=0; y<m; y++){
        for(int x=0; x<n; x++){
            if(!mat[y][x]) minDistances[y][x] = 0;
        }
    }

    bool allCalculated = false;

    for(int y=0; y<m; y++){
        for(int x=0; x<n; x++){
            if(mat[y][x] == 0) continue;
            minDist = MAX_DIST;
            vector<vector<bool>> visited(m, vector<bool>(n, false));
            vector<vector<int>> dist(m, vector<int>(n, MAX_DIST));

            while(!q.empty()) q.pop();
            q.push({x, y});
            visited[y][x] = true;
            dist[y][x] = 0;

            while(!q.empty()){
                a = q.front().first;
                b = q.front().second;
                q.pop();
                
                minDist = MAX;
                allCalculated = true;
                if(a > 0){
                    if(minDistance[b][a-1] == MAX) allCalculated = false;
                }
                minDist = min(min(minDistances[b-1][a], minDistances[b+1][a]), min(minDistances[b][a-1], minDistances[b][a+1]));

                if(a > 0 && !visited[b][a-1] && minDistances[b][a-1] < MAX){
                    visited[b][a-1] = true;
                    dist[b][a-1] = dist[b][a] + 1;
                    if(mat[b][a-1] == 0){
                        minDist = dist[b][a-1];
                        break;
                    }
                    else if(minDist > dist[b][a-1])
                        q.push({a-1, b});
                }
                if(a < n-1 && !visited[b][a+1] && minDistances[b][a+1] < MAX){
                    visited[b][a+1] = true;
                    dist[b][a+1] = dist[b][a] + 1;
                    if(mat[b][a+1] == 0){
                        minDist = dist[b][a+1];
                        break;
                    }
                    else if(minDist > dist[b][a+1])
                        q.push({a+1, b});
                }
                if(b > 0 && !visited[b-1][a]  && minDistances[b-1][a] < MAX){
                    visited[b-1][a] = true;
                    dist[b-1][a] = dist[b][a] + 1;
                    if(mat[b-1][a] == 0){
                        minDist = dist[b-1][a];
                        break;
                    }
                    else if(minDist > dist[b-1][a])
                        q.push({a, b-1});
                }
                if(b < m-1 && !visited[b+1][a]  && minDistances[b+1][a] < MAX){
                    visited[b+1][a] = true;
                    dist[b+1][a] = dist[b][a] + 1;
                    if(mat[b+1][a] == 0){
                        minDist = dist[b+1][a];
                        break;
                    }
                    else if(minDist > dist[b+1][a])
                        q.push({a, b+1});
                }
            }       
            updatedMatrix[y][x] = minDist;
        }
    }

    return updatedMatrix;
}

int main(){
    // vector<vector<int>> inputMat {{0, 0, 0}, {0, 1, 0}, {0, 0, 0}};
    // vector<vector<int>> inputMat {{1, 1, 1}, {1, 1, 1}, {1, 1, 0}};
    vector<vector<int>> inputMat {{0, 0, 0}, {0, 1, 0}, {1, 1, 1}};
    

    for(int x=0; x<inputMat.size(); x++){
        for(int y=0; y<inputMat[0].size(); y++){
            cout << inputMat[x][y] << ' ';
        }
        cout << endl;
    }

    vector<vector<int>> outputMat = updateMatrix(inputMat);

    for(int x=0; x<outputMat.size(); x++){
        for(int y=0; y<outputMat[0].size(); y++){
            cout << outputMat[x][y] << ' ';
        }
        cout << endl;
    }


}
