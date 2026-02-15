#include<stdio.h>
#include<string.h>
#include<ctype.h>

char *strstr_ignore(char *str, char *sub) {
    if (sub == NULL || *sub == '\0') {
        return str;
    }
    char *p1,*p2;
    while(*str) {
        p1 = str;
        p2 = sub;
        while(*p1 && *p2 && (toupper(*p1) == toupper(*p2))) {
            p1++;
            p2++;
        }
        if (*p2 == '\0') {
            return str;
        }
        str++;
    }
    return NULL;
}

int main() {
    char pre[100];
    char after[100];
    scanf("%s %s",pre,after);

    FILE *source,*target;
    source = fopen("filein.txt","r");
    if (source == NULL) {
        printf("无法打开 filein.txt\n");
        return 1;
    }
    target = fopen("fileout.txt","w");
    if (target == NULL) {
        printf("无法创建 fileout.txt\n");
        fclose(source);
        return 1;
    }
    char buff[1000];
    while(fgets(buff,1000,source) !=NULL) {
        char *src = buff;
        char *hit;
        while((hit = strstr_ignore(src,pre)) !=NULL) {
            fwrite(src,1,hit-src,target);
            fwrite(after,1,strlen(after),target);
            src = hit + strlen(pre);
        }
        fwrite(src,1,strlen(src),target);
    }
    fclose(source);
    fclose(target);
    return 0;
}