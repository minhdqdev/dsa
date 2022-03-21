from typing import List
from datetime import datetime

# DEFINE SOLUTION IN HERE

class Solution:
    def longestRepeating(self, s: str, queryCharacters: str, queryIndices: List[int]) -> List[int]:
        # Idea: chia s thanh cac interval (sort theo starting index)
        # De insert hieu qua thi dung DLL -> de search se mat O(n)

        # Cac query operation se co the khien cac interval bi merge hoac divide.
        # Van de la neu bi divide thi ko biet dc max_len neu ko search lai tu dau.


        res = []
        m = 1
        for i in range(len(queryIndices)):
            
            res.append(m)
            pass


        return res

if __name__ == '__main__':
    solution = Solution()

    # DEFINE PARAMETERS IN HERE

    start = datetime.now()
    # RUN MAIN FUNCTION IN HERE

    ans = solution.main()

    end = datetime.now()

    print(ans)
    print('\nRuntime:', (end-start))