# Definition for a binary tree node.
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right
class Solution:
    def findTarget(self, root: TreeNode, k: int) -> bool:
        s = set()
        
        def bfs(node, s):
            s.add(node.val)
            
            if node.left:
                bfs(node.left, s)
            if node.right:
                bfs(node.right, s)
        
        bfs(root, s)
        
        def bfs_search(node, s, k):
            if not node:
                return False
            if k - node.val in s and k-node.val != node.val:
                return True
            else:
                return bfs_search(node.left, s, k) or bfs_search(node.right, s, k)
        
        return bfs_search(root, s, k)
    
    
            