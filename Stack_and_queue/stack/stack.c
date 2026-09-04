#include<stdio.h>
#define MAXSIZE 100

int main(){
    int stack[MAXSIZE];
    int top = -1;
    int op;

    while(scanf("%d", &op) != EOF) {
        if (op == -1) {
            break;
        } else if (op == 1) {
            int x;
            scanf("%d", &x);
            if (top == MAXSIZE - 1) {
                printf("error ");
            } else {
                stack[++top] = x;
            }
        } else if (op == 0) {
            if (top == -1) {
                printf("error ");
            } else {
                printf("%d ", stack[top--]);
            }
        }
    }

    return 0;
}