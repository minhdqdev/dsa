from typing import List
from datetime import datetime

# DEFINE SOLUTION IN HERE

class Solution:
    def longestStrChain(self, words: List[str]) -> int:
        res = 1
        
        s = set(words)
        
        words.sort(reverse=True, key=lambda x: len(x))
        
        chain = {} # head (child) -> parent, length of chain
        
        for i, word in enumerate(words):
            if word not in chain:
                chain[word] = (None, 1)
            
            for j in range(len(word)):
                child = word[:j] + word[j+1:]
            
                if child in s:
                    if child in chain:
                        if chain[child][1] < chain[word][1] + 1: # change chain if longer
                            chain[child] = (word, chain[word][1] + 1)
                    else:
                        chain[child] = (word, chain[word][1] + 1)
                    
                    res = max(res, chain[child][1])
            
        return res

        


if __name__ == '__main__':
    solution = Solution()

    # DEFINE PARAMETERS IN HERE

    start = datetime.now()
    # RUN MAIN FUNCTION IN HERE

    words = ["a","b","ba","bca","bda","bdca"]
    words = ["xbc","pcxbcf","xb","cxbc","pcxbc"]

    ans = solution.longestStrChain(words)

    end = datetime.now()

    print(ans)
    print('\nRuntime:', (end-start))