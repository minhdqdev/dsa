from typing import List
from datetime import datetime
import heapq
from time import sleep

# DEFINE SOLUTION IN HERE

class Solution:
    def count_ahead(self, a, d):
        count = 0
        
        for key in d:
            if key >= a[0]:
                count += d[key]
        
        return count
    
    def reconstructQueue(self, people: List[List[int]]) -> List[List[int]]:
        # greedy approach
    
        res = []
        heapq.heapify(people)
        d = {}
        
        while True:
            temp = []
            
            for _ in range(len(people)):
                a = heapq.heappop(people)

                if self.count_ahead(a, d) != a[1]:
                    # skip
                    temp.append(a)
                else:
                    # append to result queue
                    res.append(a)
                    
                    if a[0] not in d:
                        d[a[0]] = 1
                    else:
                        d[a[0]] += 1

                    # have to find the next value again
                    break

            if not temp and not people:
                break

            for a in temp:
                heapq.heappush(people, a)
                

            # sleep(1)
            # print(temp, res, d)    
        
        return res
            


if __name__ == '__main__':
    solution = Solution()

    # DEFINE PARAMETERS IN HERE

    start = datetime.now()
    # RUN MAIN FUNCTION IN HERE
    people = [[7,0],[4,4],[7,1],[5,0],[6,1],[5,2]]
    ans = solution.reconstructQueue(people)

    end = datetime.now()

    print(ans)
    print('\nRuntime:', (end-start))