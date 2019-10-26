arr = [1,1,0,-1,-1]

print("{:.6f}".format(len(list(filter(lambda x: x < 0, arr)))/ len(arr)) )