import heapq
from collections import deque
from datetime import datetime
from typing import List

# DEFINE SOLUTION IN HERE

class Solution:
    def leastInterval(self, tasks: List[str], n: int) -> int:
        if n == 0:
            return len(tasks)
        
        d = {} # type_task -> n_tasks
        pt = [-1 for i in range(26)] # priority table
        
        for t in tasks:
            if t not in d:
                d[t] = 1
                pt[ord(t) - ord('A')] = 0
            else:
                d[t] += 1
        
        def get_next_task():
            next_task = None # highest priority and has the largest number of remain tasks

            # query priority table to get the next task
            for i in range(len(pt)):
                c = chr(ord('A') + i)
                
                if pt[i] == 0: # can be the next task
                    if not next_task:
                        next_task = c 
                    else:
                        if d[next_task] < d[c]:
                            next_task = c

                elif pt[i] > 0:
                    pt[i] -= 1
            
            if next_task:
                i = ord(next_task) - ord('A')
                pt[i] = n
                d[next_task] -= 1

                if d[next_task] == 0: # remove from priority table if nothing left
                    pt[i] = -1
            
            return next_task
        
        remain, steps = len(tasks), 0

        tt = []

        while remain:
            next_task = get_next_task()
            
            if next_task != ' ':
                remain -= 1
            steps += 1

            tt.append(next_task)

        print(tt)

        return steps
        
        


if __name__ == '__main__':
    solution = Solution()

    # DEFINE PARAMETERS IN HERE

    start = datetime.now()
    # RUN MAIN FUNCTION IN HERE

    tasks = ["A","A","A","B","B","B", "C","C","C", "D", "D", "E"]
    n = 2

    ans = solution.leastInterval(tasks, n)

    end = datetime.now()

    print(ans)
    print('\nRuntime:', (end-start))
