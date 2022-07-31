#include <vector>
using namespace std;

class Solution {
public:
    void reverseString(vector<char>& s) {
        int temp, n = s.size();
        for(int i=0; i< n / 2; i++){
            temp = s[i];
            s[i] = s[n-1-i];
            s[n-1-i] = temp;
        }
    }
};
