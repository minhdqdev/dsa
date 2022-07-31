#include <vector>
#include <set>
#include <iostream>

using namespace std;

class Solution {
public:
    void solveSudoku(vector<vector<char>>& board) {
        vector<vector<char>> result;
        for(int i=0; i<9; i++){
            for(int j=0; j<9; j++){
                result[i][j] = board[i][j];
            }
        }
        
        vector<vector<set<char>>> available;
        vector<set<char>> available_y;
        vector<set<char>> available_x;
        vector<set<char>> available_s;
        
        for(int i=0; i<9; i++){
            set<char> set_x = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
            set<char> set_y = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
            set<char> set_s = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
            
            for(int j=0; j<9; j++){
                set_x.erase(board[i][j]);
                set_y.erase(board[j][i]);
                
                // TODO: 
                a = i / 3 + j % 3;
                b = j % 3 + j % 3;
                set_s.erase(board[a][b]);
            }
            
            available_y.push_back(set_y);
            available_x.push_back(set_x);
            available_s.push_back(set_s);
        }
        
        for(int i=0; i<9; i++){
            for(int j=0; j<9; j++){
                if(result[i][j] != '.') continue;
                    
                available[i][j]
            }
        }
        
        
        return result;
    }
};

int main(){
    set<int> s = {1,2,3};

    set<int >::iterator it ;

    s.erase(5);

    for (it = s.begin() ; it != s.end() ; it++ ) {
        cout << *it<<" ";
    }
    cout << endl;
}