from typing import List
from datetime import datetime

# DEFINE SOLUTION IN HERE

class Solution:
    def combinationSum(self, candidates: List[int], target: int) -> List[List[int]]:
        
        def build_backtrack(candidates, target, a, result):
            if target == 0:
                result.append(a)
                return
            elif target < 0:
                return
            
            for c in candidates:
                if a and c < a[-1]:
                    continue
                if c > target:
                    break
                t = a[:]
                t.append(c)
                build_backtrack(candidates, target-c, t, result)
        
        candidates.sort()
        result = []
        build_backtrack(candidates, target, [], result)
        
        return result


if __name__ == '__main__':
    solution = Solution()

    # DEFINE PARAMETERS IN HERE

    start = datetime.now()
    # RUN MAIN FUNCTION IN HERE

    ans = solution.main()

    end = datetime.now()

    print(ans)
    print('\nRuntime:', (end-start))