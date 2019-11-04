def print_doormat(n, m):
    for i in range(n // 2):
        print(('.|.' * (i*2 + 1)).center(m, '-'))
    print('WELCOME'.center(m, '-'))

    for i in range(n // 2-1, -1, -1):
        print(('.|.' * (i*2 + 1)).center(m, '-'))




if __name__ == '__main__':
    n, m = [int(x) for x in input().split(' ')]

    print_doormat(n,m)