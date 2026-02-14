// 按字典序输出全排列
#include<stdio.h>
#include<stdlib.h>

void swap_int(int* a,int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void reverse(int* a,int l,int r) {
    while (l<r) {
        swap_int(&a[l++],&a[r--]);
    }
}

// 生成下一个字典序排列，存在则返回1，否则返回0
int next_permutation(int* a,int n) {
    int i = n-2;
    while(i >=0 && a[i] >= a[i+1]) {
        i--;
    }
    if (i < 0) {
        return 0;
    }
    int j = n-1;
    while(a[j] <= a[i]) {
        j--;
    }
    swap_int(&a[i],&a[j]);
    reverse(a,i+1,n-1);
    return 1;
}

int main() {
    int n;
    scanf("%d",&n);
    int* a = (int*)malloc(sizeof(int) * n);
    for (int i = 0;i < n;i++) {
        a[i] = i + 1;
    }
    do {
        for (int i = 0;i < n;i++) {
            printf("%d",a[i]);
        }
        printf("\n");
    } while(next_permutation(a,n));
    free(a);
}

