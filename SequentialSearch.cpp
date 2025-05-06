#include <stdio.h>
#include <stdlib.h>
#define N 10

int sequentialSearch(int arr[], int n, int target) {
    for (int i = n-1; i >= 0; i--) {
        if (arr[i] == target) {
            return i; 
        }
    }
    return -1;
}

int main() {

    /*int arr[] = {5, 2, 9, 1, 5, 6};
    int n = sizeof(arr) / sizeof(arr[0]);// 长度*/

    printf("请输入数组数据\n");
    int arr[N];
    for(int i = 0; i < N; i++){
        scanf("%d", &arr[i]);
    }
    int target = 56; //可改为自输入52
    int result = sequentialSearch(arr, N, target);

    //尚欠缺数组中存在多个重复数据的处理，有时间再完善
    
    if (result != -1) {
        printf("索引位置是 %d\n", result);
    } else {
        printf("不在数组中\n");
    }

    return 0;
}
