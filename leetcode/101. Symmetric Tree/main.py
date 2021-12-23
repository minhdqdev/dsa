from typing import Optional

class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

class Solution:
    def traversal_left(self, node, s):
        if node is None:
            s.append(None)
        else:
            self.traversal_left(node.left, s)
            self.traversal_left(node.right, s)
            s.append(node)
    
    def traversal_right(self, node, s):
        if node is None:
            s.append(None)
        else:
            self.traversal_right(node.right, s)
            self.traversal_right(node.left, s)
            s.append(node)
    
    def isSymmetric(self, root: Optional[TreeNode]) -> bool:
        s1 = []
        s2 = []
        
        if root.left is None and root.right is None:
            return True
    
        if root.left is None or root.right is None:
            return False
    
        self.traversal_left(root.left, s1)
        self.traversal_right(root.right, s2)

        print([s.val if s else None for s in s1])
        print([s.val if s else None for s in s2])
        
        if len(s1) != len(s2):
            return False
    
        for i in range(len(s1)):
            if s1[i] is None and s2[i] is None:
                continue
            elif s1[i] is not None and s2[i] is not None:
                if s1[i].val != s2[i].val:
                    return False
            else:
                return False
        
        return True

if __name__ == '__main__':

    node1 = TreeNode(4, None, None)
    node2 = TreeNode(5, TreeNode(8), TreeNode(9))
    node3 = TreeNode(3, node1, node2)
    node4 = TreeNode(5, TreeNode(9), TreeNode(8))
    node5 = TreeNode(4, None, None)
    node6 = TreeNode(3, node4, node5)
    root = TreeNode(2, node3, node6)

    res = Solution().isSymmetric(root)

    print(res)