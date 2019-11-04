import numpy

n, m = (int(x) for x in input().split())

matrix = []
for row in range(n):
    matrix.append([])
    matrix[row] = [int(x) for x in input().split()]


np_matrix = numpy.array(matrix)

print('[ ', end='')
print(' '.join(str(x) for x in numpy.mean(np_matrix, axis=1)), end='')
print(']')

print('[ ', end='')
print(' '.join(str(x) for x in numpy.var(np_matrix, axis=0)), end='')
print(']')

print(numpy.std(np_matrix))