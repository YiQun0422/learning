#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <malloc.h>

#if 1 // 顺序栈的表示  栈非空时 top永远指向栈顶元素的上一个位置
typedef struct {
    int* base;  //栈底指针
    int* top;   //栈顶指针
    int stacksize;  //栈可用的最大容量
} Stack;

// 创建一个栈
// 参数 max_size: 支持的最大长度
Stack* StackCreate(int max_size) {
    Stack* s;
    s->base = malloc(sizeof(int)*max_size);  //为顺序栈动态分配最大容量为max_size的数组空间
    s->top = s->base;  //top初始为base 空栈
    s->stacksize = max_size;  //栈最大容量为max_size

    return s;
}

// 顺序栈的入栈
void StackPush(Stack* stack, int value) {
    if (stack->top - stack->base == stack->stacksize)
        return false; //栈满 指向数组元素下一个空间
    *stack->top = value;
    stack->top++;  //元素value压入栈顶 栈顶指针加1
}

// 从栈顶取出一个元素 用value返回其值
void StackPop(Stack* stack, int* value) {
    if (stack->top == stack->base)
        return false; //栈空
    stack->top--;
    value = *stack->top;  //栈顶指针减1 将栈顶元素赋给value
}

// 获取栈顶的元素（不取出）
int StackTop(Stack* stack) {
    if (stack->top != stack->base)
        return *(stack->top - 1);  //返回栈顶元素的值
}

#endif

// 由于这里的定义和上面的重复了, 所以可以把上面的 #if 1 改为 0 , 这里的改为 1 就可以切换不同实现
#if 0 // 使用链表（链式结构）实现栈 后进先出
//  区别于顺序结构, 链式结构支持无限长度, 所以没有 max_size 也不需要 StackFull 函数

typedef struct {
    int data;
    struct Stack* next; //和单链表一致
} Stack;

Stack* StackCreate() {
    Stack* s = malloc(sizeof(Stack));
    s = NULL;//第一个结点作为栈顶

    return s;
}

// 链栈的入栈
void StackPush(Stack* stack, int value) {
    Stack* p = malloc(sizeof(Stack));
    p->data = value;  //生成新结点 将新结点数据域置为value
    p->next = stack;
    stack = p;  //插入的元素在栈顶
}

// 从栈顶取出一个元素 用value返回其值
void StackPop(Stack* stack,int* value){
    if (stack == NULL)
        return false;  //栈空
    value = stack->data;  //将栈顶元素赋值给value
    Stack* p = stack;  //用p临时保存栈顶空间
    stack = stack->next; //修改栈顶指针后移
    free(p);  //释放原栈顶元素空间
}

// 获取栈顶的元素（不取出）
int StackTop(Stack* stack)
{
    if (stack != NULL)
        return stack->data;
}

#endif

#if 1 // 队列的顺序表示 循环队列
typedef struct {
    int* base; //存储空间的基地址
    int front; //头指针
    int rear;  //尾指针
} Queue;

Queue* QueueCreate(int max_size) {
    Queue* q;
    q->base = malloc(sizeof(int) * max_size); //为队列分配数组空间
    q->front = q->rear = q; //队列为空
}

//求队列长度
int QueueLength(Queue* queue,int max_size) {
    return(queue->rear - queue->front + max_size) % max_size;
}

// 循环队列的入队
void QueuePushback(Queue* queue, int value,int max_size) {
    if ((queue->rear + 1) % max_size == queue->front)
        return false; //队满
    queue->base[queue->rear] = value;  //新元素插入队尾
    queue->rear = (queue->rear + 1) % max_size;  //队尾指针加1
}

// 移出队头元素 用value返回其值
void QueuePopfront(Queue* queue,int* value,int max_size) {
    if (queue->front == queue->rear)
        return false; //队空
    value = queue->base[queue->front]; //保存队头元素
    queue->front = (queue->front + 1) % max_size; //队头指针加1
}

// 获取队头元素
int QueueFront(Queue* queue) {
    if (queue->front != queue->rear)
        return queue->base[queue->front];  //返回队头元素的值
}

#endif

#if 0 // 使用链表（链式结构）实现队列 先进先出
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

    return q;
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
