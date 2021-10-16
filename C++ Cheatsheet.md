### Header
```c++
#include <bits/stdc++.h>
#include <vector>
#include <math.h> /* pow */

using namespace std;
```

### Vector
```c++
vector<int> nums;

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
