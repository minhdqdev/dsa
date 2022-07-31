from typing import List
from datetime import datetime

class Solution:
    def findMax(self, i, costs, sk, lookup):
        if lookup[i] != -1:
            return lookup[i]
        
        if sk[i] - sk[i-1] != 1:
            lookup[i] = costs[sk[i]] + self.findMax(i-1, costs, sk, lookup)
        else:
            lookup[i] = max(costs[sk[i]] + self.findMax(i-2, costs, sk, lookup), self.findMax(i-1, costs, sk, lookup))
            
        return lookup[i]
            
    
    def deleteAndEarn(self, nums: List[int]) -> int:
        # init costs and sorted keys
        costs = {}
        for e in nums:
            if e not in costs:
                costs[e] = e
            else:
                costs[e] += e
        
        sk = sorted(costs.keys())
        
        # trivial cases
        if len(sk) == 1:
            return costs[sk[0]]
        elif len(sk) == 2:
            if sk[1] - sk[0] == 1:
                return max(costs[sk[0]], costs[sk[1]])
            else:
                return costs[sk[0]] + costs[sk[1]]
        
        # lookup table
        lookup = [-1 for i in range(len(sk))]
        lookup[0] = costs[sk[0]]
        if sk[1] - sk[0] == 1:
            lookup[1] = max(costs[sk[0]], costs[sk[1]])
        else:
            lookup[1] = costs[sk[0]] + costs[sk[1]]
        
        # DP
        return self.findMax(len(sk)-1, costs, sk, lookup)
            


if __name__ == '__main__':
    solution = Solution()

    # nums = [1,8,5,9,6,9,4,1,7,3,3,6,3,3,8,2,6,3,2,2,1,2,9,8,7,1,1,10,6,7,3,9,6,10,5,4,10,1,6,7,4,7,4,1,9,5,1,5,7,5]
    nums = [12,32,93,17,100,72,40,71,37,92,58,34,29,78,11,84,77,90,92,35,12,5,27,92,91,23,65,91,85,14,42,28,80,85,38,71,62,82,66,3,33,33,55,60,48,78,63,11,20,51,78,42,37,21,100,13,60,57,91,53,49,15,45,19,51,2,96,22,32,2,46,62,58,11,29,6,74,38,70,97,4,22,76,19,1,90,63,55,64,44,90,51,36,16,65,95,64,59,53,93]

    start = datetime.now()
    ans = solution.deleteAndEarn(nums)
    end = datetime.now()

    print(ans, (end-start))