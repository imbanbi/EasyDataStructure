#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

#define MAXSIZE 100  // 循环队列的最大容量

// 定义循环队列结构
struct Queue {
    int data[MAXSIZE];
    int front, rear;
};

// 初始化循环队列
void initQueue(struct Queue *queue) {
    queue->front = queue->rear = 0;
}

// 判断队列是否为空
int isEmpty(struct Queue *queue) {
    return queue->front == queue->rear;
}

// 入队操作
int enqueue(struct Queue *queue, int value) {
    if ((queue->rear + 1) % MAXSIZE == queue->front) {
        printf("队列已满，无法入队。\n");
        return -1;
    }
    queue->data[queue->rear] = value;
    queue->rear = (queue->rear + 1) % MAXSIZE;
    return 0;
}

// 出队操作
int dequeue(struct Queue *queue) {
    if (isEmpty(queue)) {
        printf("队列为空，无法出队。\n");
        return -1;
    }
    int value = queue->data[queue->front];
    queue->front = (queue->front + 1) % MAXSIZE;
    return value;
}

int main() {
    struct Queue queue;
    int choice, num, base, result;

    initQueue(&queue);

    // 数据
    int testDecimalNumbers[] = {10, 255, 100, 500, 1024};
    int testBases[] = {2, 8, 16};

    //循环队列基本操作

    //入队
    enqueue(&queue, 1);
    enqueue(&queue, 2);

    //出队
    printf("出队结果：%d\n", dequeue(&queue));

    return 0;
}

