class Solution {
public:
    ListNode* mergeList(ListNode* root, ListNode* l1, ListNode* l2){
        ListNode* curNode;
        if(l1 == NULL && l2 == NULL) root->next = NULL;
        else if(l1 == NULL){
            root->next = new ListNode(l2->val);
            mergeList(root->next, NULL, l2->next);
        }
        else if(l2 == NULL){
            root->next = new ListNode(l1->val);
            mergeList(root->next, l1->next, NULL);
        }
        else if(l1->val <= l2->val){
            root->next = new ListNode(l1->val);
            mergeList(root->next, l1->next, l2);
        }
        else{
            root->next = new ListNode(l2->val);
            mergeList(root->next, l1, l2->next);
        }
        return root;
    }
    
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        if(l1 == NULL && l2 == NULL) return NULL;
        else if(l1 == NULL) return mergeList(new ListNode(l2->val), NULL, l2->next);
        else if(l2 == NULL) return mergeList(new ListNode(l1->val), l1->next, NULL);
        else if(l1->val <= l2->val) return mergeList(new ListNode(l1->val), l1->next, l2);
        else return mergeList(new ListNode(l2->val), l1, l2->next);
    }
};