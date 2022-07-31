#include <bits/stdc++.h>

class Solution {
public:
    vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int newColor) {
        int m = image.size();
        int n = image[0].size();
        int sourceColor = image[sr][sc];
        vector<vector<bool>> visited(m, vector<bool> (n, false));
        queue<pair<int, int>> q;
        q.push({sr, sc});
        pair<int, int> p;
        while(!q.empty()){
            // pop
            p.first = q.front().first;
            p.second = q.front().second;
            q.pop();

            if(!visited[p.first][p.second]){
                visited[p.first][p.second] = true;
                image[p.first][p.second] = newColor;

                // search adj
                if(p.second > 0 && image[p.first][p.second-1] == sourceColor)
                    q.push({p.first, p.second-1});
                if(p.second < n-1 && image[p.first][p.second+1] == sourceColor)
                    q.push({p.first, p.second+1});
                if(p.first > 0 && image[p.first-1][p.second] == sourceColor) 
                    q.push({p.first-1, p.second});
                if(p.first < m-1 && image[p.first+1][p.second] == sourceColor) 
                    q.push({p.first+1, p.second});
            }
        }
        return image;
    }
};

int main(){

}