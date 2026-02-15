#include <stdio.h>
#define N 19
void checkmate(int map[][30], int n)
{
    for (int i = 4; i < n + 4; i++)
    {
        for (int j = 4; j < n + 4; j++)
        {
            int cnt = 0;
            if (map[i][j] == 1)
            {
                // 横
                for (int l = j; l <= j + 3; l++)
                {
                    if (map[i][l] == 1)
                    {
                        cnt++;
                    }
                    else
                    {
                        break;
                    }
                }
                if (cnt == 4 && (map[i][j - 1] == 0 || map[i][j + 4] == 0))
                {
                    printf("1:%d,%d\n", i - 3, j - 3);
                    return;
                }
                cnt = 0;

                // 竖
                for (int l = i; l <= i + 3; l++)
                {
                    if (map[l][j] == 1)
                    {
                        cnt++;
                    }
                    else
                    {
                        break;
                    }
                }
                if (cnt == 4 && (map[i - 1][j] == 0 || map[i + 4][j] == 0))
                {
                    printf("1:%d,%d\n", i - 3, j - 3);
                    return;
                }
                cnt = 0;

                // 左斜
                for (int l = i, r = j; l <= i + 3 && r >= j - 3; l++, r--)
                {
                    if (map[l][r] == 1)
                    {
                        cnt++;
                    }
                    else
                    {
                        break;
                    }
                    if (cnt == 4 && (map[i - 1][j + 1] == 0 || map[i + 4][j - 4] == 0))
                    {
                        printf("1:%d,%d\n", i - 3, j - 3);
                        return;
                    }
                    cnt = 0;
                }

                // 右斜
                for (int l = i, r = j; l <= i + 3 && r <= j + 3; l++, r++)
                {
                    if (map[l][r] == 1)
                    {
                        cnt++;
                    }
                    else
                    {
                        break;
                    }
                    if (cnt == 4 && (map[i - 1][j - 1] == 0 || map[i + 4][j + 4] == 0))
                    {
                        printf("1:%d,%d\n", i - 3, j - 3);
                        return;
                    }
                    cnt = 0;
                }
            }
            else if (map[i][j] == 2)
            {
                // 横
                for (int l = j; l <= j + 3; l++)
                {
                    if (map[i][l] == 2)
                    {
                        cnt++;
                    }
                    else
                    {
                        break;
                    }
                }
                if (cnt == 4 && (map[i][j - 1] == 0 || map[i][j + 4] == 0))
                {
                    printf("2:%d,%d\n", i - 3, j - 3);
                    return;
                }
                cnt = 0;

                // 竖
                for (int l = i; l <= i + 3; l++)
                {
                    if (map[l][j] == 2)
                    {
                        cnt++;
                    }
                    else
                    {
                        break;
                    }
                }
                if (cnt == 4 && (map[i - 1][j] == 0 || map[i + 4][j] == 0))
                {
                    printf("2:%d,%d\n", i - 3, j - 3);
                    return;
                }
                cnt = 0;

                // 左斜
                for (int l = i, r = j; l <= i + 3 && r >= j - 3; l++, r--)
                {
                    if (map[l][r] == 2)
                    {
                        cnt++;
                    }
                    else
                    {
                        break;
                    }
                    if (cnt == 4 && (map[i - 1][j + 1] == 0 || map[i + 4][j - 4] == 0))
                    {
                        printf("2:%d,%d\n", i - 3, j - 3);
                        return;
                    }
                    cnt = 0;
                }

                // 右斜
                for (int l = i, r = j; l <= i + 3 && r <= j + 3; l++, r++)
                {
                    if (map[l][r] == 2)
                    {
                        cnt++;
                    }
                    else
                    {
                        break;
                    }
                    if (cnt == 4 && (map[i - 1][j - 1] == 0 || map[i + 4][j + 4] == 0))
                    {
                        printf("2:%d,%d\n", i - 3, j - 3);
                        return;
                    }
                }
            }
        }
    }
    printf("No\n");
}

int main() {
    int map[30][30] = {0};
    for (int i = 4; i < N + 4; i++)
    {
        for (int j = 4; j < N + 4; j++)
        {
            scanf("%d", &map[i][j]);
        }
    }
    checkmate(map, N);
    return 0;
}