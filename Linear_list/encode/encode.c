#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define ASCII_MIN 32
#define ASCII_MAX 126

typedef struct node {
    char raw;
    char now;
    struct node *next;
} Node;

int mem[150];
char ans[100];

Node* create_node(char raw) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->raw = raw;
    new_node->now = 0;
    new_node->next = NULL;
    return new_node;
}

void build_circle(char *str,Node** head,Node** tail) {    // 修改节点指向用二重指针
    *head = NULL;
    *tail = NULL;
    memset(mem,0,sizeof(mem));

    for(int i = 0; str[i]; i++) {
        if (mem[str[i]] == 0) {
            Node* new_node = create_node(str[i]);
            if (*head == NULL) {
                *head = new_node;
                *tail = new_node;
            }
            else {
                (*tail)->next = new_node;
                *tail = new_node;
            }
            mem[str[i]] = 1;
        }
    }
    for (int i = ASCII_MIN; i <= ASCII_MAX; i++) {
        if (mem[i] == 0) {
            Node* new_node = create_node(i);
            if (*head == NULL) {
                *head = new_node;
                *tail = new_node;
            }
            else {
                (*tail) -> next = new_node;
                *tail = new_node;
            }
        }
    }
    if (*tail) {
        (*tail) -> next = *head; // 形成循环链表
    }
}

void free_circle(Node* head) {
    if (head == NULL) return;
    Node* current = head -> next;
    while(current != head) {
        Node* temp = current;
        current = current -> next;
        free(temp);
    }
    free(head);
}

void free_list(Node* head) {
    Node* current = head;
    while(current) {
        Node* temp = current;
        current = current -> next;
        free(temp);
    }
}

Node* build_map(Node* head,Node* tail) {
    if (head == NULL || tail == NULL) {
        return NULL;
    }

    Node* map_head = NULL;
    Node* map_tail = NULL;

    Node* current = head;
    char c = current -> raw;
    Node* preV = tail;
    int remainning  = 95; // ASCII范围内的字符数量
    while (remainning > 1) {
        int num = current -> raw;
        int step = (num - 1) % (remainning - 1);
        Node* temp_current = current;      // temp to be deleted
        Node* temp_preV = preV;            // temp's previous node
        current = current -> next;
        preV = preV ->next;
        for (int i = 0; i < step; i++) {
            current = current -> next;
            preV = preV -> next;
        }
        // 映射关系建立
        Node* new_node = create_node(current -> raw);
        new_node -> now = current -> raw;
        new_node -> raw = temp_current -> raw;
        if (map_head == NULL) {
            map_head = map_tail = new_node;
        }
        else {
            map_tail -> next = new_node;
            map_tail = new_node;
        }

        // 删除temp节点
        temp_preV -> next = temp_current -> next;
        // 如果被删除的节点是preV，更新preV指向
        if (preV == temp_current) {   
            preV = temp_preV;
        }
        free(temp_current);
        remainning--;
    }
    // 最后一个节点的映射关系
    Node* new_node = create_node(current -> raw);
    new_node -> now = c;
    if (map_head == NULL) {
        map_head = map_tail = new_node;
    }
    else {
        map_tail -> next = new_node;
        map_tail = new_node;
    }
    free(current);
    return map_head;
}

int main() {
    char str[100];
    gets(str);    // gets不读取换行符，fgets会读取换行符，使用fgets需要处理换行符
    Node* head = NULL;
    Node* tail = NULL;
    build_circle(str,&head,&tail);
    Node* map_head = build_map(head,tail);

    FILE* source = fopen("in.txt","r");
    if (source == NULL) {
        printf("无法打开 in.txt\n");
        free_list(map_head);
        return 1;
    }
    FILE* target = fopen("in_crypt.txt","w");
    if (target == NULL) {
        printf("无法创建 in_crypt.txt\n");
        fclose(source);
        free_list(map_head);
        return 1;
    }
    char buff[1000];
    while (fgets(buff,1000,source) != NULL) {
        int l = strlen(buff);
        for (int i = 0; i < l; i++) {
            if (buff[i] >= ASCII_MIN && buff[i] <= ASCII_MAX) {
                Node* current = map_head;
                while (current) {
                    if (current -> raw == buff[i]) {
                        buff[i] = current -> now;
                        break;
                    }
                    current = current -> next;
                }
            }
        }
        fputs(buff,target);
    }

    fclose(source);
    fclose(target);
    free_list(map_head);
    return 0;
}