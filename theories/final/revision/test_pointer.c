#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    // char id[15];
    int grade;
} Student;

int main(){
    Student *studentList = (Student*)malloc(sizeof(Student) * 3);
    Student *ptr = studentList;

    studentList[0].grade = 10;
    // strcpy(studentList[0].id, "Minh");
    studentList[1].grade = 10;
    // strcpy(studentList[1].id, "Dang");

    // printf("%p - %s - %d\n", ptr, ptr->id, ptr->grade);
    // printf("%p - %s - %d\n", ptr+1, (ptr+1)->id, (ptr+1)->grade);
    printf("%p - %d\n", ptr, ptr->grade);
    printf("%p - %d\n", ptr+1, (ptr+1)->grade);

    
    
    return 0;
}