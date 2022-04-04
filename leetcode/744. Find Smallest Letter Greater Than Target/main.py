class Solution:
    def nextGreatestLetter(self, letters: List[str], target: str) -> str:
        
        def binary_search(arr, left, right, target, last_found):
            if left > right:
                return last_found
            
            mid = (left + right) // 2
            
            if target == arr[mid]:
                return binary_search(arr, mid+1, right, target, last_found)
            elif target > arr[mid]:
                return binary_search(arr, mid+1, right, target, last_found)
            
            last_found = mid
            return binary_search(arr, left, mid-1, target, last_found)
        
        
        res = binary_search(letters, 0, len(letters)-1, target, -1)
        return letters[res if res != -1 else 0]