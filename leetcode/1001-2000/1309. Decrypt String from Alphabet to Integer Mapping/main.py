class Solution:
    def freqAlphabets(self, s: str) -> str:
        state = 0
        
        a = []
        
        def remap(c):
            return chr(ord('a') + int(c) - 1)
        
        for i in range(len(s)-1, -1, -1):
            if state == 0:
                if s[i] == '#':
                    j = i
                    state = 1
                else:
                    a.append(remap(s[i]))
            elif state == 1:
                state = 2
            else:
                a.append(remap(s[i:j]))
                state = 0
        
        return ''.join(a[::-1])