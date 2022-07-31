# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
class Solution:
    def swapNodes(self, head: Optional[ListNode], k: int) -> Optional[ListNode]:
        # Do 2 passes to find the 1st and 2nd node
        # I don't think this is a optimal solution but it is still AC.
        
        first, second, prev_first, prev_second = None, None, None, None
        
        i = 0
        prev_cur, cur = None, head
        while cur:
            if i + 1 == k:
                prev_first, first = prev_cur, cur
                
            prev_cur = cur
            cur = cur.next
            
            i += 1
        
        k2 = i - k + 1
        
        i = 0
        prev_cur, cur = None, head
        
        while cur:
            if i + 1 == k2:
                prev_second, second = prev_cur, cur
            
            prev_cur = cur
            cur = cur.next
            
            i += 1
        
        first.val, second.val = second.val, first.val
        
#         if not prev_first: # first node is head
#             head = second
            
#             temp = first.next
#             first.next = second.next
#             second.next = temp
#             prev_second.next = first
#             # prev_first.next = second
#         else:
#             temp = first.next
#             first.next = second.next
#             second.next = temp
#             prev_second.next = first
#             prev_first.next = second
        
        return head
        
        
        