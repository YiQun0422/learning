#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <malloc.h>

#define MAXSIZE 1000

#define EXPECT_EQ(actual, expect)                                                                 \
    do {                                                                                          \
        if ((expect) != (actual))                                                                 \
            printf("%s:%d: actual: %d, expect: %d\n", __FILE__, __LINE__, (actual), (expect));    \
    } while(0)

#define EXPECT_TRUE(expect) EXPECT_EQ(expect, true)

#if 0 // 顺序栈的表示  栈非空时 top永远指向栈顶元素的上一个位置
typedef struct {
    int* base;      // 栈底指针
    int* top;       // 栈顶指针
    int stacksize;  // 栈可用的最大容量
} Stack;

// 构造一个空栈s
void InitStack(Stack* s) {
    s->base = malloc(sizeof(int) * MAXSIZE);
    // s->base[n] == *(s->base+n)
    s->top = s->base;
    s->stacksize = MAXSIZE;
}

// 插入元素value为新的栈顶元素
bool PushStack(Stack* s, int value)
{
    if (s->top - s->base == s->stacksize)
        return false;  // 栈满 指向数组元素下一个空间
    *(s->top) = value;
    s->top++;          // 元素value压入栈顶 栈顶指针加1
    return true;
}

// 删除栈顶元素 用value返回其值
bool PopStack(Stack* s, int* value)
{
    if (s->top == s->base)
        return false;
    s->top -= 1;
    *value = *s->top;
    // s->top <==> (*s).top
    // *s->top <==> *((*s).top)
    return true;
}

// 返回s的栈顶元素 不修改栈顶指针
bool TopStack(Stack* s, int* value) {
    if (s->top == s->base)
        return false;
    *value = *(s->top - 1);
    return true;
}

// 销毁创造的栈
void DestoryStack(Stack* s)
{
    free(s->base);
}
#endif

// 由于这里的定义和上面的重复了, 所以可以把上面的 #if 1 改为 0 , 这里的改为 1 就可以切换不同实现
#if 1 // 使用链表（链式结构）实现栈 后进先出
//  区别于顺序结构, 链式结构支持无限长度, 所以没有 MAXSIZE
//定义链表结构体
typedef struct {
    int data;
    struct LNode* next;
}LNode;

//定义栈结构体
typedef struct {
    struct LNode* top;
}Stack;

// 构造一个空栈
void InitStack(Stack* s) {
    s->top = NULL;
}

// 在栈顶插入元素value
void PushStack(Stack* stack, int value) {
    LNode* p = malloc(sizeof(LNode));  // 生成新结点
    p->data = value;                   // 将新结点数据域置为value
    p->next = stack->top;              // 头插法插入p结点
    stack->top = p;                    // 新生成的结点作为top
}

// 删除s的栈顶元素 用value返回其值
bool PopStack(Stack* stack, int* value) {
    if (stack->top == NULL)
        return false;       // 栈空
    LNode* p = stack->top;  // p结点指向栈顶
    *value = p->data;       // 栈顶的值赋给value
    stack->top = p->next;   // 栈顶结点为p的下一个结点
    free(p);                // 释放p结点空间
    return true;
}

// 返回s的栈顶元素 不修改栈顶指针
bool TopStack(Stack* stack, int* value)
{
    LNode* p = stack->top;
    if (stack == NULL)
        return false;
    else
        *value = p->data;
        return true;
}

#endif

#if 0 // 队列的顺序表示 循环队列
typedef struct {
    int* base; //存储空间的基地址
    int front; //头指针
    int rear;  //尾指针
} Queue;

// 构造一个空队列q
void InitQueue(Queue* q) {
    q->base = malloc(sizeof(int) * MAXSIZE); // 为队列分配数组空间
    q->front  = 0;
    q->rear = q->front;                      // 队列为空
}

// 求队列长度
int QueueLength(Queue* queue) {
    return(queue->rear - queue->front + MAXSIZE) % MAXSIZE;
}

// 循环队列的入队
bool PushQueue(Queue* queue, int value) {
    if ((queue->rear + 1) % MAXSIZE == queue->front)
        return false;                           // 队满
    queue->base[queue->rear] = value;           // 新元素插入队尾
    queue->rear = (queue->rear + 1) % MAXSIZE;  // 队尾指针加1
    return true;
}

// 移出队头元素 用value返回其值
bool PopQueue(Queue* queue, int* value) {
    if (queue->front == queue->rear)
        return false;                             // 队空
    *value = queue->base[queue->front];           // 保存队头元素
    queue->front = (queue->front + 1) % MAXSIZE;  // 队头指针加1
    return true;
}

// 获取队头元素
bool TopQueue(Queue* queue, int* value) {
    if (queue->front == queue->rear)        // 队列为空
        return false;
    else
        *value = queue->base[queue->front]; // 返回队头元素的值
        return true;
}

// 销毁创建的队列
void DestoryQueue(Queue* q) {
    free(q->base);
}

#endif

#if 1 // 使用链表（链式结构）实现队列 先进先出
typedef struct
{
    int data;
    struct  QNode* next;
}QNode; // 定义结点结构体

typedef struct
{
    QNode* front;  // 队头指针
    QNode* rear;   // 队尾指针
}Queue;            // 定义队列结构体

// 构造一个空队列q
void InitQueue(Queue* q) {
    q->front = malloc(sizeof(QNode)); // 新生成的结点作为头节点
    q->rear = q->front;               // 队尾指向队指向新节点
    q->front->next = NULL;            // 带头结点,头结点指针域置空
}

// 链队的入队
void PushQueue(Queue* queue, int value) {
    QNode* p = malloc(sizeof(QNode));
    p->data = value;        // 为入队元素分配结点空间 数据域置为value 用指针p指向
    p->next = NULL;
    queue->rear->next = p;  // 将新结点插入队尾
    queue->rear = p;        // 修改队尾指针
}

// 链队的出队 用value返回其值
bool PopQueue(Queue* queue, int* value) {
    if (queue->front == queue->rear)
        return false;                // 队列空出错
    QNode* p = queue->front->next;   // p指向队头元素
    *value = p->data;
    queue->front->next = p->next;    // 修改头节点指针域
    if (queue->rear == p)
        queue->rear = queue->front;  // 尾结点被删 指向头结点
    free(p);                         // 释放队头元素空间
    return true;
}

// 取队头元素
bool TopQueue(Queue* queue, int* value)
{
    QNode* p = queue->front->next;
    if (queue->front == queue->rear)
        return false;
    else
        *value = p->data;
        return true;
}

#endif

int main() {
    // 测试栈
    Stack* s = malloc(sizeof(Stack));
    int value = 0, value1 = 1, value2 = 2;
    int topstack = 0;

    InitStack(s);
    PushStack(s, value1);              // 元素1入栈
    TopStack(s, &topstack);
    EXPECT_EQ(topstack, 1);            // 判断是否入栈成功
    PushStack(s, value2);              // 元素2入栈
    TopStack(s, &topstack);
    EXPECT_EQ(topstack, 2);            // 判断是否入栈成功
    EXPECT_TRUE(PopStack(s, &value));  // 元素2出栈
    EXPECT_EQ(value, 2);               // 判断是否出栈成功
    TopStack(s, &topstack);
    EXPECT_EQ(topstack, 1);            // 判断栈顶元素是否为1
    //DestoryStack(s);
    //free(s);

    // 测试队列
    Queue* q = malloc(sizeof(Queue));
    int valuea = 0, valueb = 3, valuec = 4;
    int topqueue = 0;

    // 测试顺序队列
    /*InitQueue(q);
    EXPECT_TRUE(PushQueue(q, valueb));  // 元素3入队
    TopQueue(q, &topqueue);
    EXPECT_EQ(topqueue, 3);             // 判断是否入队成功
    EXPECT_TRUE(PushQueue(q, valuec));  // 元素4入队
    EXPECT_EQ(QueueLength(q), 2);       // 判断队列长度是否为2
    EXPECT_TRUE(PopQueue(q, &valuea));  // 元素3出队
    EXPECT_EQ(valuea, 3);               // 判断是否出队成功
    TopQueue(q, &topqueue);
    EXPECT_EQ(topqueue,4);              // 取队列元素判断是否为4
    DestoryQueue(q);
    free(q);*/

    // 测试链队列
    InitQueue(q);
    PushQueue(q, valueb);               // 元素3入队
    TopQueue(q, &topqueue);
    EXPECT_EQ(topqueue, 3);             // 判断是否入队成功
    EXPECT_TRUE(PopQueue(q, &valuea));  // 元素3出队
    EXPECT_EQ(valuea, 3);               // 判断是否出队成功
    PushQueue(q, valuec);               // 元素4入队
    TopQueue(q, &topqueue);
    EXPECT_EQ(topqueue, 4);             // 取队列元素判断是否为4

    return 0;
}
