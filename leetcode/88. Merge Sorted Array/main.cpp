class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        int j = 0;
        queue<int> hold;
        
        if(n == 0) return;
        
        for(int i=0; i<m+n; i++){
            if(i < m){
                if(hold.empty()){
                    if(nums2[j] < nums1[i]){
                        hold.push(nums1[i]);
                        nums1[i] = nums2[j];
                        j += 1;
                    }
                }
                else{
                    if(j >= n){ // nums2 is empty -> take from queue
                        hold.push(nums1[i]);
                        nums1[i] = hold.front();
                        hold.pop();
                    }
                    else if(hold.front() < nums1[i] && nums2[j] < nums1[i]){
                        if(hold.front() <= nums2[j]){ // take from queue
                            hold.push(nums1[i]);
                            nums1[i] = hold.front();
                            hold.pop();
                        }
                        else{ // take from nums2
                            hold.push(nums1[i]);
                            nums1[i] = nums2[j];
                            j += 1;
                        }
                    }
                    else if(hold.front() < nums1[i]){ // take from queue
                        hold.push(nums1[i]);
                        nums1[i] = hold.front();
                        hold.pop();
                    }
                    else if(nums2[j] < nums1[i]){ // take from nums2
                        hold.push(nums1[i]);
                        nums1[i] = nums2[j];
                        j += 1;
                    }
                }
            }
            else{ // check only queue and nums2
                if(hold.empty()){ // take from nums2
                    nums1[i] = nums2[j];
                    j += 1;
                }
                else{
                    if(j >= n || hold.front() <= nums2[j]){ // take from queue
                        nums1[i] = hold.front();
                        hold.pop();
                    }
                    else{ // take from nums2
                        nums1[i] = nums2[j];
                        j += 1;
                    }
                }
            }
        }
    }
};