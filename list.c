#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#if 1 // 使用数组（线性结构）实现栈
typedef struct {
    int* base;
    int* top;
    int stacksize;
} Stack;

// 创建一个栈
// 参数 max_size: 支持的最大长度
Stack* StackCreate(int max_size) {
    Stack *s=malloc(sizeof(Stack));
    s->base = malloc(sizeof(int)*max_size);
    s->top = s->base;
    s->stacksize = max_size;

    return s;
}

// 删除 StackCreate 创建的栈
void StackDestory(Stack* stack) {
    if (StackEmpty(stack))
        return 0;
    stack->top--;
}

// 判断栈是否为空, 返回1表示空, 0表示不空 (int强制转换为bool, 0为false, 其他为true)
int StackEmpty(Stack* stack) {
    if (stack->top == stack->base)
        return 1;
    return 0;
}

// 判断栈是否已满, 返回1表示满，0表示不满
int StackFull(Stack* stack) {
    if (stack->top - stack->base == stack->stacksize)
        return 1;
    return 0;
}

// 向栈顶放入一个元素
void StackPush(Stack* stack, int value) {
    if (!StackFull(stack))
        *stack->top = value;
        stack->top++;
}

// 获取栈顶的元素（不取出）
int StackTop(Stack* stack) {
    if (stack->top != stack->base)
        return *(stack->top - 1);
}

// 从栈顶取出一个元素 用value返回其值
void StackPop(Stack* stack,int* value) {
    if (!StackEmpty(stack))
        stack->top--;
        value=stack->top;
}

#endif

// 由于这里的定义和上面的重复了, 所以可以把上面的 #if 1 改为 0 , 这里的改为 1 就可以切换不同实现
#if 0 // 使用链表（链式结构）实现栈
//  区别于顺序结构, 链式结构支持无限长度, 所以没有 max_size 也不需要 StackFull 函数

typedef struct {
    int data;
    struct Stack* next; //和单链表一样
} Stack;

// 这里的参数没有意义，仅仅为了保证和上面的接口一致
Stack* StackCreate() {
    Stack* s = malloc(sizeof(Stack));
    s = NULL;//第一个结点作为栈顶

    return s;
}

// 删除 StackCreate 创建的栈
void StackDestory(Stack* stack) {
    free(stack);
}

// 判断栈是否为空, 返回0表示空, 1表示不空
int StackEmpty(Stack* stack) {
    if (stack == NULL)
        return 0;
    return 1;
}

// 永远不会满，仅仅为了保证和上面的接口一致
int StackFull(Stack* stack) { return 0; }

// 向栈顶放入一个元素
void StackPush(Stack* stack, int value) {
    Stack* p = malloc(sizeof(Stack));
    p->data = value;
    p->next = stack;
    stack = p;
}

// 获取栈顶的元素（不取出）
int StackTop(Stack* stack)
{
    if (stack != NULL)
        return stack->data;
}

// 从栈顶取出一个元素 用value返回其值
void StackPop(Stack* stack,int* value){
    if (stack == NULL)
        return false;
    value = stack->data;
    Stack* p = stack;
    free(p);
}

#endif

#if 1 // 使用数组（线性结构）实现队列
typedef struct {
} Queue;

Queue *QueueCreate(int max_size);

void QueueDestory(Queue *queue);

int QueueEmpty(Queue *queue);

int QueueFull(Queue *queue);

// 把元素放入队列尾部
void QueuePushback(Queue *queue, int value);

// 获取队头元素
int QueueFront(Queue *queue);

// 移出队头元素
void QueuePopfront(Queue *queue);

#endif

#if 0 // 使用链表（链式结构）实现队列，和上面类似
#endif

void check_int(int a, int b) {
    if (a != b) {
        printf("actual: %d, except: %d\n", a, b);
        abort(); // 终止程序
    }
}

void check(bool v) {
    if (!v) {
        printf("actual: false, except: true\n");
        abort(); // 终止程序
    }
}

void test_stack() {
    // 一下代码仅为使用示例，测试代码自行编写

    // 创建一个空的 stack
    Stack *s = StackCreate(3);

    // 向 stack 中添加一个元素
    if (!StackFull(s)) {
        StackPush(s, 1);
    }

    // 从 stack 末尾移出一个元素并打印这个元素
    if (!StackEmpty(s)) {
        printf("%d\n", StackTop(s));
        StackPop(s);
    }

    // 使用 check 测试代码, 而不是打印出来靠眼睛测试
    check(StackEmpty(s));
    check(!StackFull(s));

    StackPush(s, 2);
    check(!StackEmpty(s));
    check(!StackFull(s));
    check_int(StackTop(s), 2);

    StackPop(s);
    check(StackEmpty(s));
    check(!StackFull(s));

    StackPush(s, 2);
    StackPush(s, 3);
    StackPush(s, 4);
    check(!StackEmpty(s));
    check(StackFull(s));

    printf("tests all passed\n");
}

void test_queue() {
    // 关于 queue 的函数命名
    // 考虑到客观上存在双端队列，就是说可以同时从队头或队尾插入、删除
    // 所以函数命名为 QueuePopfront 而不是 QueuePop

    Queue *q = QueueCreate(3);

    if (!QueueFull(q)) {
        QueuePushback(q, 1);
    }

    if (!QueueEmpty(q)) {
        printf("%d\n", QueueFront(q));
        QueuePopfront(q);
    }

    check(QueueEmpty(q));
    check(!QueueFull(q));

    QueuePushback(q, 2);
    check(!QueueEmpty(q));
    check(!QueueFull(q));
    check_int(QueueFront(q), 2);

    QueuePopfront(q);
    check(QueueEmpty(q));
    check(!QueueFull(q));

    QueuePushback(q, 2);
    QueuePushback(q, 3);
    QueuePushback(q, 4);
    check(!QueueEmpty(q));
    check(QueueFull(q));

    printf("tests all passed\n");
}
