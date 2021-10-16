#include <vector>
using namespace std;

class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {
        vector<int> indices;
        indices.push_back(0);
        indices.push_back(numbers.size()-1);
        
        int s = numbers[indices[0]] + numbers[indices[1]];
        
        while(s != target){
            if(s < target){
                indices[0] += 1;
            }
            else if(s > target){
                indices[1] -= 1;
            }
            
            s = numbers[indices[0]] + numbers[indices[1]];
        }
        
        indices[0] += 1;
        indices[1] += 1;
        
        return indices;
    }
};