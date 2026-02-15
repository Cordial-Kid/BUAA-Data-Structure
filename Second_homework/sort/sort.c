#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAXN 105
#define NAMEL 25
#define PHONEL 15

typedef struct {
    char name[NAMEL];
    char phone[PHONEL];
    int idx; // 用于记录原始输入顺序
} Contact;

int cmp_contact(const void *a, const void *b) {
    Contact *c1 = (Contact *)a;
    Contact *c2 = (Contact *)b;
    int name_cmp = strcmp(c1->name, c2->name);
    if (name_cmp != 0) {
        return name_cmp;
    }
    return c1->idx - c2->idx;
}

int main() {
    int n;
    scanf("%d",&n);
    Contact contacts[MAXN];
    for (int i = 0;i < n;i++) {
        scanf("%s %s",contacts[i].name,contacts[i].phone);
        contacts[i].idx = i;
    }
    qsort(contacts,n,sizeof(Contact),cmp_contact);

    // 去重
    int len = 0;
    for (int i = 0;i < n; i++) {
        if (i == 0 || !(strcmp(contacts[i].name, contacts[i-1].name) == 0 && strcmp(contacts[i].phone, contacts[i-1].phone) == 0)) {
            contacts[len++] = contacts[i];
        }
    }

    // 输出
    int same_name_count = 0;
    for (int i = 0; i < len; i++) {
        if (i > 0 && strcmp(contacts[i].name,contacts[i-1].name) == 0) {
            same_name_count++;
        }
        else {
            same_name_count = 0;
        }
        if (same_name_count > 0) {
        printf("%s_%d %s\n",contacts[i].name,same_name_count,contacts[i].phone);
        }
        else {
            printf("%s %s\n",contacts[i].name,contacts[i].phone);
        }
    }
}