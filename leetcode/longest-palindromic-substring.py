class Solution:
    def longestPalindrome(self, s: str) -> str:        
        for i in range(len(s), 1, -1):
            for j in range(0, len(s) - i + 1):
                st = s[j:j+i]
                if st == st[::-1]:
                    return s[j:j+i]
        
        return s[0]


if __name__ == '__main__':
    solution = Solution()

    print(solution.longestPalindrome('bb'))