"""
# Definition for a Node.
class Node:
    def __init__(self, val=None, children=None):
        self.val = val
        self.children = children
"""

class Solution:
    def levelOrder(self, root: 'Node') -> List[List[int]]:
        res = []
        
        if not root:
            return res
        
        q = deque()
        q.append(root)
        level_size = 1
        
        while q:
            level = []
            
            for _ in range(level_size):
                a = q.popleft()
                
                level.append(a.val)
                
                for child in a.children:
                    q.append(child)
            
            res.append(level)
            level = []
            level_size = len(q)
        
        return res