class Solution:
    def countAndSay(self, n: int) -> str:
        if n == 1:
            return "1"
        
        s = "1"
        for i in range(2, n+1):
            d = {}
            ss = ""
            
            # build dict
            count = 1
            c = s[0]
            
            for j in range(1, len(s)):
                if s[j] == c:
                    count += 1
                else:
                    ss += f"{count}{c}"
                    count = 1
                    c = s[j]
            ss += f"{count}{c}"
            
            s = ss
        
        return s
