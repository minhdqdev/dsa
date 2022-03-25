from typing import List
from datetime import datetime

# DEFINE SOLUTION IN HERE
class Solution:
    def checkStraightLine(self, coordinates: List[List[int]]) -> bool:
        # y = ax + b
        # horizontal line: y = C
        # vertical line: x = C
        
        n = len(coordinates)
        
        def gcd(a, b):
            a, b = abs(a), abs(b)

            while b:
                a, b = b, a % b
            return a
    
        def calculate_ab(p1, p2):
            if p2[0] > p1[0]:
                a = [(p2[1] - p1[1]), (p2[0] - p1[0])]
            else:
                a = [(p1[1] - p2[1]), (p1[0] - p2[0])]
            g = gcd(a[0], a[1])
            a[0], a[1] = a[0] // g, a[1] // g
        
            b = [p1[1] * a[1] - a[0] * p1[0], a[1]]
            g = gcd(b[0], b[1])
            b[0], b[1] = b[0] // g, b[1] // g
            
            return a, b
        
        if coordinates[0][0] == coordinates[1][0]: # could be vertical line
            c = coordinates[0][0]
            for i in range(2, n):
                if coordinates[i][0] != c:
                    return False
        elif coordinates[0][1] == coordinates[1][1]: # could be horizontal line
            c = coordinates[0][1]
            for i in range(2, n):
                if coordinates[i][1] != c:
                    return False
        else:
            # y1 = ax1 + b
            # y2 = ax2 + b 
            # (x2 > x1)
            
            # a = (y2-y1) / (x2-x1)
            # b = y1 - ax1
            
            a, b = calculate_ab(coordinates[0], coordinates[1])
            
            for i in range(2, n):
                if coordinates[0][0] == coordinates[i][0] or coordinates[0][1] == coordinates[i][1]:
                    return False
                
                a2, b2 = calculate_ab(coordinates[0], coordinates[i])

                if not (a[0] == a2[0] and a[1] == a2[1] and b[0] == b2[0] and b[1] == b2[1]):
                    return False
            
        return True

if __name__ == '__main__':
    solution = Solution()

    # DEFINE PARAMETERS IN HERE

    start = datetime.now()
    # RUN MAIN FUNCTION IN HERE
    coordinates = [[1,1],[2,2],[3,4],[4,5],[5,6],[7,7]] 
    ans = solution.checkStraightLine(coordinates)

    end = datetime.now()

    print(ans)
    print('\nRuntime:', (end-start))