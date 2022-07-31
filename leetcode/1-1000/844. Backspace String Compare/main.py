import heapq
from collections import deque
from datetime import datetime
from typing import List

# DEFINE SOLUTION IN HERE

class Solution:
    def backspaceCompare(self, s: str, t: str) -> bool:
        # Time complexity: O(n)
        # Space complexity: O(1)
        
        a, b = "", ""
        c1, c2 = 0, 0
        i, j = len(s) - 1, len(t) - 1
        
        while True:
            # get a
            a = ""
            while i >= 0:
                if s[i] == '#':
                    c1 += 1
                else:
                    if c1 > 0:
                        c1 -= 1
                    else:
                        a = s[i]
                        i -= 1
                        break
                i -= 1
        
            # get b
            b = ""
            while j >= 0:
                if t[j] == '#':
                    c2 += 1
                else:
                    if c2 > 0:
                        c2 -= 1
                    else:
                        b = t[j]
                        j -= 1
                        break
                j -= 1
            
            if a != b:
                return False
            
            if i == j and i == -1:
                break
        
        return True


if __name__ == '__main__':
    solution = Solution()

    # DEFINE PARAMETERS IN HERE

    start = datetime.now()
    # RUN MAIN FUNCTION IN HERE

    ans = solution.backspaceCompare()

    end = datetime.now()

    print(ans)
    print('\nRuntime:', (end-start))
