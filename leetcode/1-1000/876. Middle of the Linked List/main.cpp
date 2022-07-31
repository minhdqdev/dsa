/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* middleNode(ListNode* head) {
        int n = 0;
        int middleIndex = 0;
        ListNode* middle = head;
        ListNode* curNode = head;
        while(curNode != NULL){
            n += 1;
            curNode = curNode->next;
            
            if(n/2 > middleIndex){
                middleIndex = n/2;
                middle = middle->next;
            }
        }
        
        return middle;
    }
};