from typing import List
from datetime import datetime

# DEFINE SOLUTION IN HERE

class Solution:
    def countCollisions(self, directions: str) -> int:
        count = 0

        d = [_ for _ in directions]

        count_r = 0

        if d[0] == 'R':
            count_r += 1

        for i in range(1, len(d)):
            if d[i] == 'L':
                if d[i-1] == 'R':
                    count += count_r + 1
                    count_r = 0
                    d[i] = 'S'
                elif d[i-1] == 'S':
                    count += 1
                    d[i] = 'S'
                else:
                    continue
            elif d[i] == 'S':
                if d[i-1] == 'R':
                    count += count_r
                    count_r = 0
            else:
                count_r += 1
                continue

        return count


if __name__ == '__main__':
    solution = Solution()

    # DEFINE PARAMETERS IN HERE

    start = datetime.now()
    # RUN MAIN FUNCTION IN HERE

    directions = "SSRSSRLLRSLLRSRSSRLRRRRLLRRLSSRR"
    ans = solution.countCollisions(directions)

    end = datetime.now()

    print(ans)
    print('\nRuntime:', (end-start))