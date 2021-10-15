#include <iostream>
using namespace std;

int main(){
    int n;
    int count;
    int k;
    int res = 0;

    cin >> n;
    for(int i=0; i<n; i++){
        count = 0;
        for(int j=0; j<3; j++){
            cin >> k;
            if(k == 1) count += 1;
        }

        if(count > 1) res += 1;
    }

    cout << res << endl;
}