def print_rangoli(size):
    # your code goes here
    # chr(97) ord('a')
    for i in range(1, size+1):
        char_list = []
        for j in range(1, i+1):
            char_list.append(chr(97 + size - j))
        for j in range(i-1, 0, -1):
            char_list.append(chr(97 + size -j))
        print(('-'.join(char_list).center(size * 4 - 3, '-')))

    for i in range(size-1, 0, -1):
        char_list = []
        for j in range(1, i+1):
            char_list.append(chr(97 + size - j))
        for j in range(i-1, 0, -1):
            char_list.append(chr(97 + size -j))
        print(('-'.join(char_list).center(size * 4 - 3, '-')))


if __name__ == '__main__':
    n = int(input())
    print_rangoli(n)
