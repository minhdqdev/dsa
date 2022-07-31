from typing import List
from datetime import datetime

# DEFINE SOLUTION IN HERE

class Solution:
    def is_palindrome(self, s, i, length, d):
        if length % 2 == 0:
            for k in d:
                if d[k] % 2 != 0: # can not have odd char
                    return False
        elif length % 2 == 0:
            found_odd = False
            for k in d:
                if d[k] % 2 != 0:
                    found_odd = True
                    
                    if s[i+length // 2] != k: # the center char is not this one
                        return False

            if not found_odd:
                return False
        
        # search in the old way
        for j in range(length // 2):
            if s[i+j] != s[i+length-1-j]:
                return False
        
        return True
        
    def longestPalindrome(self, s: str) -> str:
        
        d = {}
        for w in s:
            d[w] = 1 if w not in d else (d[w] + 1)
        
        for length in range(len(s), 1, -1):
            dd = d.copy()
            
            for i in range(length, len(s)):
                w = s[i]
                if dd[w] == 1:
                    del dd[w]
                else:
                    dd[w] -= 1
            
            # slide window
            if self.is_palindrome(s, 0, length, dd):
                return s[0:0+length]
                
            for i in range(1, len(s) - length + 1):
                w = s[i-1]
                if dd[w] == 1:
                    del dd[w]
                else:
                    dd[w] -= 1
                
                w = s[i-1+length]
                if w not in dd:
                    dd[w] = 1
                else:
                    dd[w] += 1
                
                if self.is_palindrome(s, i, length, dd):
                    return s[i:i+length]
        
        return s[0]


if __name__ == '__main__':
    solution = Solution()

    # DEFINE PARAMETERS IN HERE

    start = datetime.now()
    # RUN MAIN FUNCTION IN HERE
    
    s = "badad"
    ans = solution.longestPalindrome(s)

    # ans = solution.is_palindrome(s, 0, len(s), {'a': 2, 'b': 2, 'c': 1})

    end = datetime.now()

    print(ans)
    print('\nRuntime:', (end-start))