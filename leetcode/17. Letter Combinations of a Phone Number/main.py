from typing import List
from datetime import datetime

# DEFINE SOLUTION IN HERE

class Solution:
    def letterCombinations(self, digits: str) -> List[str]:
        res = []
        if len(digits) == 0:
            return res
        
        d = {
            '2': ('a','b','c'),
            '3': ('d','e','f'),
            '4': ('g','h','i'),
            '5': ('j','k','l'),
            '6': ('m','n','o'),
            '7': ('p','q','r','s'),
            '8': ('t','u','v'),
            '9': ('w','x','y','z'),
        }
    
        def build_backtrack(digits, a, res):
            if len(a) < len(digits):
                
                for c in d[digits[len(a)]]:
                    build_backtrack(digits, a+c, res)
            else:
                res.append(a)
        
        build_backtrack(digits, "", res)
    
        return res
        


if __name__ == '__main__':
    solution = Solution()

    # DEFINE PARAMETERS IN HERE

    start = datetime.now()
    # RUN MAIN FUNCTION IN HERE

    ans = solution.main()

    end = datetime.now()

    print(ans)
    print('\nRuntime:', (end-start))