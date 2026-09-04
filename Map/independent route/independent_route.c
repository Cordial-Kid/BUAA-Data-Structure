#include<stdio.h>
#include<stdlib.h>
#define MAX_VERTEX 1005

typedef struct edgeNode {
    int to;
    int edge_id;
    struct edgeNode* next;
} EdgeNode;

typedef struct vertex {
    EdgeNode* head;
} Vertex;

Vertex vertices[MAX_VERTEX];
int visited[MAX_VERTEX];
int path[MAX_VERTEX]; // Store the path taken during DFS
int path_len = 0;

EdgeNode* create_edge(int to, int edge_id) {
    EdgeNode* new_edge = (EdgeNode*)malloc(sizeof(EdgeNode));
    new_edge->to = to;
    new_edge->edge_id = edge_id;
    new_edge->next = NULL;
    return new_edge;
}

void add_edge(int from, int to, int edge_id) {
    EdgeNode* new_edge = create_edge(to, edge_id);
    EdgeNode** current = &vertices[from].head;
    while (*current != NULL && (*current)->edge_id < edge_id) {
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
        int edge_id, from, to;
        scanf("%d %d %d", &edge_id, &from, &to);
        add_edge(from, to, edge_id);
        add_edge(to, from, edge_id); // Assuming undirected graph
    }
}

void init_visited(int vertex_count) {
    for (int i = 0; i < vertex_count; i++) {
        visited[i] = 0;
    }
}

void free_graph(int vertex_count) {
    for (int i = 0; i < vertex_count; i++) {
        EdgeNode* current = vertices[i].head;
        while (current != NULL) {
            EdgeNode* temp = current;
            current = current->next;
            free(temp);
        }
        vertices[i].head = NULL;
    }
}

void print_path(int depth) {
    for (int i = 0; i < depth; i++) {
        printf("%d ", path[i]);
    }
    printf("\n");
}

// 按照边访问，不同路径
void DFS(int current, int target, int depth) {
    visited[current] = 1;
    if (current == target) {
        print_path(depth);
        visited[current] = 0; // Unmark the current node for other paths
        return;
    }
    for (EdgeNode* edge = vertices[current].head; edge != NULL; edge = edge->next) {
        if (!visited[edge->to]) {
            path[depth] = edge->edge_id; // Store the edge ID in the path
            DFS(edge->to, target, depth + 1);
        }
    }
    visited[current] = 0; // Unmark the current node for other paths
}

int main() {
    int vertex_count, edge_count;
    scanf("%d %d", &vertex_count, &edge_count);
    create_graph(vertex_count, edge_count);

    init_visited(vertex_count);
    DFS(0, vertex_count - 1, 0);

    free_graph(vertex_count);
    return 0;
}