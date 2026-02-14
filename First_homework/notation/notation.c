#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAXN 110

void notation(char *str)
{
    int len = strlen(str);
    char *digits = (char *)malloc(sizeof(char) * MAXN);
    int idx = 0;
    int pre_dot_pos = 0;
    int valid_pos = 0;
    int exp;

    for (int i = 0; i < len; i++)
    {
        if (str[i] == '.')
        {
            pre_dot_pos = i;
        }
        else
        {
            digits[idx++] = str[i];
        }
    }

    for (int i = 0; i < idx; i++)
    {
        if (digits[i] != '0')
        {
            valid_pos = i;
            break;
        }
    }
    // 指数部分是（小数点前面的位数 - 1）- （第一个非0数字的索引）
    exp = pre_dot_pos - 1 - valid_pos;
    // 底数部分
    if (len - 2 == valid_pos)
    {
        printf("%c", digits[valid_pos]);
    }
    else
    {
        printf("%c.", digits[valid_pos]);
        for (int i = valid_pos + 1; i < idx; i++)
        {
            printf("%c", digits[i]);
        }
    }
    putchar('e');
    printf("%d\n", exp);
    free(digits);
}

int main()
{
    char str[MAXN];
    scanf("%s", str);
    notation(str);
    return 0;
}