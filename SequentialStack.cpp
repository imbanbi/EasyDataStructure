#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

#define MAXSIZE 100  // 顺序栈的最大容量

// 定义顺序栈结构
struct Stack {
    int data[MAXSIZE];
    int top;
};


// 初始化栈
void initStack(struct Stack *stack) {
    stack->top = -1;
}

// 判断栈是否为空
int isEmpty(struct Stack *stack) {
    return stack->top == -1;
}

// 入栈操作
int push(struct Stack *stack, int value) {
    if (stack->top == MAXSIZE - 1) {
        printf("栈已满，无法入栈。\n");
        return -1;
    }
    stack->data[++stack->top] = value;
    return 0;
}

// 出栈操作
int pop(struct Stack *stack) {
    if (isEmpty(stack)) {
        printf("栈为空，无法出栈。\n");
        return -1;
    }
    return stack->data[stack->top--];
}

// 数制转换函数，将十进制数转为任意进制
void radixConversion(int origin, int radix) {
    struct Stack stack;
    initStack(&stack);
    while (origin > 0) {
        push(&stack, origin % radix);
        origin /= radix;
    }
    printf("转换结果：");
    while (!isEmpty(&stack)) {
        int terminal;
        terminal=pop(&stack);
        if (terminal < 10)
            printf("%d", terminal);
        else
            printf("%c", 'A' + terminal - 10); 
    }
    printf("\n");
}

// 获取栈顶元素
int peek(struct Stack *stack) {
    return stack->data[stack->top];
}

// 判断操作符优先级
int priority(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

// 执行一次运算
int applyOp(int a, int b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b;
    }
    return 0;
}

//size_t是一种用于表示对象大小的无符号整数类型，记得c好像有strlen函数，但忘了在哪个库
size_t strlen(const char *str) {
    size_t length = 0;       // 初始化长度为 0
    while (*str != '\0') {   // 遍历字符串直到遇到 '\0' 结束符
        length++;
        str++;               
    }
    return length;           
}

// 表达式计算函数(+、-、*、/)
int evaluate(const char *formula) {
    struct Stack values;   // 数栈
    struct Stack ops;      // 符栈
    initStack(&values);
    initStack(&ops);

    for (int i = 0; formula[i] != '\0'; i++) {
        // 跳过空格
        if (formula[i] == ' ')
            continue;

        // 如果是数字，将其处理成整数
        if (isdigit(formula[i])) {
            int val = 0;
            while (i < strlen(formula) && isdigit(formula[i])) {
                val = (val * 10) + (formula[i] - '0');
                i++;
            }
            push(&values, val);
            i--;  // 调整索引位置
        }

        // 如果是左括号
        else if (formula[i] == '(') {
            push(&ops, formula[i]);
        }

        // 如果是右括号，处理栈内的操作符直到遇到左括号
        else if (formula[i] == ')') {
            while (!isEmpty(&ops) && peek(&ops) != '(') {
                int val2 = pop(&values);
                int val1 = pop(&values);
                char op = pop(&ops);
                push(&values, applyOp(val1, val2, op));
            }
            pop(&ops);  // 弹出左括号
        }

        // 如果是操作符
        else if (formula[i] == '+' || formula[i] == '-' || formula[i] == '*' || formula[i] == '/') {
            while (!isEmpty(&ops) && priority(peek(&ops)) >= priority(formula[i])) {
                int val2 = pop(&values);
                int val1 = pop(&values);
                char op = pop(&ops);
                push(&values, applyOp(val1, val2, op));
            }
            push(&ops, formula[i]);
        }
    }

    // 处理剩余的操作符
    while (!isEmpty(&ops)) {
        int val2 = pop(&values);
        int val1 = pop(&values);
        char op = pop(&ops);
        push(&values, applyOp(val1, val2, op));
    }

    return pop(&values);
}



int main() {
    struct Stack stack;
    int choice, num, radix, result;

    initStack(&stack);

    // 测试数据
    int originNumbers[] = {10, 255, 100, 500, 1024};
    int radixs[] = {2, 8, 16};

    //顺序栈基本操作

    //入栈
    push(&stack, 10);
    push(&stack, 20);
    //出栈
    printf("出栈结果：%d\n", pop(&stack));
    printf("出栈结果：%d\n", pop(&stack));

    //数制转换测试
    for (int i = 0; i < 5; i++) {
        num = originNumbers[i];
        printf("十进制数 %d 的进制转换：\n", num);
        for (int j = 0; j < 3; j++) {
            radix = radixs[j];
            printf("  %d 进制: ", radix);
            radixConversion(num, radix);
        }
    }

    //表达式计算示例
    const char *formula[] = {"3+5*2", "(2+3)*4", "10/(5-3)"};
    for (int i = 0; i < 3; i++) {
        printf("表达式 %s 的计算结果为：%d\n", formula[i] ,evaluate(formula[i]));
        
    }

    return 0;
}
