// 题目建议链表实现，但这里个人感觉采用数组可以优化时间复杂度（使用qsort排序）。链表需要双重循环和冒泡排序，时间复杂度O(n^2)，而数组使用qsort排序，时间复杂度O(nlogn)。

#include<stdio.h>
#include<stdlib.h>

typedef struct polygon {
    long long a;
    int b;
} Polygon;

int cmp(const void* a,const void* b) {
    Polygon* p1 = (Polygon*)a;
    Polygon* p2 = (Polygon*)b;
    return p2->b - p1->b; // 按照幂从大到小排序
}

// 动态扩容
int read_polygon(Polygon** arr) {
    int size = 8;   // 初始容量
    int n = 0;      // 当前元素数量
    *arr = (Polygon*)malloc(size * sizeof(Polygon));
    if (*arr == NULL) {
        return 0;
    }

    while(1) {
        long long a;
        int b;
        if (scanf("%lld %d", &a,&b) != 2) {
            break; // 输入结束
        }
        if (n == size) {
            size *= 2; //扩容
            Polygon* temp = (Polygon*)realloc(*arr, size * sizeof(Polygon));
            if (temp == NULL) {
                free(*arr);
                *arr = NULL;
                return 0;
            }
            *arr = temp;
        }
        (*arr)[n].a = a;
        (*arr)[n].b = b;
        n++;

        int c = getchar();
        if (c == '\n' || c == EOF) {
            break; // 输入结束
        }
        ungetc(c, stdin); // 将非换行符的字符放回输入流
    }
    return n;
}

int main() {
    Polygon* p1 = NULL,*p2 = NULL;
    int n = read_polygon(&p1);
    if (n == 0) {
        return 0;
    }
    int m = read_polygon(&p2);
    if (m == 0) {
        free(p1);
        return 0;
    }

    long long total = (long long)n * (long long )m;
    Polygon* ans = (Polygon*)malloc(total * sizeof(Polygon));
    if (ans == NULL) { 
        free(p1);
        free(p2);
        return 0;
    }

    long long idx = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            ans[idx].a = p1[i].a * p2[j].a;
            ans[idx].b = p1[i].b + p2[j].b;
            idx++;
        }
    }

    qsort(ans,total,sizeof(Polygon),cmp);

    // 线性合并同幂
    long long current_a = ans[0].a;
    int current_b = ans[0].b;
    for (long long i = 0; i < total - 1; i++) {
        if (ans[i].b == ans[i + 1].b) {
            current_a += ans[i + 1].a; // 同幂合并
        }
        else {
            printf("%lld %d ", current_a, current_b);
            current_a = ans[i + 1].a; // 更新当前幂的系数
            current_b = ans[i + 1].b; // 更新当前幂
        }
    }
    printf("%lld %d\n", current_a, current_b);
    free(p1);
    free(p2);
    free(ans);
    return 0;
}
