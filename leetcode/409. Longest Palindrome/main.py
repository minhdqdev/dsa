class Solution:
    def longestPalindrome(self, s: str) -> int:
        d = {}
        
        for c in s:
            if c not in d:
                d[c] = 1
            else:
                d[c] += 1
        
        is_odd = False
        res = 0
        
        for k in d:
            if d[k] % 2 == 0:
                res += d[k]
            else:
                is_odd = True
                res += d[k] - 1
        
        return (res + 1) if is_odd else res
