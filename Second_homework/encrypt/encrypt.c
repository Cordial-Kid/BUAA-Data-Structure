#include<stdio.h>
#include<string.h>
#include<ctype.h>

int mem[500];
char encrypt[60];

void get_encrypt(char *str,int len) {
    int idx = 0;
    for (int i = 0 ; i < len; i++) {
        if (mem[str[i]] == 0) {
            encrypt[idx++] = str[i];
            mem[str[i]] = 1;
        }
    }
    for (int i = 122;i >= 97;i--) {
        if (mem[i] ==0) {
            encrypt[idx++] = i;
        }
    }
}

int main() {
    char str[60];
    char buff[1000]; //用来存储加密后的字符串 
    scanf("%s",str);
    int len = strlen(str);
    get_encrypt(str,len);

    FILE *source,*target;
    source = fopen("encrypt.txt","r");
    if (source == NULL) {
        printf("无法打开 encrypt.txt\n");
        return 1;
    }
    target = fopen("output.txt","w");
    if (target == NULL) {
        printf("无法创建 output.txt\n");
        fclose(source);
        return 1;
    }
    while(fgets(buff,1000,source) != NULL) {
        int l = strlen(buff);
        for (int i = 0; i < l; i++) {
            if (islower(buff[i])) {
                buff[i] = encrypt[buff[i] - 'a'];
            }
        }
        fputs(buff,target);
    }
    fclose(source);
    fclose(target);
    return 0;
}