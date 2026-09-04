#include<stdio.h>
#include<string.h>

#define MAX_FUNC 205
#define NAME_LEN 20

typedef struct function {
    char name[NAME_LEN];
    int children[MAX_FUNC];
    int child_count;
} Function;

Function functions[MAX_FUNC];
int function_count = 0;

int find_function_index(const char* name) {
    for (int i = 0; i < function_count; i++) {
        if (strcmp(functions[i].name, name) == 0) {
            return i;
        }
    }
    return -1; // Function not found
}

int add_function(const char* name) {
    int index = find_function_index(name);
    if (index != -1) {
        return index; // Function already exists, return its index
    }
    functions[function_count].child_count = 0;
    strcpy(functions[function_count].name, name);
    function_count++;
    return function_count - 1;
}

int has_child(int parent_index, int child_index) {
    for (int i = 0; i < functions[parent_index].child_count; i++) {
        if (functions[parent_index].children[i] == child_index) {
            return 1;
        }
    }
    return 0;
}

void add_child(int parent_index, int child_index) {
    if (has_child(parent_index, child_index)) {
        return; // Child already exists, do not add again
    }
    int pos = functions[parent_index].child_count;
    functions[parent_index].children[pos] = child_index;
    functions[parent_index].child_count++;
}

void print_function_tree() {
    for (int i = 0; i < function_count; i++) {
        if (functions[i].child_count > 0) {
            printf("%s:", functions[i].name);
            int tmp_child_index = functions[i].children[0];
            printf("%s", functions[tmp_child_index].name);
            for (int j = 1; j < functions[i].child_count; j++) {
                int child_index = functions[i].children[j];
                printf(",%s", functions[child_index].name);
            }
            printf("\n");
        }
    }
}

int main() {
    int stack[MAX_FUNC];
    int top = -1;
    int n;
    while (scanf("%d", &n) != EOF) {
        if (n == 8) {
            char name[NAME_LEN];
            scanf("%s", name);
            int current_index = add_function(name);
            if (top >= 0) {
                int parent_index = stack[top];
                add_child(parent_index, current_index);
            }
            stack[++top] = current_index;
        }
        else {
            if (top >= 0) {
                top--; // Pop the current function from the stack
            }
        }
    }
    print_function_tree();
    return 0;
}