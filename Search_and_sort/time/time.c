#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_STUDENTS 105
#define ID_LEN 10
#define NAME_LEN 25

typedef struct {
    char id[ID_LEN];
    char name[NAME_LEN];
    int time;
} Student;

Student students[MAX_STUDENTS];

int cmp_by_time(const void* a, const void* b) {
    Student* student_a = (Student*)a;
    Student* student_b = (Student*)b;
    if (student_a->time != student_b->time) {
        return student_b->time - student_a->time;
    }
    return strcmp(student_a->id, student_b->id);
}

int cmp_by_id(const void* a, const void* b) {
    Student* student_a = (Student*)a;
    Student* student_b = (Student*)b;
    return strcmp(student_b->id, student_a->id);
}

void merge_data(int num_of_data) {
    qsort(students, num_of_data, sizeof(Student), cmp_by_id);
    for (int i = 0; i < num_of_data - 1; i++) {
        if (strcmp(students[i].id, students[i + 1].id) == 0) {
            students[i + 1].time += students[i].time;
            students[i].time = 0;
        }
    }
}

int main() {
    int num_of_data;
    scanf("%d", &num_of_data);
    for (int i = 0; i < num_of_data; i++) {
        scanf("%s %s %d", students[i].id, students[i].name, &students[i].time);
    }
    merge_data(num_of_data);
    qsort(students, num_of_data, sizeof(Student), cmp_by_time);
    for (int i = 0; i < num_of_data; i++) {
        if (students[i].time > 0) {
            printf("%s %s %d\n", students[i].id, students[i].name, students[i].time);
        }
    }
}
