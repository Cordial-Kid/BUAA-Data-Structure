#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_WORDS 5000
#define WORD_LENGTH 25
#define NHASH     3001
#define MULT      37
#define ALPHABET  26

//顺序查找
void seq_search(char dict[][WORD_LENGTH], char* word, int len) {
    int cnt = 0;
    for (int i = 0; i < len; i++) {
        cnt++;
        if (strcmp(dict[i], word) == 0) {
            printf("1 %d\n", cnt);
            return;
        } else if (strcmp(dict[i], word) > 0) {
            printf("0 %d\n", cnt);
            return;
        }
    }
    printf("0 %d\n", cnt);
}

//折半查找
void binary_search(char dict[][WORD_LENGTH], char* word, int len) {
    int left = 0; 
    int right = len - 1;
    int cnt = 0;
    while(left <= right) {
        int mid = left + (right - left) / 2;
        cnt++;
        int cmp = strcmp(dict[mid], word);
        if (cmp == 0) {
            printf("1 %d\n", cnt);
            return;
        } else if (cmp < 0) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    printf("0 %d\n", cnt);
}

//索引查找
typedef struct {
    int start;
    int num;
} Index;

Index index_table[26]; // Assuming only lowercase letters a-z

void build_index_table(char dict[][WORD_LENGTH], int len) {
    for (int i = 0; i < 26; i++) {
        index_table[i].start = -1;
        index_table[i].num = 0;
    }
    for (int i = 0; i < len; i++) {
        int idx = dict[i][0] - 'a';
        if (index_table[idx].start == -1) {
            index_table[idx].start = i;
        }
        index_table[idx].num++;
    }
}

void index_search(char dict[][WORD_LENGTH], char* word, int len) {
    int idx = word[0] - 'a';
    int cnt = 0;
    int left = index_table[idx].start;
    int right = left + index_table[idx].num - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        cnt++;
        int cmp = strcmp(dict[mid], word);
        if (cmp == 0) {
            printf("1 %d\n", cnt);
            return;
        } else if (cmp < 0) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    printf("0 %d\n", cnt);
}

// hash查找
typedef struct hashNode{
    char word[WORD_LENGTH];
    struct hashNode* next;
} HashNode;

HashNode* hash_table[NHASH];

unsigned int hash(const char *str) {
    unsigned int h = 0;
    while (*str != '\0') {
        h = MULT * h + (unsigned char)*str;
        str++;
    }
    return h % NHASH;
}

void init_hash_table() {
    for (int i = 0; i < NHASH; i++) {
        hash_table[i] = NULL;
    }
}

void insert_hash_table(char* word) {
    unsigned int h = hash(word);
    HashNode* new_node = (HashNode*)malloc(sizeof(HashNode));
    strcpy(new_node->word, word);
    new_node->next = NULL;
    HashNode** current = &hash_table[h];
    while (*current != NULL && strcmp((*current)->word, word) < 0) {
        current = &(*current)->next;
    }
    new_node->next = *current;
    *current = new_node;
}

void build_hash_table(char dict[][WORD_LENGTH], int len) {
    init_hash_table();
    for (int i = 0; i < len; i++) {
        insert_hash_table(dict[i]);
    }
}

void hash_search(char* word) {
    unsigned int h = hash(word);
    HashNode* current = hash_table[h];
    int cnt = 0;
    while (current != NULL) {
        cnt++;
        int cmp = strcmp(current->word, word);
        if (cmp == 0) {
            printf("1 %d\n", cnt);
            return;        
        } else if (cmp > 0) {
            printf("0 %d\n", cnt);
            return;
        }
        current = current->next;
    }
    printf("0 %d\n", cnt);
}

void free_hash_table() {
    for (int i = 0; i < NHASH; i++) {
        HashNode* current = hash_table[i];
        while (current != NULL) {
            HashNode* temp = current;
            current = current->next;
            free(temp);
        }
    }
}

int main() {
    char dict[MAX_WORDS][WORD_LENGTH];
    int len = 0;
    FILE* fp = fopen("dictionary3000.txt", "r");
    // fgets要处理结尾问题
    while (fgets(dict[len], sizeof(dict[len]), fp) != NULL) {
        dict[len][strcspn(dict[len], "\r\n")] = '\0';
        len++;
    }
    fclose(fp);
    build_index_table(dict, len);
    build_hash_table(dict, len);

    int cmd;
    char word[WORD_LENGTH];
    scanf("%s", word);
    scanf("%d", &cmd);
    switch (cmd) {
        case 1:
            seq_search(dict, word, len);
            break;
        case 2:
            binary_search(dict, word, len);
            break;
        case 3:
            index_search(dict, word, len);
            break;
        case 4:
            hash_search(word);
            break;
        default:
            printf("Invalid command\n");
            break;
    }
    return 0;
}