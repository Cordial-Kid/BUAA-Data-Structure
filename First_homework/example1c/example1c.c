#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

#define MAXN 1008

char expression[100008];

int calc(char* exp) {
    int len = strlen(exp);
    int ans = 0;
    char op = '+';
    long long num = 0;
    int* res = (int*)malloc(sizeof(int) * MAXN);
    int idx = 0;
    
    for (int i = 0; i < len; i++) {
        if (isdigit(exp[i])) {
            num = num * 10 + (exp[i] - '0');
            continue;
        }
        else if (exp[i] == ' ') {
            continue;
        }
        else {
            if (op == '+') {
                res[idx++] = num;
            }
            else if (op == '-') {
                res[idx++] = -num;
            }
            else if(op == '*') {
                res[idx - 1] = res[idx - 1] * num;
            }
            else if(op == '/') {
                res[idx - 1] = res[idx - 1] / num;
            }
            op = exp[i];
            num = 0;
        }
    }
    
    for (int i = 0;i < idx; i++) {
        ans += res[i];
    }

    free(res);
    return ans;
} 

int main() {
    fgets(expression,sizeof(expression),stdin);
    int ans = calc(expression);
    printf("%d\n",ans);
    return 0;
}
