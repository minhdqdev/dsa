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
    ListNode* reverseList(ListNode* head) {
        if(head == NULL) return NULL;
        
        ListNode* curNode = head;
        ListNode* node1 = NULL;
        ListNode* node2 = NULL;
        
        while(curNode != NULL){
            if(node1 == NULL) node1 = new ListNode(curNode->val);
            else{
                node2 = node1;
                node1 = new ListNode(curNode->val, node2);
            }
            curNode = curNode->next;
        }
        
        return node1;
    }
};