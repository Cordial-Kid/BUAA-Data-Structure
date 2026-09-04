#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

#define MAX_VERTEX 100
#define INF INT_MAX

int Prim(int weight[][MAX_VERTEX], int vertex_count, int start, int parent[]) {
    int low_cost[MAX_VERTEX];                // 某个点到最小生成树的最小距离
    int in_mst[MAX_VERTEX] = {0};            // 某个点是否在最小生成树中
    // parent数组用于存储某个点的父节点

    for (int i = 0; i < vertex_count; i++) {
        low_cost[i] = weight[start][i];
        if (i != start && low_cost[i] < INF) {
            parent[i] = start; // 初始化父节点为起点
        } else {
            parent[i] = -1;    // 没有父节点
        }
    }

    low_cost[start] = 0; 
    in_mst[start] = 1; 
    int total_cost = 0;

    for (int i = 1; i < vertex_count; i++) {
        int min_cost = INF;
        int min_index = -1;

        for (int j = 0; j < vertex_count; j++) {
            if (!in_mst[j] && low_cost[j] < min_cost) {
                min_cost = low_cost[j];
                min_index = j;
            }
        }

        if (min_index != -1) {
            in_mst[min_index] = 1;
            total_cost += min_cost;
            for (int k = 0; k < vertex_count; k++) {
                if (!in_mst[k] && weight[min_index][k] < low_cost[k]) {
                    low_cost[k] = weight[min_index][k];
                    parent[k] = min_index;    // 在这里更新父节点
                }
            }
        }
    }
    return total_cost;
}

int cmp(const void* a, const void* b) {
    int* num1 = (int*)a;
    int* num2 = (int*)b;
    return (*num1) - (*num2);
}

int main() {
    int vertex_count, edge_count;
    scanf("%d %d", &vertex_count, &edge_count);

    int weight[MAX_VERTEX][MAX_VERTEX];
    int edge_id[MAX_VERTEX][MAX_VERTEX]; 

    for (int i = 0; i < vertex_count; i++) {
        for (int j = 0; j < vertex_count; j++) {
            if (i == j) {
                weight[i][j] = 0;
            } else {
                weight[i][j] = INF;
            }
            edge_id[i][j] = -1;
        }
    }

    for (int i = 0; i < edge_count; i++) {
        int id, from, to, w;
        scanf("%d %d %d %d", &id, &from, &to, &w);
        weight[from][to] = w;
        weight[to][from] = w;
        edge_id[from][to] = id;
        edge_id[to][from] = id;
    }

    int parent[MAX_VERTEX];
    int total_cost = Prim(weight, vertex_count, 0, parent);

    printf("%d\n", total_cost);

    // 默认根节点是0
    int mst_edges[MAX_VERTEX];
    int edge_num = 0;

    for (int i = 0; i < vertex_count; i++) {
        if (parent[i] != -1) {
            mst_edges[edge_num++] = edge_id[i][parent[i]];
        }
    }

    qsort(mst_edges, edge_num, sizeof(int), cmp);
    for (int i = 0; i < edge_num; i++) {
        printf("%d ", mst_edges[i]);
    }
    return 0;
}