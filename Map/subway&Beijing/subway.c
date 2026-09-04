#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<limits.h>
#define MAX_VERTEX 512
#define INF (INT_MAX / 4)
#define NAME_LEN 64

typedef struct {
    char name[NAME_LEN];
    int is_transfer;
} Station;

// 相当于把weight和line封装在一起，方便管理
typedef struct {
    int line;
    int weight;
} Edge;

Station stations[MAX_VERTEX];
Edge graph[MAX_VERTEX][MAX_VERTEX];

// stations 里面的元素个数
int station_count = 0;

void init_graph() {
    for (int i = 0; i < MAX_VERTEX; i++) {
        for (int j = 0; j < MAX_VERTEX; j++) {
            if (i == j) {
                graph[i][j].weight = 0;
            } else {
                graph[i][j].weight = INF;
            }
            graph[i][j].line = -1;
        }
    }
}

int find_station(const char* name) {
    for (int i = 0; i < station_count; i++) {
        if (strcmp(stations[i].name, name) == 0) {
            return i;
        }
    }
    return -1; // Not found
}

int add_station(Station station) {
    stations[station_count++] = station;
    return station_count - 1; // Return the index of the newly added station
}

int get_station(Station station) {
    int index = find_station(station.name);
    if (index == -1) {
        return add_station(station);
    } else {
        return index;
    }

}

void load_map() {
    FILE* file = fopen("bgstations.txt", "r");
    if (!file) {
        printf("Failed to open bgstations.txt\n");
        exit(1);
    }
    int line_cnt;
    fscanf(file, "%d", &line_cnt);
    for (int i = 0; i < line_cnt; i++) {
        int line, station_cnt;
        fscanf(file, "%d %d", &line, &station_cnt);
        int prev = -1;   // 记录前一个站点的索引,从而表示相连
        
        for (int j = 0; j < station_cnt; j++) { 
            Station station;
            fscanf(file, "%s%d", station.name, &station.is_transfer);
            int current = get_station(station);
            if (prev != -1) {
                graph[prev][current].line = line;
                graph[prev][current].weight = 1; 
                graph[current][prev].line = line;
                graph[current][prev].weight = 1;
            }
            prev = current;
        }
    }
    // printf("%d", station_count);
    fclose(file);
}

void dijkstra(int start, int prev[]) {
    int dist[MAX_VERTEX];
    int visited[MAX_VERTEX] = {0};

    for (int i = 0; i < station_count; i++) {
        dist[i] = graph[start][i].weight;
        if (i != start && dist[i] < INF) {
            prev[i] = start;
        } else {
            prev[i] = -1;
        }
    }

    dist[start] = 0;
    visited[start] = 1;

    for (int i = 1; i < station_count; i++) {
        int min_dist = INF;
        int min_index = -1;
        for (int j = 0; j < station_count; j++) {
            if (!visited[j] && dist[j] < min_dist) {
                min_dist = dist[j];
                min_index = j;
            }
        }
        if (min_index != -1) {
            visited[min_index] = 1;
            for (int k = 0; k < station_count; k++) {
                if (!visited[k] && graph[min_index][k].weight + dist[min_index] < dist[k]) {
                    dist[k] = graph[min_index][k].weight + dist[min_index];
                    prev[k] = min_index;
                }
            }
        }
    }
}

void print_path(int start, int end, int prev[]) {
    if (start == end) {
        printf("%s", stations[start].name);
        return;
    }
    int reverse_path[MAX_VERTEX];
    int path_len = 0;

    int current = end;
    while (current != -1) {
        reverse_path[path_len++] = current;
        if (current == start) {
            break;
        }
        current = prev[current];
    }

    printf("%s", stations[reverse_path[path_len - 1]].name);

    int same_line_count = 0;
    for (int i = path_len - 1; i > 1; i--) {
        if (graph[reverse_path[i]][reverse_path[i - 1]].line == graph[reverse_path[i - 1]][reverse_path[i - 2]].line) {
            same_line_count++;        
        } else {
            printf("-%d(%d)-", graph[reverse_path[i]][reverse_path[i - 1]].line, same_line_count + 1);
            printf("%s", stations[reverse_path[i - 1]].name);
            same_line_count = 0;
        }
    }
    if (same_line_count == 0) {
        printf("-%d(%d)-%s", graph[reverse_path[1]][reverse_path[0]].line, 1, stations[reverse_path[0]].name);
    } else {
        printf("-%d(%d)-%s", graph[reverse_path[1]][reverse_path[0]].line, same_line_count + 1, stations[reverse_path[0]].name);
    }
}

int main() {
    init_graph();
    load_map();

    char start_name[NAME_LEN], end_name[NAME_LEN];
    scanf("%s %s", start_name, end_name);

    int start_index = find_station(start_name);
    int end_index = find_station(end_name);

    if (start_index == -1 || end_index == -1) {
        printf("Station not found.\n");
        return 1;
    }

    int prev[MAX_VERTEX];
    dijkstra(start_index, prev);
    print_path(start_index, end_index, prev);
    printf("\n");

    return 0;
}