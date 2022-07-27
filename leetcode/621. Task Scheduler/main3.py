import heapq
from collections import deque
from datetime import datetime
from typing import List

# DEFINE SOLUTION IN HERE

class Solution:
    def leastInterval(self, tasks: List[str], n: int) -> int:
        d = {}
        pq = []
        
        for t in tasks:
            if t not in d:
                d[t] = 1
            else:
                d[t] += 1
        
        for t in tasks:
            pq.append((-d[t], t))
        
        heapq.heapify(pq)



        def get_next_task():
            p, nt = heapq.heappop(pq)

            if nt == ' ':
                return nt

            d[nt] -= 1

            if d[nt] > 0:
                if len(pq) < n:
                    for _ in range(n - len(pq)):
                        pq.append(' ')
                pq.append(nt)

            return nt
        
        remain, steps = len(tasks), 0

        tt = []

        while remain:
            next_task = get_next_task()
            
            if next_task not in ' ':
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

    # tasks = ["A","A","A","B","B","B", "C","C","C", "D", "D", "E"]
    # n = 2

    tasks = ["A","A","A","A","A","A","B","C","D","E","F","G"]
    n = 2

    ans = solution.leastInterval(tasks, n)

    end = datetime.now()

    print(ans)
    print('\nRuntime:', (end-start))
