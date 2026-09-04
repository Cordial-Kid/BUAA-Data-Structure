#include<stdio.h>
#include<string.h>
#define MAX_TEXT 512
#define MAX_OPERATIONS 1000

typedef struct operation {
    int type;
    int position;
    char text[MAX_TEXT + 1];
} Operation;

Operation operations[MAX_OPERATIONS];
int operation_top = -1;

void insert_text(char* text, int position, const char* insert_text) {
    int insert_len = strlen(insert_text);
    int text_len = strlen(text);
    memmove(
        text + position + insert_len,   // 目标地址
        text + position,                // 源地址
        text_len - position + 1         // 移动的字符数
    ); 
    memcpy(text + position, insert_text, insert_len);   // 不检查内容，严格复制n个字节
}

void delete_text(char* text, int position, int length, char* deleted_text) {
    int text_len = strlen(text);
    if (position + length > text_len) {
        length = text_len -position; // Adjust length to avoid going out of bounds
    }
    strncpy(deleted_text, text + position, length);
    deleted_text[length] = '\0'; // Null-terminate the deleted text
    memmove(text + position, text + position + length, text_len - position - length + 1);
}

void undo(char* text) {
    if (operation_top < 0) {
        return; // No operations to undo
    }
    Operation last_op = operations[operation_top--];
    char foo[MAX_TEXT + 1];
    if (last_op.type == 1) {
        delete_text(text, last_op.position, strlen(last_op.text), foo);
    } else if (last_op.type == 2) {
        insert_text(text, last_op.position, last_op.text);
    }
}

int main() {
    char text[MAX_TEXT + 1] = "";
    fgets(text, sizeof(text), stdin);   // fgets会读入换行符
    text[strcspn(text, "\n")] = '\0'; // Remove newline character。碰到第二个参数的任意一个字符就停下来
    int num;
    scanf("%d", &num);
    for (int i = 0; i < num; i++) {
        Operation op;
        scanf("%d%d%s", &op.type, &op.position, &op.text);
        operations[++operation_top] = op;
    }

    while(1) {
        int type;
        scanf("%d", &type);
        if (type == -1) {
            break; // Exit the loop
        } else if (type == 1) {
            Operation op;
            op.type = 1;
            scanf("%d%s", &op.position, &op.text);
            insert_text(text, op.position, op.text);
            operations[++operation_top] = op;
        } else if (type == 2) {
            Operation op;
            op.type = 2;
            int length;
            scanf("%d%d", &op.position, &length);
            delete_text(text, op.position, length, op.text);
            operations[++operation_top] = op;
        } else if (type == 3) {
            undo(text);
        }
    }
    printf("%s\n", text);
}