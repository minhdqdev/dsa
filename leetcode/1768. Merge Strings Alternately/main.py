class Solution:
    def mergeAlternately(self, word1: str, word2: str) -> str:
        m, n = len(word1), len(word2)
        a = []
        
        for i in range(min(len(word1), len(word2))):
            a.append(word1[i])
            a.append(word2[i])
        
        if m > n:
            for i in range(n, m):
                a.append(word1[i])
        elif m < n:
            for i in range(m, n):
                a.append(word2[i])
        
        return ''.join(a)
