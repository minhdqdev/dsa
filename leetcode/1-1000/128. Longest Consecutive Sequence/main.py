from typing import List
from datetime import datetime

# DEFINE SOLUTION IN HERE

class Solution:
    def longestConsecutive(self, nums: List[int]) -> int:
        # O(n) -> can not sort
        # -> optimal solution: use hashmap
        
        s = set()
        
        for _ in nums:
            s.add(_)
        
        max_count = 0
        count = 0
        for i in s:
            if i-1 not in s: # then i is the first elem of the sequence
                count = 1
                j = i + 1
                while j in s:
                    count += 1
                    j += 1
                
                if count > max_count:
                    max_count = count
            else:
                continue
        return max_count


if __name__ == '__main__':
    solution = Solution()

    # DEFINE PARAMETERS IN HERE

    start = datetime.now()
    # RUN MAIN FUNCTION IN HERE

    ans = solution.main()

    end = datetime.now()

    print(ans)
    print('\nRuntime:', (end-start))