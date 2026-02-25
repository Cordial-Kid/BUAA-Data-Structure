#include<stdio.h>
#include<stdlib.h>

typedef struct segment {
    int x1, y1, x2, y2;
} Segment;

void find_max(Segment* segments,int n,int* ans,int* X,int* Y) {
    int head_x,head_y;
    int tail_x,tail_y;
    for (int i = 0; i < n; i++) {
        int cnt = 1;
        head_x = segments[i].x1;
        head_y = segments[i].y1;
        tail_x = segments[i].x2;
        tail_y = segments[i].y2;
        for (int j = 0; j < n; j++) {
            if (tail_x == segments[j].x1 && tail_y == segments[j].y1) {
                cnt++;
                tail_x = segments[j].x2;
                tail_y = segments[j].y2;
                j = -1; // 重新从头开始检查
            }  
        }
        if (cnt > *ans) {
            *ans = cnt;
            *X = head_x;
            *Y = head_y;
        }
    }
}
int main() {
    Segment segments[100];
    int n;
    scanf("%d",&n);
    for (int i = 0; i < n; i++) {
        scanf("%d %d %d %d",&segments[i].x1, &segments[i].y1, &segments[i].x2, &segments[i].y2);
    }

    int ans = 1;
    int X,Y;

    find_max(segments,n,&ans,&X,&Y);
    printf("%d %d %d\n",ans,X,Y);
    return 0;
}