from typing import List
from datetime import datetime

# DEFINE SOLUTION IN HERE

# Backtracking approach.
# Not very optimal as we have to generate new array at every step.

class Solution:
    def readBinaryWatch(self, turnedOn: int) -> List[str]:
        res = []
        
        def get_hours(a):
            hour = 0
            for i in range(4):
                hour += 2 ** i * a[3-i]
            return hour
    
        def get_minutes(a):
            minute = 0
            for i in range(6):
                minute += 2 ** i * a[9-i]
            return minute
        
        def count_ones(a):
            count = 0
            for i in range(len(a)):
                if a[i] == 1:
                    count += 1
            return count
        
        def reconstruct_time(a):
            return f"{get_hours(a)}:{get_minutes(a):02}"
        
        def build_backtrack(avail, a, res, target):
            if avail:
                # check if hour is valid:
                if len(a) >= 2:
                    if a[0] and a[1]:
                        return
                
                # check if minute is valid:
                if len(a) >= 8:
                    if a[4] and a[5] and a[6] and a[7]:
                        return
                
                for i in range(2):
                    t = a[:]
                    t.append(i)
                    build_backtrack(avail-1, t, res, target)
            else:
                if count_ones(a) == target:
                    res.append(reconstruct_time(a))
                
        
        build_backtrack(10, [], res, turnedOn)
        
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