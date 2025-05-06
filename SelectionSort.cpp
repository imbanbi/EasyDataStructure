#include <stdio.h>

void selectionSort(int arr[], int n) {
    int minIndex, temp;
    for (int i = 0; i < n - 1; i++) {
        minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        temp = arr[i];
        arr[i] = arr[minIndex];
        arr[minIndex] = temp;
    }
}

int main() {
    int testCases[3][5] = {{7, 3, 1, 4, 9}, {8, 5, 2, 6, 3}, {10, 7, 5, 2, 8}};
    int n = 5;

    for (int t = 0; t < 3; t++) {
        printf("\n测试用例 %d:\n", t + 1);
        
        selectionSort(testCases[t], n);

        printf("最终排序结果: ");
        for (int i = 0; i < n; i++) {
            printf("%d ", testCases[t][i]);
        }
        printf("\n");
    }
    return 0;
}
