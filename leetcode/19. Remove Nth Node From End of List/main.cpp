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
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode* node1 = NULL;
        ListNode* node2 = NULL;
        ListNode* curNode = head;
        
        int c = 0;
        while(curNode != NULL){
            c += 1;
            
            if(c == n){
                node2 = head;
            }
            else if(c == n+1){
                node1 = head;
                node2 = head->next;
            }
            else if(c > n+1){
                node1 = node1->next;
                node2 = node2->next;
            }
            curNode = curNode->next;
        }
        
        if(node1 == NULL){ // which mean the head node is removed
            return head->next;
        }
        else{ // which mean an internal or the tail node is removed
            node1->next = node2->next;
            return head;
        }
    }
};