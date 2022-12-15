from calendar import calendar
import heapq
from collections import deque
from datetime import datetime
from typing import List

# DEFINE SOLUTION IN HERE

class MyCalendarThree:

    def __init__(self):
        self.events = []

    def book(self, start: int, end: int) -> int:
        self.events.append((start, end))
        self.events.sort(key=lambda x: x[0])

        intersections = self.events[:]

        k = 1
        while True:

            if len(intersections) == 1:
                return k

            have_intersection = False
            new_intersections = []

            for i, a in enumerate(intersections[:-1]):
                for b in intersections[i+1:]:
                    if a[1] <= b[0]:
                        break

                    # overlap
                    have_intersection = True
                    t = (b[0], min(a[1], b[1]))
                    if not new_intersections or not (t[0] == new_intersections[-1][0] and t[1] == new_intersections[-1][1]):
                        new_intersections.append(t)                    
                    
            if not have_intersection:
                break

            intersections = new_intersections[:]
            k += 1

        return k


# Your MyCalendarThree object will be instantiated and called as such:
# obj = MyCalendarThree()
# param_1 = obj.book(start,end)


if __name__ == '__main__':

    # DEFINE PARAMETERS IN HERE

    start = datetime.now()
    # RUN MAIN FUNCTION IN HERE

    calendar = MyCalendarThree()
    
    arr2 = [[], [10, 20], [50, 60], [10, 40], [5, 15], [5, 10], [25, 55]]
    arr3 = [[],[26,35],[26,32],[25,32],[18,26],[40,45],[19,26],[48,50],[1,6],[46,50],[11,18]]

    for a in arr3[1:]:
        k = calendar.book(a[0], a[1])    
        print(k)


    end = datetime.now()

    print()
    print('\nRuntime:', (end-start))
