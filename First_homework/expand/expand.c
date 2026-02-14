#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *expand(const char *str)
{
    int len = strlen(str);

    char *ans = (char *)malloc(sizeof(char) * 100008);
    if (ans == NULL)
        return NULL;

    int idx = 0;
    for (int i = 0; i < len; i++)
    {
        if (str[i] != '-')
        {
            ans[idx++] = str[i];
        }
        else
        {
            if (str[i - 1] >= 'a' && str[i - 1] <= 'z' && str[i + 1] >= 'a' && str[i + 1] <= 'z' && str[i - 1] < str[i + 1])
            {
                for (char c = str[i - 1] + 1; c < str[i + 1]; c++)
                {
                    ans[idx++] = c;
                }
            }
            else if (str[i - 1] >= 'A' && str[i - 1] <= 'Z' && str[i + 1] >= 'A' && str[i + 1] <= 'Z' && str[i - 1] < str[i + 1])
            {
                for (char c = str[i - 1] + 1; c < str[i + 1]; c++)
                {
                    ans[idx++] = c;
                }
            }
            else if (str[i - 1] >= '0' && str[i - 1] <= '9' && str[i + 1] >= '0' && str[i + 1] <= '9' && str[i - 1] < str[i + 1])
            {
                for (char c = str[i - 1] + 1; c < str[i + 1]; c++)
                {
                    ans[idx++] = c;
                }
            }
            else
            {
                ans[idx++] = '-';
            }
        }
    }
    ans[idx] = '\0';
    return ans;
}

int main()
{
    char str[100008];
    scanf("%s", str);
    char *ans = expand(str);
    if (ans != NULL)
    {
        printf("%s\n", ans);
        free(ans);
    }
    return 0;
}