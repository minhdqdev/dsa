if __name__ == '__main__':
    students = {}

    for i in range(int(input())):
        name, *scores = input().split(' ')
        students[name] = [float(x) for x in scores]
    
    name = input()
    print("{:.2f}".format(sum(students[name]) / len(students[name])))