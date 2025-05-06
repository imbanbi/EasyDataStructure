#include <stdio.h>
#include <stdlib.h>

#define TABLE_SIZE 10

// 除留余数
int hash(int key) {
    return key % TABLE_SIZE;
}

// 开放地址法
void insertOpenAddressing(int hashTable[], int key) {
    int index = hash(key);
    
    while (hashTable[index] != -1) {
        index = (index + 1) % TABLE_SIZE;
    }
    
    hashTable[index] = key;
}

// 查找函数
int searchOpenAddressing(int hashTable[], int key) {
    int index = hash(key);

    while (hashTable[index] != -1) {
        if (hashTable[index] == key) {
            return index; 
        }
        index = (index + 1) % TABLE_SIZE;
    }
    
    return -1; 
}

int main() {
    int hashTable[TABLE_SIZE];
    
    // 初始化
    for (int i = 0; i < TABLE_SIZE; i++) {
        hashTable[i] = -1;
    }

    // 插入元素
    insertOpenAddressing(hashTable, 12);
    insertOpenAddressing(hashTable, 25);
    insertOpenAddressing(hashTable, 32);
    
    // 查找元素
    int key = 25;
    int result = searchOpenAddressing(hashTable, key);
    if (result != -1) {
        printf("索引位置是 %d\n", result);
    } else {
        printf("不在哈希表中\n");
    }

    return 0;
}


