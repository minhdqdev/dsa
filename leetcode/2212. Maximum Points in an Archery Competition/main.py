from typing import List
from datetime import datetime

# DEFINE SOLUTION IN HERE

class Solution:
    res = []
    m = 0

    def build_backtrack(self, aliceArrows, avail, index, points, r):
        
        if not avail:
            if points > self.m:
                self.m = points
                self.res = r
            return

        if index == -1: # finish
            if avail:
                r[0] += avail
            
            if points > self.m:
                self.m = points
                self.res = r
            return 


        # 2 options: shot or not
        if avail > aliceArrows[index]:
            n = aliceArrows[index]+1
            
            rr = r[:]
            rr[index] = n

            self.build_backtrack(aliceArrows, avail-n, index-1, points+index, rr)

        # not shot
        rr = r[:]
        self.build_backtrack(aliceArrows, avail, index-1, points, rr)
    def maximumBobPoints(self, numArrows: int, aliceArrows: List[int]) -> List[int]:
        # backtracking
        

        self.build_backtrack(aliceArrows, numArrows, 11, 0, [0 for _ in range(12)])

        return self.res



if __name__ == '__main__':
    solution = Solution()

    # DEFINE PARAMETERS IN HERE

    start = datetime.now()
    # RUN MAIN FUNCTION IN HERE

    avail = 9
    nums = [1,1,0,1,0,0,2,1,0,1,2,0]

    print('nums:', nums)

    ans = solution.maximumBobPoints(avail, nums)

    end = datetime.now()

    print(ans)
    print('\nRuntime:', (end-start))