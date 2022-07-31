class Solution:
    def addStrings(self, num1: str, num2: str) -> str:
        m, n = len(num1), len(num2)
        
        # zero padding
        if m > n:
            num2 = '0' * (m-n) + num2
        elif m < n:
            num1 = '0' * (n-m) + num1
        
        rem = 0
        res = []
        for i in range(len(num1)-1, -1, -1):
            s = rem + int(num1[i]) + int(num2[i])
            
            rem = s // 10
            res.append(str(s % 10))
        
        if rem:
            res.append(str(rem))
        
        return ''.join(res[::-1])
            
            
            