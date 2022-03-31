class Solution:
    def isAlienSorted(self, words: List[str], order: str) -> bool:
        
        m = {} # char -> index
        for i, c in enumerate(order):
            m[c] = i
                
        def compare(s1, s2, m):
            i = 0
            
            while i < min(len(s1), len(s2)):
                if m[s1[i]] < m[s2[i]]:
                    return -1
                elif m[s1[i]] > m[s2[i]]:
                    return 1
                else:
                    i += 1
            
            if len(s1) < len(s2):
                return -1
            elif len(s1) > len(s2):
                return 1
            return 0
        
        
        for i in range(1, len(words)):
            if compare(words[i-1], words[i], m) > 0:
                return False
        
        return True
        
            
            