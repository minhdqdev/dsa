#include <string>
#include <iostream>
using namespace std;

// ham nay se chay rat cham -> su dung phuong an dung hashmap de check permutation se hieu qua hon
bool arePermutations(string& s1, string& s2, int start){
    string s3 = s2.substr(start, s1.size());
    sort(s3.begin(), s3.end());
    
    for(int i=0; i<s1.size(); i++){
        if(s3[i] != s1[i]) return false;
    }
    return true;
}

bool checkInclusion(string s1, string s2) {
    sort(s1.begin(), s1.end());
    
    int left = -1;
    int right = -1;
    
    int m = s1.size();
    int n = s2.size();
    
    bool c = false;
    bool res = false;
    for(int i=0; i<n; i++){
        c = false;
        for(int j=0; j<s1.size(); j++){
            if(s2[i] == s1[j]){
                c = true; break;
            }
        }
        
        if(c){ // char is in s1
            if(right == -1) left = i;
            right = i;
        }
        else{
            if(right - left + 1 >= m && right != -1){
                // slide window
                for(int k=0; k<right-left-m+2; k++){
                    if(arePermutations(s1, s2, left+k)) return true;
                }
            }
            
            left = -1; right = -1;
        }
    }
    
    if(right != -1){
        if(right - left + 1 >= m){
            // slide window
            for(int k=0; k<right-left-m+2; k++){
                if(arePermutations(s1, s2, left+k)) return true;
            }
        }
    }
    
    return res;
}

int main(){
    string s1 = "hello";
    string s2 = "ooolleoooleh";

    cout << checkInclusion(s1, s2) << endl;

    s1 = "ab";
    s2 = "eidbaooo";

    cout << checkInclusion(s1, s2) << endl;

    s1 = "a";
    s2 = "b";

    cout << checkInclusion(s1, s2) << endl;
}