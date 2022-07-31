from typing import List
from datetime import datetime
import math

# DEFINE SOLUTION IN HERE

class Solution:
    def maxPoints(self, points: List[List[int]]) -> int:
        if len(points) < 3:
            return len(points)
    
        d1 = {}
        d2 = {}
        
        res = 1
    
        for i in range(len(points)-1):
            for j in range(i+1, len(points)):
                if points[i][0] == points[j][0]: # vertical line
                    if points[i][0] not in d2:
                        d2[points[i][0]] = 1
                    else:
                        d2[points[i][0]] += 1

                        if d2[points[i][0]] > res:
                            res = d2[points[i][0]]
                else: # slope and horizontal
                    if points[j][0] > points[i][0]:
                        a = (points[j][1] - points[i][1]) / (points[j][0] - points[i][0])
                    else:
                        a = (points[i][1] - points[j][1]) / (points[i][0] - points[j][0])
                    b = points[j][1] - a * points[j][0]
                    params = (round(a, 10), round(b, 10))
                    
                    if params not in d1:
                        d1[params] = 1

                        # print("init", params, d1[params])
                    else:
                        d1[params] += 1

                        # print("update", params, d1[params])

                        if d1[params] > res:
                            res = d1[params]

        if res >= 3:
            return int((1 + math.sqrt(1 + 8 * res)) // 2)
        return 2



if __name__ == '__main__':
    solution = Solution()

    # DEFINE PARAMETERS IN HERE

    start = datetime.now()
    # RUN MAIN FUNCTION IN HERE

    a = [[-6,-1],[3,1],[12,3]]

    ans = solution.maxPoints(a)

    end = datetime.now()

    print(ans)

    print("Runtime:", end-start)