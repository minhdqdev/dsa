class Solution:
    def sortByBits(self, arr: List[int]) -> List[int]:

        def compare(a, b):
            c1, c2 = bin(a).count('1'), bin(b).count('1')
            if c1 > c2:
                return 1
            elif c1 < c2:
                return -1
            else:
                if a < b:
                    return -1
                elif a > b:
                    return 1
                else:
                    return 0
        
        # bubble sort
        n = len(arr)
        for i in range(n-1):
            for j in range(i+1, n):
                if compare(arr[i], arr[j]) > 0:
                    # swap
                    arr[i], arr[j] = arr[j], arr[i]
        
        return arr
                