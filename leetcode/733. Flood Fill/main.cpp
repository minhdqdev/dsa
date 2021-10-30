#include <vector>

using namespace std;

int main(){
    queue<int[2]> q;

    while(!q.empty()){
        // pop
        p = q.pop();
        
        if(!visited[p.first][p.second){
            visited[p.first[p.second] = true;
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
}