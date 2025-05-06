#include <stdio.h>
#include <stdlib.h>
#define N 10

int binarySearch(int arr[], int n, int target) {
    int left = 0, right = n - 1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (arr[mid] == target) {
            return mid;  
        }
        
        if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    return -1;
}

int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);  // 返回差值，升序
}

int main() {

    /*int arr[] = {5, 2, 9, 1, 5, 6};
    int n = sizeof(arr) / sizeof(arr[0]);// 长度*/
    
    int arr[N];
    printf("请输入数组数据\n");
    for(int i = 0; i < N; i++){
        scanf("%d", &arr[i]);
    }
    qsort(arr, N, sizeof(int), compare);// 使用 qsort 排序数组
    int target = 23;
    int result = binarySearch(arr, N, target);
    if (result != -1) {
        printf("在排序后数组的%d索引位置处\n", result);
    } else {
        printf("不在数组中\n");
    }
    return 0;
}
