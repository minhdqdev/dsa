# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
class Solution:
    def isPalindrome(self, head: Optional[ListNode]) -> bool:
        # Time complexity: O(N)
        # Space complexity: O(1)
        
        # Idea: reverse the first half
        # - n is odd: reverse(head, n // 2) and ignore the middle node when check
        # - n is even: reverse(head, n // 2)
        
        n = 0
        cur = head
        while cur:
            n += 1
            cur = cur.next
        
        if n == 1:
            return True
    
        def reverse_sublist(head, k):
            prev = None
            cur = head
            
            i = 0
            while i < k:
                next = cur.next
                cur.next = prev
                prev = cur
                cur = next
                i += 1
            
            return prev, cur
    
        head1, head2 = reverse_sublist(head, n // 2)
        
        if n % 2 != 0:
            head2 = head2.next
        
        for i in range(n // 2):
            if head1.val != head2.val:
                return False
            
            head1 = head1.next
            head2 = head2.next
        
        return True

        
        
        