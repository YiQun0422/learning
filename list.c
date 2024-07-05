#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <malloc.h>

#if 0 // 使用数组（线性结构）实现栈
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
#if 1 // 使用链表（链式结构）实现栈
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

#if 0 // 使用数组（线性结构）实现队列
typedef struct {

} Queue;

Queue* QueueCreate(int max_size);

void QueueDestory(Queue* queue);

int QueueEmpty(Queue* queue);

int QueueFull(Queue* queue);

// 把元素放入队列尾部
void QueuePushback(Queue* queue, int value);

// 获取队头元素
int QueueFront(Queue* queue);

// 移出队头元素
void QueuePopfront(Queue* queue);

#endif

#if 1 // 使用链表（链式结构）实现队列 先进先出
typedef struct
{
    int data;
    struct  QNode* next;
}QNode;

typedef struct
{
    QNode* front;  //队头指针
    QNode* rear;   //队尾指针
}Queue;

Queue* QueueCreate() {
    Queue* q = malloc(sizeof(Queue));
    q->front = malloc(sizeof(QNode));//新生成的结点作为头节点
    q->front->next = NULL;//带头结点,头结点指针域置空
    q->rear = q->front;//队尾指向队指向新节点
}

// 链队的入队
void QueuePush(Queue* queue, int value) {
    QNode* p = malloc(sizeof(QNode));
    p->data = value;  //为入队元素分配结点空间 数据域置为value 用指针p指向
    p->next = NULL;  
    queue->rear->next = p;  //将新结点插入队尾
    queue->rear = p;  //修改队尾指针
}

// 链队的出队 用value返回其值
void QueuePop(Queue* queue, int* value){
    if (queue->front == queue->rear)
        return false; //队列空出错
    QNode* p = queue->front->next;  //p指向队头元素
    value = p->data;
    queue->front->next = p->next;  //修改头节点指针域
    if (queue->rear == p)
        queue->rear = queue->front; //尾结点被删 指向头结点
    free(p);  //释放队头元素空间
}

// 取队头元素
int QueueTop(Queue* queue)
{
    QNode* p = queue->front->next;
    if (queue->front != queue->rear)
        return p->data;
}

#endif
