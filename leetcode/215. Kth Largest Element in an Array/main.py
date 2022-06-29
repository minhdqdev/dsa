from typing import List
from datetime import datetime
import heapq

# DEFINE SOLUTION IN HERE

class Solution:
    def findKthLargest(self, nums: List[int], k: int) -> int:
        a = [_ * -1 for _ in nums]
        
        heapq.heapify(a)
        
        b = None
        for i in range(k):
            b = heapq.heappop(a)
        
        return b * -1


if __name__ == '__main__':
    solution = Solution()

    # DEFINE PARAMETERS IN HERE

    start = datetime.now()
    # RUN MAIN FUNCTION IN HERE

    ans = solution.main()

    end = datetime.now()

    print(ans)
    print('\nRuntime:', (end-start))