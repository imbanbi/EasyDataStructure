#include <stdio.h>

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// 新枢轴位置确定并调整数组
int partition(int arr[], int low, int high) {
    int pivot = arr[high]; // 初始最后一个元素为枢轴
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    // 调整枢轴位置
    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;

    return i + 1;
}

void quickSort(int arr[], int low, int high, int n) {
    if (low < high) {
        int pi = partition(arr, low, high); // 枢轴

        printf("分划后: ");
        printArray(arr, n);
        
        // 枢轴左右递归
        quickSort(arr, low, pi - 1, n);  
        quickSort(arr, pi + 1, high, n); 
    }
}

int main() {
    int testCases[3][5] = {{4, 2, 6, 9, 1}, {7, 3, 5, 8, 2}, {10, 5, 2, 7, 8}};
    int n = 5;

    for (int t = 0; t < 3; t++) {
        printf("\n测试用例 %d:\n", t + 1);
        printf("原数组: ");
        printArray(testCases[t], n);

        quickSort(testCases[t], 0, n - 1, n);

        printf("最终排序结果: ");
        printArray(testCases[t], n);
    }
    return 0;
}
