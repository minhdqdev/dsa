class Solution:
    def lengthOfLongestSubstring(self, s: str) -> int:
        if len(s) == 0:
            return 0
        
        max_length = 1
        cset = set(s[0])
        start = 0
        end = start
        
        for i in range(1, len(s)):
            if s[i] in cset:
                c_index = start + s[start:end+1].index(s[i])
                
                for k in range(start, c_index):
                    cset.remove(s[k])
                
                start = c_index + 1
            else:
                cset.add(s[i])

            end += 1
            
            new_length = end - start + 1
            if new_length > max_length:
                max_length = new_length
            
            # print(cset, max_length, s[start:end+1])
        
        return max_length
                
                
if __name__ == '__main__':
    solution = Solution()
    s = solution.lengthOfLongestSubstring('abcabcbb')

    print(s)
