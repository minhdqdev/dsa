#include <vector>
#include <string>
using namespace std;

class Solution {
public:
    void reverseString(string& s, int start, int end){
        int temp, n = end - start + 1;
        for(int i=0; i<n / 2; i++){
            temp = s[start + i];
            s[start + i] = s[end-i];
            s[end-i] = temp;
        }
    }
    
    string reverseWords(string s) {
        int left = -1;
        
        for(int i=0; i<s.size(); i++){
            if(s[i] != ' '){
                if(left == -1){ // start of word
                    left = i;
                }
            }
            else{
                if(left != -1){ // end of word
                    reverseString(s, left, i - 1);
                    left = -1;
                }
            }
        }
        
        if(left != -1){ // string ends with word not space
            reverseString(s, left, s.size()-1);
        }
        
        return s;
    }
};