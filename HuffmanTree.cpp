#include <stdio.h>
#include <stdlib.h>

typedef struct HuffmanNode {
    char data;
    int weight;
    struct HuffmanNode *left, *right;
} HuffmanNode;

typedef struct MinSet {
    HuffmanNode** elements;
    int size;
    int capacity;
} MinSet;

// 创建最小集合
MinSet* createMinSet(int capacity) {
    MinSet* Set = (MinSet*)malloc(sizeof(MinSet));
    Set->elements = (HuffmanNode**)malloc(sizeof(HuffmanNode*) * (capacity + 1));
    Set->size = 0;
    Set->capacity = capacity;
    return Set;
}

// 插入集合
void insertSet(MinSet* Set, HuffmanNode* node) {
    int i = ++Set->size;
    while (i > 1 && node->weight < Set->elements[i / 2]->weight) {
        Set->elements[i] = Set->elements[i / 2];
        i /= 2;
    }
    Set->elements[i] = node;
}

// 删除最小元素
HuffmanNode* deleteMin(MinSet* Set) {
    HuffmanNode* minNode = Set->elements[1];
    HuffmanNode* lastNode = Set->elements[Set->size--];

    int parent = 1, child;
    while (parent * 2 <= Set->size) {
        child = parent * 2;
        if (child < Set->size && Set->elements[child]->weight > Set->elements[child + 1]->weight) {
            child++;
        }
        if (lastNode->weight <= Set->elements[child]->weight) break;
        Set->elements[parent] = Set->elements[child];
        parent = child;
    }
    Set->elements[parent] = lastNode;
    return minNode;
}

// 生成
HuffmanNode* createHuffmanTree(char* data, int* weights, int size) {
    MinSet* Set = createMinSet(size);
    for (int i = 0; i < size; i++) {
        HuffmanNode* node = (HuffmanNode*)malloc(sizeof(HuffmanNode));
        node->data = data[i];
        node->weight = weights[i];
        node->left = node->right = NULL;
        insertSet(Set, node);
    }

    for (int i = 1; i < size; i++) {
        HuffmanNode* left = deleteMin(Set);
        HuffmanNode* right = deleteMin(Set);

        HuffmanNode* newNode = (HuffmanNode*)malloc(sizeof(HuffmanNode));
        newNode->data = '\0'; // 内部结点无字符
        newNode->weight = left->weight + right->weight;
        newNode->left = left;
        newNode->right = right;

        insertSet(Set, newNode);
    }
    return deleteMin(Set);
}

// 递归输出（本来想让它更像一个树的，但是最后感觉太麻烦了，从网上看到有这种表示法，于是直接复制了一下）
void printHuffmanTree(HuffmanNode* root, int depth) {
    if (root) {
        for (int i = 0; i < depth; i++) printf("  ");
        printf("%c(%d)\n", root->data ? root->data : '#', root->weight);
        printHuffmanTree(root->left, depth + 1);
        printHuffmanTree(root->right, depth + 1);
    }
}

int main() {
    char data[] = {'a', 'b', 'c', 'd', 'e', 'f'};
    int weights[] = {5, 9, 12, 13, 16, 45};
    int size = sizeof(data) / sizeof(data[0]);

    HuffmanNode* root = createHuffmanTree(data, weights, size);
    printHuffmanTree(root, 0);

    return 0;
}
