if __name__ == '__main__':
    n = int(input())
    students = []
    for i in range(n):
        students.append([input(), float(input())])

    students.sort(key=lambda student: student[1])

    second_students = []
    min_score = students[0][1]
    
    second_score = min_score
    for student in students:
        if student[1] > min_score:
            if second_score == min_score:
                second_students.append(student[0])
                second_score = student[1]
            else:
                if student[1] == second_score:
                    second_students.append(student[0])
                else:
                    break

    for student in sorted(second_students):
        print(student)
