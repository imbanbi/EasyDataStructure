#include <stdio.h>
#include <stdlib.h>

#define TABLE_SIZE 10 

typedef struct Node {
    int key;
    struct Node* next;
} Node;

// 除留余数
int hash(int key) {
    return key % TABLE_SIZE;
}

// 链地址法
void insertChaining(Node* hashTable[], int key) {
    int index = hash(key);
    // 全部头插
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->key = key;
    newNode->next = hashTable[index];
    hashTable[index] = newNode;
}

// 链地址法查找
int searchChaining(Node* hashTable[], int key) {
    int index = hash(key);
    Node* temp = hashTable[index];
    while (temp != NULL) {
        if (temp->key == key) {
            return 1;
        }
        temp = temp->next;
    }
    
    return 0;
}

int main() {
    Node* hashTable[TABLE_SIZE] = {NULL};  // 初始化
    
    // 插入元素
    insertChaining(hashTable, 12);
    insertChaining(hashTable, 25);
    insertChaining(hashTable, 32);
    
    // 查找元素
    int key = 25;
    //尚未解决链地址法在找到后位置索引表示相关问题
    if (searchChaining(hashTable, key)) {
        printf("找到\n");
    } else {
        printf("不在哈希表中\n");
    }

    return 0;
}