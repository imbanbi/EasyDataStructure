#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *next;
};

// 创建空链表
struct Node* createEmptyList() {
    return NULL;
}

// 尾插法
struct Node* createListForward(int arr[], int n) {
    struct Node *head = NULL, *tail = NULL;
    for (int i = 0; i < n; i++) {
        struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));
        newNode->data = arr[i];
        newNode->next = NULL;
        if (!head) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
    }
    return head;
}

// 头插法
struct Node* createListBackward(int arr[], int n) {
    struct Node *head = NULL;
    for (int i = 0; i < n; i++) {
        struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));
        newNode->data = arr[i];
        newNode->next = head;
        head = newNode;
    }
    return head;
}

// 打印链表
void printList(struct Node *head) {
    struct Node *current = head;
    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}

// 插入元素
void insertElement(struct Node **head, int position, int value) {
    struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    if (position == 0) {
        newNode->next = *head;
        *head = newNode;
        return;
    }
    struct Node *current = *head;
    for (int i = 0; current != NULL && i < position - 1; i++) {
        current = current->next;
    }
    if (current == NULL) {
        printf("插入位置无效\n");
        return;
    }
    newNode->next = current->next;
    current->next = newNode;
}

// 删除元素
void deleteElement(struct Node **head, int value) {
    struct Node *current = *head, *prev = NULL;
    while (current != NULL && current->data != value) {
        prev = current;
        current = current->next;
    }
    if (current == NULL) {
        printf("未找到元素\n");
        return;
    }
    if (prev == NULL) {
        *head = current->next;
    } else {
        prev->next = current->next;
    }
    free(current);
    printf("删除成功\n");
}

// 查找元素
struct Node* searchElement(struct Node *head, int value) {
    struct Node *current = head;
    while (current != NULL && current->data != value) {
        current = current->next;
    }
    return current;
}

// 查找前驱节点
struct Node* findPredecessor(struct Node *head, int value) {
    struct Node *current = head, *prev = NULL;
    while (current != NULL && current->data != value) {
        prev = current;
        current = current->next;
    }
    return prev;
}

// 查找后继节点
struct Node* findSuccessor(struct Node *head, int value) {
    struct Node *current = searchElement(head, value);
    return (current != NULL) ? current->next : NULL;
}

// 求链表长度
int getListLength(struct Node *head) {
    int length = 0;
    struct Node *current = head;
    while (current != NULL) {
        length++;
        current = current->next;
    }
    return length;
}

// 清空链表
void clearList(struct Node **head) {
    struct Node *current = *head;
    while (current != NULL) {
        struct Node *temp = current;
        current = current->next;
        free(temp);
    }
    *head = NULL;
    printf("链表已清空\n");
}

// 销毁链表
void destroyList(struct Node **head) {
    clearList(head);
    printf("链表已销毁\n");
}

// 链表前 m 个节点与后 n 个节点对调
void swapSegments(struct Node **head, int m, int n) {
    int length = getListLength(*head);
    if (m + n > length) {
        printf("m 和 n 之和大于链表长度，无法对调。\n");
        return;
    }

    struct Node *current = *head, *prevM = NULL, *prevN = NULL, *segmentM = NULL, *segmentN = NULL,*tail=NULL,*head1=NULL;

    // 找到前 m 个节点末尾和后 n 个节点开头
    for (int i = 1; i <= length; i++) {

        if (i == m) {
            prevM = current;
            segmentM = current->next;
        }
        if(i == 1){
            head1=current;
        }
        if (i == length - n) {
            prevN = current;
            segmentN = current->next;
        }
        if(i==length){
            tail=current;
            break;
        }
        current = current->next;
    }

    // 对调前 m 和后 n 段
    if (prevM && segmentM && prevN && segmentN) {

        if(m+n < length){
            tail->next = segmentM;
            *head = segmentN;
            prevN->next =head1;
            prevM->next = NULL;
        }
        if(m+n == length){
            tail->next = *head;
            prevM->next = NULL;
            *head = segmentN;
        }
        

        printf("链表前 %d 个和后 %d 个节点已对调。\n", m, n);
    } else {
        printf("对调失败，检查输入的 m 和 n 是否有效。\n");
    }
}

// 合并两个有序链表
struct Node* mergeSortedLists(struct Node *list1, struct Node *list2) {
    struct Node dummy;
    dummy.next = NULL;
    struct Node *tail = &dummy;

    // 合并过程，保持有序
    while (list1 && list2) {
        if (list1->data < list2->data) {
            tail->next = list1;
            list1 = list1->next;
        } else {
            tail->next = list2;
            list2 = list2->next;
        }
        tail = tail->next;
    }

    // 连接剩余节点
    if (list1) tail->next = list1;
    if (list2) tail->next = list2;

    return dummy.next;
}


int main() {
    struct Node *head = createEmptyList();
    int arr[] = {1, 2, 3, 4, 5};

    printf("1. 创建空链表\n");
    head = createEmptyList();
    printf("空链表创建成功\n");

    printf("2. 正序创建链表\n");
    head = createListForward(arr, 5);
    printf("正序链表创建成功: ");
    printList(head);

    printf("3. 逆序创建链表\n");
    destroyList(&head);
    head = createListBackward(arr, 5);
    printf("逆序链表创建成功: ");
    printList(head);

    printf("4. 插入新元素\n");
    insertElement(&head, 2, 10); // 在第2个位置插入10
    printf("插入后的链表: ");
    printList(head);

    printf("5. 删除元素\n");
    deleteElement(&head, 3); // 删除值为3的元素
    printf("删除后的链表: ");
    printList(head);

    printf("6. 查找元素\n");
    struct Node *found = searchElement(head, 4);
    printf(found ? "找到元素 4\n位置为%d\n"  : "未找到元素 4\n ",searchElement(head,4));

    printf("7. 交换元素\n");
    swapSegments(&head,2,3);
    printList(head);

    printf("8. 查找前驱节点\n");
    struct Node *predecessor = findPredecessor(head, 10);
    printf(predecessor ? "元素 10 的前驱节点: %d\n" : "没有前驱节点\n", predecessor ? predecessor->data : -1);

    printf("9. 查找后继节点\n");
    struct Node *successor = findSuccessor(head, 2);
    printf(successor ? "元素 2 的后继节点: %d\n" : "没有后继节点\n", successor ? successor->data : -1);

    printf("10. 求链表长度\n");
    int length = getListLength(head);
    printf("链表长度为: %d\n", length);

    printf("11. 清空链表\n");
    clearList(&head);
    printList(head);

    printf("12. 销毁链表\n");
    destroyList(&head);
    printList(head);

    return 0;
}
