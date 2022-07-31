import heapq
from collections import deque
from datetime import datetime
from typing import List

# DEFINE SOLUTION IN HERE
class Solution:
    def longestValidParentheses(self, s: str) -> int:
        # dynamic programming
        # valid: valid + valid. E.g: ()()
        #        (valid). E.g: (())
        
        # stack dung de check nhanh
        # valid substring start at index i
        # neu substring start with ) -> never valid
        # length of valid substring always is even
        
        # dp[i] = length of the longest valid substring start at index i
        
        # edge cases
        if len(s) < 2:
            return 0
        
        def find_dp(i, dp):
            if i not in dp:
                if s[i] == ')':
                    dp[i] = 0
                    return dp[i]
                
                ss = ['('] # stack
                max_length = 0
                
                j = i+1
                while j < len(s):
                    t = find_dp(j, dp)
                    
                    if t == 0: # not valid
                        # push stack
                        if s[j] == ')' and ss and ss[-1] == '(':
                            ss.pop()
                            
                            if not ss:
                                max_length = max(max_length, j - i + 1)
                        else:
                            ss.append(s[j])
                    else:
                        if len(ss) == 0: # valid + valid
                            max_length = j - i + dp[j]
                            break
                        
                        # ss is not valid, ss may be ['(','(']
                        j += dp[j] - 1
                            
                    
                    j += 1

                dp[i] = max_length
                    
            return dp[i]
        
        
        # start from right to left
        dp = {}
        
        for i in range(len(s)-1, -1, -1):
            find_dp(i, dp)
        
        # print(dp)
        
        return max((dp[k] for k in dp))

        
if __name__ == '__main__':
    solution = Solution()

    # DEFINE PARAMETERS IN HERE

    start = datetime.now()
    # RUN MAIN FUNCTION IN HERE

    s = ""

    ans = solution.longestValidParentheses(s)

    end = datetime.now()

    print(ans)
    print('\nRuntime:', (end-start))
