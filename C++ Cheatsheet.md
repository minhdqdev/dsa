### Header
```c++
#include <bits/stdc++.h>
#include <vector>
#include <math.h> /* pow */

using namespace std;
```


## Array
Khi khởi tạo array với size thì bắt buộc size phải là const.
-> với dynamic-sized array thì tốt nhất là dùng vector 
```c++
// 2D dynamic-sized array
vector<vector<int>> array2D;
```

C++ không hỗ trợ assign array vào biến như Python
-> phải khởi tạo biến rồi add từng phần tử vào
```c++
queue<int[2]> q;

int[2] p = {1,2};

// wrong, you must create a new one
q.push(p);

// still wrong, runtime error, i don't know why
q.push({1,2});


int[2] = p2;

// wrong, you can't directly assign array to a variable
p2 = q.pop();

// correct
p2[0] = q.front()[0];
p2[1] = q.front()[1];
q.pop();




```
Mà tốt nhất là khi làm việc với queue of array thì tốt nhất là nên sử dụng object kiểu như là pair hay struct sẽ tốt hơn




### Vector
```c++
vector<int> nums;

// create 2D vector with size mxn and default value of 0.
vector<vector<int>> visited(m, vector<int> (n, 0));


// get size
nums.size();

// indexing
nums[index];

// pass by reference
int function_a(vector<int>& nums){...}

// sort (ascending)
sort(v.begin(), v.end());
sort(v.begin(), v.end(), greater<int>()); // more verbose

// custom lambda sort
bool compare(int a, int b){ return a > b; } // descending
sort(v.begin(), v.end(), compare);
```

### Math
```c++
pow(7.0, 3.0) // = 343.000000 (float)
```
