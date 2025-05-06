#include <stdio.h>

void bubbleSort(int arr[], int n) {
    int temp, lastSwap, boundary = n - 1;

    for (int i = 0; i < n - 1; i++) {
        lastSwap = 0;  // 初始化最后交换位
        for (int j = 0; j < boundary; j++) {
            if (arr[j] > arr[j + 1]) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                lastSwap = j;  // 更新最后交换的位置
            }
        }
        

        if (lastSwap == 0) {
            break;  // 提前结束
        }

        // 更新排序边界
        boundary = lastSwap;
    }
}

int main() {
    int testCases[3][5] = {{7, 3, 1, 4, 9}, {8, 5, 2, 6, 3}, {10, 7, 5, 2, 8}};
    int n = 5;

    for (int t = 0; t < 3; t++) {
        printf("\n测试用例 %d:\n", t + 1);
        
        bubbleSort(testCases[t], n);

        printf("最终排序结果: ");
        for (int i = 0; i < n; i++) {
            printf("%d ", testCases[t][i]);
        }
        printf("\n");
    }

    return 0;
}
