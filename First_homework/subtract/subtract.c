#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXN 90

char *skip_leading_zeros(char *s)
{
    while (*s == '0' && *(s + 1) != '\0')
    {
        s++;
    }
    return s;
}

int cmp_numstr(char *A, char *B)
{
    int a = strlen(A);
    int b = strlen(B);
    if (a > b)
        return 1;
    if (a < b)
        return -1;
    int c = strcmp(A, B);
    if (c > 0)
        return 1;
    if (c < 0)
        return -1;
    return 0;
}

char *subtract_numstr(char *A, char *B)
{
    char *ans = (char *)malloc(sizeof(char) * (MAXN));
    if (ans == NULL)
        return NULL;
    int a = strlen(A) - 1;
    int b = strlen(B) - 1;
    int idx = 0;
    int borrow = 0;

    while (a >= 0)
    {
        int x = A[a] - '0' - borrow;
        int y = (b >= 0) ? (B[b] - '0') : 0;
        if (x >= y)
        {
            ans[idx++] = (x - y) + '0';
            borrow = 0;
        }
        else
        {
            ans[idx++] = (x + 10 - y) + '0';
            borrow = 1;
        }
        a--, b--;
    }

    for (int i = 0; i < idx / 2; i++)
    {
        char temp = ans[i];
        ans[i] = ans[idx - 1 - i];
        ans[idx - 1 - i] = temp;
    }

    ans[idx] = '\0';
    return ans;
}

int main()
{
    char A[MAXN], B[MAXN];
    scanf("%s %s", A, B);
    char *a = skip_leading_zeros(A);
    char *b = skip_leading_zeros(B);
    int cmp = cmp_numstr(a, b);
    if (cmp == 0)
    {
        printf("0\n");
    }
    else if (cmp > 0)
    {
        char *ans = subtract_numstr(a, b);
        char *final_ans = skip_leading_zeros(ans);
        printf("%s\n", final_ans);
        free(ans);
    }
    else
    {
        char *ans = subtract_numstr(b, a);
        char *final_ans = skip_leading_zeros(ans);
        printf("-%s\n", final_ans);
        free(ans);
    }
    return 0;
}