class Solution:
    def computeArea(self, ax1: int, ay1: int, ax2: int, ay2: int, bx1: int, by1: int, bx2: int, by2: int) -> int:
        # find IoU area (top-right and bottom-left)
        
        cx2, cy2, cx1, cy1 = 0, 0, 0, 0
        
        have_iou = False
        
        if ax1 <= bx1:
            if ax2 > bx1: # overlap in x-axis
                cx1, cx2 = bx1, min(ax2, bx2)
                
                if ay1 <= by1:
                    if ay2 > by1: # overlap in y-axis
                        cy2 = min(ay2, by2)
                        cy1 = by1
                        have_iou = True
                else:
                    if by2 > ay1: # overlap in y-axis
                        cy2 = min(by2, ay2)
                        cy1 = ay1
                        have_iou = True
        else:
            if bx2 > ax1: # overlap in x-axis
                cx1, cx2 = ax1, min(ax2, bx2)
                
                if ay1 <= by1:
                    if ay2 > by1: # overlap in y-axis
                        cy2 = min(ay2, by2)
                        cy1 = by1
                        have_iou = True
                else:
                    if by2 > ay1: # overlap in y-axis
                        cy2 = min(by2, ay2)
                        cy1 = ay1
                        have_iou = True
    
        iou_area = 0
        
        if have_iou:
            iou_area = (cx2 - cx1) * (cy2 - cy1)
        
        return (ax2 - ax1) * (ay2 - ay1) + (bx2 - bx1) * (by2 - by1) - iou_area