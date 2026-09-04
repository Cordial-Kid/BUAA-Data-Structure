#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define MAX_STUDENTS 105
#define ID_LEN 10
#define NAME_LEN 25

typedef struct {
    char id[ID_LEN];
    char name[NAME_LEN];
    int position;
    int original_index;
} Student;

Student students[MAX_STUDENTS];

int cmp_by_position(const void* a, const void* b) {
    Student* student_a = (Student*)a;
    Student* student_b = (Student*)b;
    if (student_a->position != student_b->position) {
        return student_a->position - student_b->position;
    }
    return student_a->original_index - student_b->original_index;
}

int cmp_by_id(const void* a, const void* b) {
    Student* student_a = (Student*)a;
    Student* student_b = (Student*)b;
    return strcmp(student_a->id, student_b->id);
}

void fill_gaps(int students_num) {
    int sig[MAX_STUDENTS] = {0};
    qsort(students, students_num, sizeof(Student), cmp_by_position);
    int max_seat = students[students_num - 1].position;
    int seats_num = students_num > max_seat ? max_seat : students_num;
    for (int i = 0; i < students_num; i++) {
        sig[students[i].position] = 1;
    }
    int j = students_num - 1;
    for (int i = 1; i <= seats_num; i++) {
        if (!sig[i]) {
            students[j--].position = i;
        }
    }
}

void remove_duplicates(int students_num) {
    qsort(students, students_num, sizeof(Student), cmp_by_position);
    int last_position = students[students_num - 1].position;
    for (int i = 0; i < students_num -1; i++) {
        if (students[i].position == students[i + 1].position) {
            students[i+1].position = last_position + 1;
            last_position++;
        }
    }
}

int main() {
    int students_num;
    scanf("%d", &students_num);
    FILE* fp = fopen("in.txt", "r");
    for (int i = 0; i < students_num; i++) {
        fscanf(fp, "%s %s %d", students[i].id, students[i].name, &students[i].position);
        students[i].original_index = i;
    }
    fclose(fp);
    fill_gaps(students_num);
    remove_duplicates(students_num);
    qsort(students, students_num, sizeof(Student), cmp_by_id);
    for (int i = 0; i < students_num; i++) {
        printf("%s %s %d\n", students[i].id, students[i].name, students[i].position);
    }
    return 0;
}