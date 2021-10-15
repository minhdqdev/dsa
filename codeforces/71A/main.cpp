#include <iostream>
#include <string>
#include <array>

using namespace std;

int main(){
    int n;

    cin >> n;

    string list[n];

    for(int i=0; i<n; i++){
        cin >> list[i];
        if(list[i].length() > 10) cout << list[i][0] << list[i].length() - 2 << list[i][list[i].length() - 1] << '\n';
        else cout << list[i] << '\n';
    }
}