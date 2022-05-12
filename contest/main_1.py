from typing import List
from datetime import datetime

# DEFINE SOLUTION IN HERE

class Solution:
    def convertTime(self, current: str, correct: str) -> int:
        hours, minutes = int(current[:2]), int(current[3:])
        
        correct_hours, correct_minutes = int(correct[:2]), int(correct[3:])
        
        diff  = correct_hours * 60 + correct_minutes - hours * 60 - minutes

        if diff < 0:
            diff += 60 * 24
        
        total_op = 0
        while diff > 0:
            if diff >= 60:
                a = diff // 60
                diff -= 60 * a
                total_op += a
            elif diff >= 15:
                a = diff // 15
                diff -= 15 * a
                total_op += a
            elif diff >= 5:
                a = diff // 5
                diff -= 5 * a
                total_op += a
            elif diff >= 1:
                a = diff // 1
                diff -= a
                total_op += a
        
        return total_op

if __name__ == '__main__':
    solution = Solution()

    # DEFINE PARAMETERS IN HERE

    start = datetime.now()
    # RUN MAIN FUNCTION IN HERE
    current = "02:30"
    correct = "04:35"
    ans = solution.convertTime(current, correct)

    end = datetime.now()

    print(ans)
    print('\nRuntime:', (end-start))