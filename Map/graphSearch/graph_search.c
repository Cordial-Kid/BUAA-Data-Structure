// 顶点数组和边链表
#include<stdio.h>
#include<stdlib.h>
#define MAX_VERTEX 105

typedef struct edgeNode {
    int to;
    struct edgeNode* next;
} EdgeNode;

typedef struct vertex {
    EdgeNode* head;
} Vertex;

Vertex vertices[MAX_VERTEX];
int visited[MAX_VERTEX];

EdgeNode* create_edge(int to) {
    EdgeNode* new_edge = (EdgeNode*)malloc(sizeof(EdgeNode));
    new_edge->to = to;
    new_edge->next = NULL;
    return new_edge;
}

// 不分情况讨论，二级指针可以直接修改指针的内存地址
void add_edge(int from, int to) {
    EdgeNode* new_edge = create_edge(to);
    EdgeNode** current = &vertices[from].head;
    while (*current != NULL && (*current)->to < to) {
        current = &(*current)->next;
    }
    new_edge->next = *current;
    *current = new_edge;
}

void create_graph(int vertex_count, int edge_count) {
    for (int i = 0; i < vertex_count; i++) {
        vertices[i].head = NULL;
    }
    for (int i = 0; i < edge_count; i++) {
        int from, to;
        scanf("%d %d", &from, &to);
        add_edge(from, to);
        add_edge(to, from); // Assuming undirected graph
    }
}

void reset_visited(int vertex_count) {
    for (int i = 0; i < vertex_count; i++) {
        visited[i] = 0;
    }
}

void DFS(int current) {
    visited[current] = 1;
    printf("%d ", current);
    for (EdgeNode* edge = vertices[current].head; edge != NULL; edge = edge->next) {
        if (!visited[edge->to]) {
            DFS(edge->to);
        }
    }
}

void BFS(int start) {
    int queue[MAX_VERTEX];
    int front = 0, rear = 0;
    queue[rear++] = start;
    visited[start] = 1;
    while (front < rear) {
        int current = queue[front++];
        printf("%d ", current);
        for (EdgeNode* edge = vertices[current].head; edge != NULL; edge = edge->next) {
            if (!visited[edge->to]) {
                visited[edge->to] = 1;
                queue[rear++] = edge->to;
            }
        }
    }
}

void free_graph(int vertex_count) {
    for (int i = 0; i < vertex_count; i++) {
        EdgeNode* current = vertices[i].head;
        while (current != NULL) {
            EdgeNode* tmp = current;
            current = current->next;
            free(tmp);
        }
    }
}

int main() {
    int vertex_count, edge_count;
    scanf("%d %d", &vertex_count, &edge_count);
    create_graph(vertex_count, edge_count);

    reset_visited(vertex_count);
    DFS(0); // Assuming starting from vertex 0
    printf("\n");

    reset_visited(vertex_count);
    BFS(0); // Assuming starting from vertex 0
    printf("\n");

    reset_visited(vertex_count);
    int banned_vertex;
    scanf("%d", &banned_vertex);
    visited[banned_vertex] = 1;
    DFS(0); // Assuming starting from vertex 0
    printf("\n");

    reset_visited(vertex_count);
    visited[banned_vertex] = 1;
    BFS(0); // Assuming starting from vertex 0
    printf("\n");

    free_graph(vertex_count);
    return 0;
}