# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def sumOfLeftLeaves(self, root: Optional[TreeNode]) -> int:
        if not root:
            return 0
        
        def find_sum(root, direction):
            if not root.left and not root.right:
                if direction == 0:
                    return root.val
                return 0
            elif root.left and root.right:
                return find_sum(root.left, 0) + find_sum(root.right, 1)
            elif root.left:
                return find_sum(root.left, 0)
            else:
                return find_sum(root.right, 1)
        
        return find_sum(root, 1)