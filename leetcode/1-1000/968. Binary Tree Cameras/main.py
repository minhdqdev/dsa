from collections import deque
from typing import List, Optional
from datetime import datetime

# DEFINE SOLUTION IN HERE

class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

class Solution:
    def is_covered_by_children(self, node: TreeNode, put_camera: dict) -> bool:
        if node.left and put_camera[node.left]:
            return True
        if node.right and put_camera[node.right]:
            return True
        return False

    def minCameraCover(self, root: Optional[TreeNode]) -> int:
        q = deque()
        
        q.append(root)
        
        layers = [[root]]
        parents = {root: None}

        layer = []
        
        while q:
            node = q.popleft()
            
            if node.left:
                parents[node.left] = node
                layer.append(node.left)
            if node.right:
                parents[node.right] = node
                layer.append(node.right)
            
            if not q and layer:
                layers.append(layer[:])
                for _ in layer:
                    q.append(_)
                layer = []
        
        if len(layers) <= 2:
            return 1
        
        count = 0
        put_camera = {}
        for i in range(len(layers)-1, -1, -1):
            # print('layer', [_.val for _ in layers[i]])
            for j in range(len(layers[i])):
                item = layers[i][j]
                put_camera[item] = False

                if item.left and item.right:
                    need_put = False
                    if put_camera[item.left] and put_camera[item.right]:
                        # don't need to put camera
                        pass
                    elif put_camera[item.left]:
                        if not self.is_covered_by_children(item.right, put_camera):
                            need_put = True
                    elif put_camera[item.right]:
                        if not self.is_covered_by_children(item.left, put_camera):
                            need_put = True
                    else:
                        a = self.is_covered_by_children(item.left, put_camera)
                        b = self.is_covered_by_children(item.right, put_camera)
                        
                        if a and b:
                            if not parents[item]:
                                need_put = True                  
                        else:
                            need_put = True
                    
                    if need_put:
                        count += 1
                        put_camera[item] = True

                elif item.left:
                    need_put = False
                    if not put_camera[item.left]:
                        if not self.is_covered_by_children(item.left, put_camera):
                            need_put = True
                        elif not parents[item]:
                            need_put = True
                    
                    if need_put:
                        count += 1
                        put_camera[item] = True
                elif item.right:
                    need_put = False
                    if not put_camera[item.right]:
                        if not self.is_covered_by_children(item.right, put_camera):
                            need_put = True
                        elif not parents[item]:
                            need_put = True
                        
                    if need_put:
                        put_camera[item] = True
                        count += 1
        
        return count


"""
[0,0,null,0,0]
[0,0,null,0,null,0,null,null,0]
[0,0,0,null,null,null,0]
[0,0,null,null,0,0,null,null,0,0]
"""


if __name__ == '__main__':
    solution = Solution()

    # DEFINE PARAMETERS IN HERE

    start = datetime.now()
    # RUN MAIN FUNCTION IN HERE

    n10 = TreeNode(10)
    n8 = TreeNode(8)
    n9 = TreeNode(9)
    n6 = TreeNode(6)
    n7 = TreeNode(7, right=n10)
    n5 = TreeNode(5, left=n8, right=n9)
    n4 = TreeNode(4, left=n7)
    n2 = TreeNode(2, left=n4, right=n5)
    n3 = TreeNode(3, right=n6)
    n1 = TreeNode(1, left=n2, right=n3)
    root = n1

    # n4 = TreeNode(4)
    # n2 = TreeNode(2)
    # n3 = TreeNode(3, right=n4)
    # n1 = TreeNode(1, left=n2, right=n3)
    # root = n1

    ans = solution.minCameraCover(root)

    end = datetime.now()

    print(ans)
    print('\nRuntime:', (end-start))