from typing import List
from datetime import datetime

# DEFINE SOLUTION IN HERE

class Solution:
    def isPalindrome(self, s: str) -> bool:
        s = "".join([_ for _ in s.lower() if _.isalpha() or _.isnumeric()])
        
        left, right = 0, len(s) - 1
        
        while left < right:
            c1 = s[left].lower()
            if not c1.isalpha() and not c1.isnumeric():
                left += 1
                continue
            
            c2 = s[right].lower()
            if not c2.isalpha() and not c2.isnumeric():
                right -= 1
                continue
            
            if c1 != c2:
                return False
            
            left += 1
            right -= 1
        
        return True


if __name__ == '__main__':
    solution = Solution()

    # DEFINE PARAMETERS IN HERE

    start = datetime.now()
    # RUN MAIN FUNCTION IN HERE

    ans = solution.main()

    end = datetime.now()

    print(ans)
    print('\nRuntime:', (end-start))