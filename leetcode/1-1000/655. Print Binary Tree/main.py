# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def printTree(self, root: Optional[TreeNode]) -> List[List[str]]:
        # find the height of the tree
        
        def find_height(root, h):
            if not root or not root.left and not root.right:
                return h
            
            a = h
            if root.left:
                a = max(a, find_height(root.left, h+1))
            if root.right:
                a = max(a, find_height(root.right, h+1))
            return a
        
        height = find_height(root, 0)
        
        m, n = height + 1, 2 ** (height+1) - 1
        matrix = [['' for j in range(n)] for i in range(m)]
        
        
        def build_matrix(root, matrix, row, col, height):
            matrix[row][col] = str(root.val)
            
            if root.left:
                build_matrix(root.left, matrix, row+1, col - 2 ** (height - row - 1), height)
            if root.right:
                build_matrix(root.right, matrix, row+1, col + 2 ** (height- row - 1), height)
        
        build_matrix(root, matrix, 0, (n-1) // 2, height)
        
        return matrix