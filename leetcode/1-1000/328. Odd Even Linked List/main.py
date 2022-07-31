# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
class Solution:
    def oddEvenList(self, head: Optional[ListNode]) -> Optional[ListNode]:
        if not head or not head.next or not head.next.next:
            return head
    
        head1 = head
        head2 = head.next
        
        prev = head1
        cur = head1.next.next if head1.next else None
        
        while cur:
            e1 = prev.next
            e2 = cur.next
            prev.next = cur
            prev = cur
            cur = cur.next.next if cur.next else None
            
            e1.next = e2
            if e2:
                e2.next = None
        
        tail1 = prev
        tail1.next = head2
        return head1
        
        