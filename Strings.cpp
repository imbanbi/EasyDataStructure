#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100

/*
typedef struct String {
    char *data;  //试图将data改为指针来实现串的位置改变
    int length;
    int capacity;
} String;

void dataIncrease(String **s, int additionalSize) {
    int newCapacity = (*s)->length + additionalSize;
    char *newDatabase = (char *)realloc((*s)->data, newCapacity * sizeof(char));
    if (!newDatabase) {
        printf("重新分配内存错误\n");
        exit(1);
    }
    (*s)->data = newDatabase; // 更新 data 指针
    (*s)->capacity = newCapacity; // 更新容量信息
}

// 初始化函数
String *initString() {
    String *s = (String *)malloc(sizeof(String));
    if (!s) {
        printf("错误\n");
        exit(1);
    }
    s->data = (char *)malloc(DATAINCREMENT * sizeof(char)); // 初始分配内存
    if (!s->data) {
        printf("数据存储错误\n");
        free(s);
        exit(1);
    }
    s->length = 0;
    s->capacity = DATAINCREMENT;
    return s;
}

//重新分配内存(未完成)，问题在于如何重建数组
void dataIncreate(struct String **s, int value) {
    char *newDatabase = (char *)realloc((*s)->data, ((*s)->length + DATAINCREMENT) * sizeof(char));
        if (!newDatabase) {
            printf("重新分配内存错误\n");
            exit(1);
        }
        *s->data = newDatabase;
}
*/

struct String{
    char data[MAX_SIZE];
    int length;
};



//初始化
void initString(String *s, const char *content) {
    strcpy(s->data, content);
    s->length = strlen(s->data);
}

//任意字符数组求长度
size_t strlen(const char *str) {
    size_t length = 0;       
    while (*str != '\0') {   
        length++;
        str++;               
    }
    return length;           
}

//求长度
int strLength(const String *s) {
    return s->length;
}

//求子串
void subString(const String *s, String *sub, int position, int len) {
    if (position < 0 || position + len > s->length || len < 0) {
        printf("非法长度或位置。\n");
        sub->data[0] = '\0';
        sub->length = 0;
        return;
    }
    strncpy(sub->data, s->data + position, len);
    sub->data[len] = '\0';
    sub->length = len;
}

//删除子串
void deleteSubString(String *s, int position, int len) {
    if (position < 0 || position + len > s->length || len < 0) {
        printf("非法长度或位置。\n");
        return;
    }
    memmove(s->data + position, s->data + position + len, s->length - position - len + 1);
    //开始想用memcpy，结果一直错，后来查了说memcpy源和目标内存块不可重叠，但仔细想下感觉也没重叠，不知道怎么会错
    s->length -= len;
}

//插入子串
void insertSubString(String *s, const String *sub, int position) {
    if (position < 0 || position > s->length) {
        printf("非法位置。\n");
        return;
    }
    if (s->length + sub->length >= MAX_SIZE) {
        printf("非法插入长度 \n");
        return;
    }
    //记得后续补写增大串容量的函数！！！
    memmove(s->data + position + sub->length, s->data + position, s->length - position + 1);
    strncpy(s->data + position, sub->data, sub->length);
    s->length += sub->length;
}

//模式匹配
int simpleMatch(const String *main, const String *pattern) {
    for (int i = 0; i <= main->length - pattern->length; i++) {
        int j = 0;
        while (j < pattern->length && main->data[i + j] == pattern->data[j]) {
            j++;
        }
        if (j == pattern->length) {
            return i+1;
        }
    }
    return -1;
}

//KMP的next数组计算
void computeNext(const String *pattern, int next[]) {
    int i = 0, j = -1;
    next[0] = -1;
    while (i < pattern->length - 1) {
        if (j == -1 || pattern->data[i] == pattern->data[j]) {
            i++;
            j++;
            next[i] = j;
        } else {
            j = next[j];
        }
    }
}

//KMP匹配算法
int KMPMatch(const String *main, const String *pattern) {
    int next[MAX_SIZE];
    computeNext(pattern, next);
    int i = 0, j = 0;
    while (i < main->length && j < pattern->length) {
        if (j == -1 || main->data[i] == pattern->data[j]) {
            i++;
            j++;
        } else {
            j = next[j];
        }
    }
    return (j == pattern->length) ? (i - j)+1 : -1;
}

//子串出现次数
int countSubstring(String *main, const String *pattern) {
    int count = 0;
    int pos = 0;

    // 创建一个副本
    String temp = *main;

    while ((pos = KMPMatch(&temp, pattern)) != -1) {
        count++;
        deleteSubString(&temp,0,pos-1+strLength(pattern));
    }
    return count;
}








// 主函数
int main() {
    String mainStr, patternStr, subStr;
    initString(&mainStr, "hello, world, hello!");
    initString(&patternStr, "hello");

    printf("主串: %s\n", mainStr.data);
    printf("模式串: %s\n", patternStr.data);

    printf("主串长度: %d\n", strLength(&mainStr));

    subString(&mainStr, &subStr, 0, 5);
    printf("子串(从 0 开始，长度为 5): %s\n", subStr.data);

    deleteSubString(&mainStr, 7, 5);
    printf("删除从位置 7 开始的 5 个字符后的主串: %s\n", mainStr.data);

    initString(&subStr, "inserted ");
    insertSubString(&mainStr, &subStr, 7);
    printf("插入子串后的主串: %s\n", mainStr.data);

    printf("简单匹配位置: %d\n", simpleMatch(&mainStr, &patternStr));

    printf("KMP 匹配位置: %d\n", KMPMatch(&mainStr, &patternStr));

    printf("模式串在主串中出现的次数: %d\n", countSubstring(&mainStr, &patternStr));

    return 0;
}


