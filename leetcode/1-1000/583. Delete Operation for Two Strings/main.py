from typing import List
from datetime import datetime

# DEFINE SOLUTION IN HERE
class Solution:
    def lcs(self, word1, word2, i, j, dp):
        """Largest common subsequence"""
        
        if (i, j) not in dp:
            if i == len(word1) or j == len(word2):
                dp[(i, j)] = 0
            elif word1[i] == word2[j]:
                dp[(i, j)] = 1 + self.lcs(word1, word2, i+1, j+1, dp)
            else:
                dp[(i, j)] = max(
                    self.lcs(word1, word2, i+1, j, dp),
                    self.lcs(word1, word2, i, j+1, dp),
                )
        
        return dp[(i, j)]
    
    def minDistance(self, word1: str, word2: str) -> int:
        dp = {} # memoization
        return len(word1) + len(word2) - 2 * self.lcs(word1, word2, 0, 0, dp)

if __name__ == '__main__':
    solution = Solution()

    # DEFINE PARAMETERS IN HERE

    start = datetime.now()
    # RUN MAIN FUNCTION IN HERE
    """
        "sea"
        "eat"
        "leetcode"
        "etco"
        "dinitropheny"
        "acetylpheny"
    """

    word1 = "dinitropheny"
    word2 = "acetylpheny"

    ans = solution.minDistance(word1, word2)

    end = datetime.now()

    print(ans)
    print('\nRuntime:', (end-start))