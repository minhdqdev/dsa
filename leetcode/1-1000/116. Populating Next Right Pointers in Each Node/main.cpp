#include <vector>
#include <queue>
#include <math.h>

using namespace std;

// Definition for a Node.
class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* next;

    Node() : val(0), left(NULL), right(NULL), next(NULL) {}

    Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}

    Node(int _val, Node* _left, Node* _right, Node* _next)
        : val(_val), left(_left), right(_right), next(_next) {}
};


class Solution {
public:
    Node* connect(Node* root) { // BFS problem
        if(root == NULL) return root;
        
        queue<Node*> q;
        
        root->next = NULL;
        
        if(root->left == NULL) return root;

        q.push(root->left);
        q.push(root->right);
        int layer = 1;
        int countdown = 2;
        Node *node = NULL;
        while(!q.empty()){
            node = q.front();
            q.pop();
            
            if(countdown == 1) node->next = NULL;
            else node->next = q.front();
            
            if(node->left != NULL){
                // order is important
                q.push(node->left);
                q.push(node->right);
            }
            
            countdown -= 1;
            if(countdown == 0){
                layer += 1;
                countdown = pow(2, layer);
            }
        }
        
        return root;
    }
};