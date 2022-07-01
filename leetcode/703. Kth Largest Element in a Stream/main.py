from typing import List
from datetime import datetime
import heapq

# DEFINE SOLUTION IN HERE

class KthLargest:

    def __init__(self, k: int, nums: List[int]):
        self.m = []
        self.k = k
        
        for val in nums:
            self.add(val)

    def add(self, val: int) -> int:
        if len(self.m) >= self.k:
            heapq.heappushpop(self.m, val)
        else:
            heapq.heappush(self.m, val)
        return self.m[0]


# Your KthLargest object will be instantiated and called as such:
# obj = KthLargest(k, nums)
# param_1 = obj.add(val)


if __name__ == '__main__':
    # DEFINE PARAMETERS IN HERE

    start = datetime.now()
    # RUN MAIN FUNCTION IN HERE

    [[1,[]],[-3],[-2],[-4],[0],[4]]

    a = KthLargest(1, [])

    a.add(-3)
    a.add(-2)
    a.add(-4)
    a.add(0)
    a.add(4)

    end = datetime.now()

    # print(ans)
    print('\nRuntime:', (end-start))