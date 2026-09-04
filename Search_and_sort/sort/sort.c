#include<stdio.h>
#include<stdlib.h>
#define MAX_N 1000

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void print_result(int* arr, int len, int cnt) {
    for (int i = 0; i < len; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n%d\n", cnt);
}

void select_sort(int* arr, int len) {
    int cnt = 0;
    for (int i = 0; i < len - 1; i++) {
        int min_index = i;
        // 进循环之前先给一个min_index
        for (int j = i + 1; j < len; j++) {
            cnt++;
            if (arr[j] < arr[min_index]) {
                min_index = j;
            }
        }
        if (min_index != i) {
            swap(&arr[i], &arr[min_index]);
        }
    }
    print_result(arr, len, cnt);
}

void bubble_sort(int* arr, int len) {
    int cnt = 0;
    for (int i = 0; i < len - 1; i++) {
        int swapped = 0;
        for (int j = 0; j < len - 1 - i; j++) {
            cnt++;
            if (arr[j] > arr[j + 1]) {
                swap(&arr[j], &arr[j + 1]);
                swapped = 1;
            }
        }
        if (!swapped) {
            break;
        }
    }
    print_result(arr, len, cnt);
}

// 建立大顶堆
// 0 为下标起点
//左: 2 * root + 1
//右: 2 * root + 2
void adjust_heap(int* arr, int len, int root, int* cnt) {
    int temp = arr[root];
    int child = 2 * root + 1;    // left child
    while (child < len) {
        if (child + 1 < len && arr[child] < arr[child + 1]) {
            child++;
        }
        (*cnt)++;
        if (temp >= arr[child]) {
            break;
        }
        arr[root] = arr[child];
        root = child;
        child = 2 * root + 1;
    }
    arr[root] = temp;
}

void heap_sort(int* arr, int len) {
    int cnt = 0;
    for (int i = len / 2 - 1; i >= 0; i--) {
        adjust_heap(arr, len, i, &cnt);
    }
    // 将堆顶元素与末尾元素交换，并调整堆
    for (int i = len - 1; i > 0; i--) {
        swap(&arr[0], &arr[i]);
        adjust_heap(arr, i, 0, &cnt);
    }
    print_result(arr, len, cnt);
}

void merge(int* arr, int* temp, int left, int mid, int right, int* cnt) {
    int i = left;
    int j = mid + 1;
    int k = left;

    while (i <= mid && j <= right) {
        (*cnt)++;
        if (arr[i] < arr[j]) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
        }
    }
    while (i <= mid) {
        temp[k++] = arr[i++];
    }
    while (j <= right) {
        temp[k++] = arr[j++];
    }
    for (int l = left; l <= right; l++) {
        arr[l] = temp[l];
    }
}

void merge_sort_recursive(int* arr, int* temp, int left, int right, int* cnt) {
    if (left >= right) {
        return;
    }
    int mid = left + (right - left) / 2;
    merge_sort_recursive(arr, temp, left, mid, cnt);
    merge_sort_recursive(arr, temp, mid + 1, right, cnt);
    merge(arr, temp, left, mid, right, cnt);
}

void merge_sort(int* arr, int len) {
    int cnt = 0;
    int* temp = (int*)malloc(len * sizeof(int));
    merge_sort_recursive(arr, temp, 0, len - 1, &cnt);
    free(temp);
    print_result(arr, len, cnt);
}

void quick_sort_recursive(int* arr, int left, int right, int* cnt) {
    if (left >= right) {
        return;
    }
    int pivot = arr[left];
    int last = left;
    for (int i = left + 1; i <= right; i++) {
        (*cnt)++;
        if (arr[i] < pivot) {
            swap(&arr[++last], &arr[i]);
        }
    }
    swap(&arr[left], &arr[last]);
    quick_sort_recursive(arr, left, last - 1, cnt);
    quick_sort_recursive(arr, last + 1, right, cnt);
}

void quick_sort(int* arr, int len) {
    int cnt = 0;
    quick_sort_recursive(arr, 0, len - 1, &cnt);
    print_result(arr, len, cnt);
}

void sort(int sig,int arr[],int len){
	switch(sig){
		case 1: 
			select_sort(arr,len);
			break;
		case 2:
			bubble_sort(arr,len);
			break;
		case 3:
			heap_sort(arr,len);
			break;
		case 4:
			merge_sort(arr,len);
			break;
		case 5:
			quick_sort(arr,len);
			break;
	}
}

int main() {
    int n, sig;
    int arr[MAX_N];
    scanf("%d %d", &n, &sig);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    sort(sig, arr, n);
    return 0;
}