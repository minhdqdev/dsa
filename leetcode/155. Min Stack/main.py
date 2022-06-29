class MinStack:

    def __init__(self):
        self.st = []
        self.mst = []
        self.min_val = None

    def push(self, val: int) -> None:
        if not self.st:
            self.min_val = val
            self.mst.append(val)
        else:
            self.mst.append(min(val, self.mst[-1]))
        
        self.st.append(val)

    def pop(self) -> None:
        self.st.pop()
        self.mst.pop()

    def top(self) -> int:
        return self.st[-1]
        

    def getMin(self) -> int:
        return self.mst[-1]


# Your MinStack object will be instantiated and called as such:
# obj = MinStack()
# obj.push(val)
# obj.pop()
# param_3 = obj.top()
# param_4 = obj.getMin()