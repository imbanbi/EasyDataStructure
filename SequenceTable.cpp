#include <stdio.h>
#include <stdlib.h>
#define LISTINCREMENT 10

struct lists {
    int *elem;
    int length;
    int listsize;
};


void initList(struct lists *L, int LIST_INIT_SIZE) {
    L->elem = (int *)malloc(LIST_INIT_SIZE * sizeof(int));
    if (!L->elem) {
        printf("内存分配错误\n");
        exit(1);
    }
    L->length = 0;
    L->listsize = LIST_INIT_SIZE;    
}//创建表 

void appendElement(struct lists *L, int value) {
    if (L->length >= L->listsize) {
        int *newbase = (int *)realloc(L->elem, (L->listsize + LISTINCREMENT) * sizeof(int));
        if (!newbase) {
            printf("重新分配内存错误\n");
            exit(1);
        }
        L->elem = newbase;
        L->listsize += LISTINCREMENT;
    }
    L->elem[L->length] = value;
    L->length++;
    printf("成功追加元素 %d\n", value);
}


void printList(struct lists L) {
    for (int i = 0; i < L.length; i++) {
        printf("%d ", L.elem[i]);
    }
    printf("\n");
}//输出表 

void listInsert(struct lists *L, int loc, int value) {
    int *newbase;
    int *locate;
    if (loc < 1 || loc > L->length + 1) {
        printf("无效位置\n");
        exit(1);
    }
    if (L->length >= L->listsize) {
        newbase = (int *)realloc(L->elem, (L->listsize + LISTINCREMENT) * sizeof(int));
        if (!newbase) {
            printf("重新分配内存错误\n");
            exit(1);
        }
        L->elem = newbase;
        L->listsize += LISTINCREMENT;
    }
    locate = &(L->elem[loc - 1]);
    for (int *p = &(L->elem[L->length - 1]); p >= locate; --p) {
        *(p + 1) = *p;
    }
    *locate = value;
    ++L->length;
    printf("成功\n");
}//插入（位置）

int locateElem(struct lists L, int element) {
    for (int i = 0; i < L.length; i++) {
        if (L.elem[i] == element) {
            return i + 1; 
        }
    }
    return 0;//无数据 
}//定位 
 
void listinsertValue(struct lists *L, int locvalue, int value) {
    int loc = locateElem(*L, locvalue);
    int *newbase;
    int *locate;
    if (loc < 1 || loc > L->length + 1) {
        printf("无效值位置\n");
        exit(1);
    }
    if (L->length >= L->listsize) {
        newbase = (int *)realloc(L->elem, (L->listsize + LISTINCREMENT) * sizeof(int));
        if (!newbase) {
            printf("重新分配内存错误\n");
            exit(1);
        }
        L->elem = newbase;
        L->listsize += LISTINCREMENT;
    }
    locate = &(L->elem[loc - 1]);
    for (int *p = &(L->elem[L->length - 1]); p >= locate; --p) {
        *(p + 1) = *p;
    }
    *locate = value;
    ++L->length;
    printf("成功\n");
}//插入（值） 

void listDelete(struct lists *L, int loc) {
    if (loc < 1 || loc > L->length) {
        printf("无效位置\n");
        return;
    }
    for (int *p = &(L->elem[loc - 1]); p < &(L->elem[L->length - 1]); ++p) {
        *p = *(p + 1);
    }
    --L->length;
    printf("删除成功\n");
}//删除（位置） 

void listDelete1(struct lists *L, int loc) {
    if (loc < 1 || loc > L->length) {
        printf("无效位置\n");
        return;
    }
    for (int *p = &(L->elem[loc - 1]); p < &(L->elem[L->length - 1]); ++p) {
        *p = *(p + 1);
    }
    --L->length;
}//删除（位置） （无检查） 

void listdeleteValue(struct lists *L, int value) {
    int loc = -1;
    for (int i = 0; i < L->length; i++) {
        if (L->elem[i] == value) {
            loc = i + 1; 
            break;
        }
    }
    if (loc != -1) {
        listDelete(L, loc);
    } else {
        printf("未找到值 %d\n", value);
    }
}//删除（值） 

void listReverse(struct lists *L) {
    for (int i = 0; i < L->length / 2; i++) {
        int temp = L->elem[i];
        L->elem[i] = L->elem[L->length - 1 - i];
        L->elem[L->length - 1 - i] = temp;
    }
    printf("列表逆转成功\n");
}//逆转 

void listClear(struct lists *L) {
	int l=L->length;
	for(int i=0;i<l;i++){
		listDelete1(L,1);
	}
    printf("列表已置空\n");
}//置空表 

void listLength(struct lists L) {
	printf("列表长度：%d\n", L.length);
}//求表长 



void isEmpty(struct lists L) {
	printf("列表是否为空：%s\n", L.length == 0 ? "是" : "否");
}//判断是否为空 

void destroyList(struct lists *L) {
    if (L->elem) {
        free(L->elem); 
        L->elem = NULL; // 防止丢失
    }
    L->length = 0;
    L->listsize = 0; 
    printf("列表已销毁\n");
}//销毁表 

void mergeLists(struct lists *La, struct lists *Lb, struct lists *Lc) {
    initList(Lc, La->length + Lb->length); 

    int i = 0, j = 0, k = 0;

    while (i < La->length && j < Lb->length) {
        if (La->elem[i] < Lb->elem[j]) {
            Lc->elem[k++] = La->elem[i++];
        } else {
            Lc->elem[k++] = Lb->elem[j++];
        }
    }

    while (i < La->length) {
        Lc->elem[k++] = La->elem[i++];
    }
    while (j < Lb->length) {
        Lc->elem[k++] = Lb->elem[j++];
    }

    Lc->length = k; 
    printf("合并成功\n");
}//有序合并 



int main() {
    struct lists L1;
    initList(&L1, 7);
    
    listInsert(&L1, 1, 1);
    listInsert(&L1, 2, 2);
    listInsert(&L1, 3, 3);
    listInsert(&L1, 4, 4);
    appendElement(&L1,6) ;
    printList(L1);

    listDelete(&L1, 2); 
    printList(L1);
    
    locateElem(L1,3);//查找并定位值为三的元素 

    listdeleteValue(&L1, 3); // 删除值为3的元素
    printList(L1);

    listReverse(&L1); // 逆置表
    printList(L1);
    

    listLength(L1); // 求表长

    listClear(&L1); // 置空表
    printList(L1);

    isEmpty(L1); // 判断是否为空
    destroyList(&L1);

    return 0;
}
