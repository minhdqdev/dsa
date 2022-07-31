class Solution:
    def rob(self, nums: List[int]) -> int:
        # dp[n-1]: max money can be robbed in n houses
        # memoization approach
        
        n = len(nums)
        dp = [-1 for i in range(n)]
        dp[0] = nums[0]
        
        if n > 1:
            dp[1] = max(nums[0], nums[1])
        
        def find_sol(nums, dp, n):
            if dp[n] == -1:
                dp[n] = max(find_sol(nums, dp, n-1), find_sol(nums, dp, n-2) + nums[n])
            return dp[n]
        
        return find_sol(nums, dp, n-1)
        