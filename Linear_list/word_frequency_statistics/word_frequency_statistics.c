#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

typedef struct frequency {
    char words[20];
    int count;
} Frequency;


int cmp(const void* a,const void* b) {
    Frequency* f1 = (Frequency*)a;
    Frequency* f2 = (Frequency*)b;
    return strcmp(f1->words, f2->words); // 按照单词字典序排序
}

void addWord(Frequency* frequencys,int* frequencys_idx,char* word) {
    for (int i = 0; i < *frequencys_idx; i++) {
        if (strcmp(frequencys[i].words, word) == 0) {
            frequencys[i].count++;
            return;
        }
    }
    strcpy(frequencys[*frequencys_idx].words, word);
    frequencys[*frequencys_idx].count = 1;
    (*frequencys_idx)++;
}
int main() {
    char buffer[500];
    FILE* source = fopen("article.txt","r");
    if (source == NULL) {
        printf("无法打开文件\n");
        return 1;
    }

    Frequency frequencys[1000]; // 存储单词频率的数组
    char word[20];
    int frequencys_idx = 0;
    int word_idx = 0;
    char ch;

    while((ch = fgetc(source)) != EOF) {
        if (isalpha(ch)) {
            word[word_idx++] = tolower(ch); // 将字母转换为小写
        } else {
            if (word_idx > 0) {
                word[word_idx] = '\0'; // 结束单词
                addWord(frequencys, &frequencys_idx, word);
                word_idx = 0; // 重置单词索引
                memset(word, 0, sizeof(word)); // 清空单词数组
            }
        }
    }

    // 处理最后一个单词
    if (word_idx > 0) {
        word[word_idx] = '\0';
        addWord(frequencys,&frequencys_idx, word);
    }

    qsort(frequencys,frequencys_idx,sizeof(Frequency),cmp);

    for (int i = 0; i < frequencys_idx; i++) {
        printf("%s %d\n",frequencys[i].words,frequencys[i].count);
    }
    fclose(source);
    return 0;
}